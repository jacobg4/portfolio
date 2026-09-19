<?php
/**
 * db.php — PDO connection singleton.
 *
 * Returns a shared PDO instance configured for Blood & Burden.
 * Throws a RuntimeException if the connection fails — callers should
 * catch it and show a friendly error rather than a raw stack trace.
 */

function getDb(): PDO
{
    static $pdo = null;

    if ($pdo !== null) {
        return $pdo;
    }

    $dsn = sprintf(
        'mysql:host=%s;port=%s;dbname=%s;charset=utf8mb4',
        DB_HOST,
        DB_PORT,
        DB_NAME
    );

    $options = [
        PDO::ATTR_ERRMODE            => PDO::ERRMODE_EXCEPTION,
        PDO::ATTR_DEFAULT_FETCH_MODE => PDO::FETCH_ASSOC,
        PDO::ATTR_EMULATE_PREPARES   => false,
    ];

    try {
        $pdo = new PDO($dsn, DB_USER, DB_PASS, $options);
    } catch (PDOException $e) {
        throw new RuntimeException(
            'Database connection failed. Check DB_HOST/DB_NAME/DB_USER/DB_PASS in config.php. ' .
            '(' . $e->getMessage() . ')'
        );
    }

    return $pdo;
}

/**
 * Returns true if the database is reachable and the accounts table exists.
 * Used on the login page to show a setup notice if the schema hasn't been run.
 */
function dbIsReady(): bool
{
    try {
        $db = getDb();
        $db->query("SELECT 1 FROM `accounts` LIMIT 1");
        return true;
    } catch (Throwable) {
        return false;
    }
}
