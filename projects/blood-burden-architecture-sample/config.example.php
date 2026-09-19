<?php
/**
 * Blood & Burden application configuration — EXAMPLE FILE.
 *
 * This is a placeholder showing the shape of the real config.php, which is
 * not published. Copy this to config.php and fill in real values to run the
 * app locally; never commit the filled-in version.
 */

// ── Database ────────────────────────────────────────────────────────
define('DB_HOST', 'localhost');
define('DB_PORT', '3306');
define('DB_NAME', 'bloodburden');
define('DB_USER', 'your_db_user');
define('DB_PASS', 'your_db_password');

// Maximum characters per account
define('CHAR_SLOT_LIMIT', 5);

// ── Discord webhook ─────────────────────────────────────────────────
// Used for admin notifications (Hall of Legends submissions, etc.)
// Generate your own webhook URL in Discord: Server Settings > Integrations > Webhooks
define('DISCORD_WEBHOOK_URL', 'https://discord.com/api/webhooks/your/webhook/url');
