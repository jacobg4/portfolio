<?php

/**
 * helpers_csrf.php — CSRF token generation and verification.
 *
 * Usage in forms:   <?= csrfField() ?>
 * Usage in handlers: verifyCsrfToken();   // dies with 403 on failure
 */

// ──────────────────────────────────────────────────────────────────────────────
//  Token management
// ──────────────────────────────────────────────────────────────────────────────

/**
 * Return (and lazily create) the session CSRF token.
 */
function getCsrfToken(): string
{
    if (empty($_SESSION['csrf_token'])) {
        $_SESSION['csrf_token'] = bin2hex(random_bytes(32));
    }
    return $_SESSION['csrf_token'];
}

/**
 * Return a hidden <input> element carrying the current CSRF token.
 * Drop <?= csrfField() ?> inside every <form method="post">.
 */
function csrfField(): string
{
    $token = htmlspecialchars(getCsrfToken(), ENT_QUOTES, 'UTF-8');
    return '<input type="hidden" name="csrf_token" value="' . $token . '">';
}

/**
 * Verify the CSRF token submitted with a POST request.
 * Terminates with HTTP 403 if the token is absent or wrong.
 * Call this at the top of every post handler, after session_start().
 */
function verifyCsrfToken(): void
{
    $submitted = $_POST['csrf_token'] ?? '';
    $expected  = $_SESSION['csrf_token'] ?? '';

    if ($expected === '' || !hash_equals($expected, $submitted)) {
        http_response_code(403);
        exit('403 Forbidden — invalid or missing CSRF token.');
    }
}

/**
 * Like verifyCsrfToken() but returns false instead of exiting.
 * Use in AJAX handlers that return JSON.
 */
function verifyCsrfTokenSoft(): bool
{
    $submitted = $_POST['csrf_token'] ?? '';
    $expected  = $_SESSION['csrf_token'] ?? '';
    return $expected !== '' && hash_equals($expected, $submitted);
}
