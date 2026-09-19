# Blood & Burden — Architecture Sample

[Blood & Burden](https://bloodburden.labcabin.org) is a live, actively-developed game
(345+ commits, ~39,000 lines of PHP across 128 modules). The full source isn't public —
it's a data-driven game, and the quest text, NPC dialogue, world content, and combat
balance numbers effectively *are* the finished game. Publishing all of it would let
someone clone the design wholesale rather than the engineering behind it.

What's here instead is a small, representative slice of the codebase, chosen to show
architecture and code quality rather than content:

| File | What it shows |
|---|---|
| `Dice.php` | A minimal, cleanly-typed utility class. |
| `DataLoader.php` | The pattern used to load game content from JSON rather than hard-coding it. |
| `db.php` | PDO connection singleton — prepared statements, typed errors. |
| `helpers_csrf.php` | CSRF token generation/verification used on every POST handler. |
| `AccountManager.php` | Auth: bcrypt password hashing, prepared statements, and single-active-session enforcement (a new login invalidates any other session for that account). |
| `Character.php` | The core character data model — a large, carefully-documented struct-like class with explicit `toArray()`/`fromArray()` serialization and inline schema-migration handling. |
| `helpers_time.php` | The in-game calendar/time-of-day system (day rollover, exhaustion thresholds, aging). |
| `config.example.php` | A placeholder showing config shape. The real `config.php` (DB credentials, Discord webhook secret) is never committed anywhere. |

None of these files touch quests, dialogue, combat formulas, item/spell balance, or
world data — that content lives in the private repo.
