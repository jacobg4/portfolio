<?php
/**
 * AccountManager.php — Player account registration, login, and session management.
 *
 * Session keys managed here:
 *   $_SESSION['account_id']       — int, set on login
 *   $_SESSION['account_username'] — string, set on login
 *   $_SESSION['character_slot']   — int 1-5, slot of the currently active character
 */

// ── Auth helpers ─────────────────────────────────────────────────────────────

/**
 * True when a player account is logged in for this session.
 */
function isLoggedIn(): bool
{
    return !empty($_SESSION['account_id']);
}

/**
 * Returns the logged-in account ID, or null.
 */
function currentAccountId(): ?int
{
    return isset($_SESSION['account_id']) ? (int)$_SESSION['account_id'] : null;
}

/**
 * Returns the logged-in username, or null.
 */
function currentUsername(): ?string
{
    return $_SESSION['account_username'] ?? null;
}

/**
 * Redirects to login.php if no account is logged in, or if another session
 * has taken over this account (session token mismatch).
 */
function requireLogin(string $redirectTo = ''): void
{
    if (!isLoggedIn()) {
        $target = '/login.php';
        if ($redirectTo !== '') {
            $target .= '?redirect=' . urlencode($redirectTo);
        }
        header('Location: ' . $target);
        exit;
    }

    // Verify this session still holds the active token for the account
    $localToken = $_SESSION['session_token'] ?? null;
    if ($localToken !== null) {
        $stmt = getDb()->prepare("SELECT session_token FROM accounts WHERE id = ?");
        $stmt->execute([$_SESSION['account_id']]);
        $dbToken = $stmt->fetchColumn();
        if ($dbToken !== $localToken) {
            // Another login has taken over — kill this session
            session_unset();
            session_destroy();
            header('Location: /login.php?notice=session_replaced');
            exit;
        }
    }
}

/**
 * Register a new account.
 *
 * Returns ['ok' => true, 'account_id' => int] on success.
 * Returns ['ok' => false, 'error' => string] on failure.
 */
function registerAccount(string $username, string $password): array
{
    $username = trim($username);

    // Validate
    if ($username === '') {
        return ['ok' => false, 'error' => 'Username cannot be empty.'];
    }
    if (strlen($username) < 3) {
        return ['ok' => false, 'error' => 'Username must be at least 3 characters.'];
    }
    if (strlen($username) > 60) {
        return ['ok' => false, 'error' => 'Username cannot exceed 60 characters.'];
    }
    if (!preg_match('/^[A-Za-z0-9_]+$/', $username)) {
        return ['ok' => false, 'error' => 'Username may only contain letters, numbers, and underscores.'];
    }
    if (strlen($password) < 8) {
        return ['ok' => false, 'error' => 'Password must be at least 8 characters.'];
    }

    $db = getDb();

    // Check uniqueness (case-insensitive)
    $stmt = $db->prepare("SELECT id FROM accounts WHERE LOWER(username) = LOWER(?)");
    $stmt->execute([$username]);
    if ($stmt->fetchColumn() !== false) {
        return ['ok' => false, 'error' => 'That username is already taken.'];
    }

    $hash = password_hash($password, PASSWORD_BCRYPT);

    $stmt = $db->prepare(
        "INSERT INTO accounts (username, password_hash) VALUES (?, ?)"
    );
    $stmt->execute([$username, $hash]);

    return ['ok' => true, 'account_id' => (int)$db->lastInsertId()];
}

/**
 * Attempt login with username + password.
 *
 * Returns ['ok' => true, 'account_id' => int, 'username' => string] on success.
 * Returns ['ok' => false, 'error' => string] on failure.
 */
function loginAccount(string $username, string $password): array
{
    $username = trim($username);

    if ($username === '' || $password === '') {
        return ['ok' => false, 'error' => 'Username and password are required.'];
    }

    $db   = getDb();
    $stmt = $db->prepare(
        "SELECT id, username, password_hash FROM accounts WHERE LOWER(username) = LOWER(?)"
    );
    $stmt->execute([$username]);
    $row = $stmt->fetch();

    if (!$row || !password_verify($password, $row['password_hash'])) {
        return ['ok' => false, 'error' => 'Invalid username or password.'];
    }

    // Issue a new session token — invalidates any existing active session
    $token = bin2hex(random_bytes(32));
    $db->prepare("UPDATE accounts SET last_login_at = NOW(), session_token = ? WHERE id = ?")
       ->execute([$token, $row['id']]);

    return [
        'ok'           => true,
        'account_id'   => (int)$row['id'],
        'username'     => $row['username'],
        'session_token'=> $token,
    ];
}

/**
 * Write account info to the session.
 * Call this after a successful loginAccount().
 */
function setAccountSession(int $accountId, string $username, string $sessionToken = ''): void
{
    session_regenerate_id(true);
    $_SESSION['account_id']       = $accountId;
    $_SESSION['account_username'] = $username;
    if ($sessionToken !== '') {
        $_SESSION['session_token'] = $sessionToken;
    }
}

/**
 * Log out: clear account and character state from session.
 */
function logoutAccount(): void
{
    if (!empty($_SESSION['account_id'])) {
        getDb()->prepare("UPDATE accounts SET session_token = NULL WHERE id = ?")
               ->execute([$_SESSION['account_id']]);
    }

    unset(
        $_SESSION['account_id'],
        $_SESSION['account_username'],
        $_SESSION['session_token'],
        $_SESSION['character'],
        $_SESSION['adventure_mode'],
        $_SESSION['character_slot'],
        $_SESSION['adv_combat'],
        $_SESSION['road_encounter'],
        $_SESSION['road_travel'],
        $_SESSION['adv_venue'],
        $_SESSION['adv_npc'],
        $_SESSION['adv_topic'],
        $_SESSION['adv_result'],
        $_SESSION['adv_notices']
    );
}

/**
 * Count how many character slots the account has used.
 */
function accountUsedSlots(int $accountId): int
{
    $db   = getDb();
    $stmt = $db->prepare("SELECT COUNT(*) FROM characters WHERE account_id = ? AND is_archived=0");
    $stmt->execute([$accountId]);
    return (int)$stmt->fetchColumn();
}

/**
 * True if the account has at least one free slot.
 */
function accountHasFreeSlot(int $accountId): bool
{
    return accountUsedSlots($accountId) < CHAR_SLOT_LIMIT;
}

/**
 * Find and return the lowest available slot number (1–CHAR_SLOT_LIMIT) for an account.
 * Returns null if all slots are full.
 * Includes all rows (archived and active) because the uk_account_slot unique index applies to
 * both; archiveCharacterInDb moves archived rows to slot = id+10000, but legacy rows may
 * still occupy normal slot numbers until that migration runs.
 */
function nextFreeSlot(int $accountId): ?int
{
    $db   = getDb();
    $stmt = $db->prepare(
        "SELECT slot FROM characters WHERE account_id = ? AND slot <= ? ORDER BY slot"
    );
    $stmt->execute([$accountId, CHAR_SLOT_LIMIT]);
    $used = array_column($stmt->fetchAll(), 'slot');

    for ($i = 1; $i <= CHAR_SLOT_LIMIT; $i++) {
        if (!in_array($i, $used, true)) {
            return $i;
        }
    }
    return null;
}
