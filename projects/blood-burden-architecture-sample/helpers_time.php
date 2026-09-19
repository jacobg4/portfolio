<?php
// ════════════════════════════════════════════════════════════════════
//  TIME OF DAY & SLEEP SYSTEM
// ════════════════════════════════════════════════════════════════════

/** Ordered time periods in a day. */
const TIME_ORDER = ['morning', 'midday', 'afternoon', 'night'];

/** Exhaustion thresholds (periods awake without sleep). */
const EXHAUSTION_TIRED      = 8;   // Tired — warning only
const EXHAUSTION_EXHAUSTED  = 12;  // Exhausted — −1 to all rolls
const EXHAUSTION_COLLAPSING = 16;  // Collapsing — blocked from most actions

/**
 * Icon/label pair for each time of day.
 */
function timeOfDayInfo(string $tod): array
{
    return match($tod) {
        'morning'   => ['icon' => '🌅', 'label' => 'Morning',   'class' => 'tod-morning'],
        'midday'    => ['icon' => '☀️',  'label' => 'Midday',    'class' => 'tod-midday'],
        'afternoon' => ['icon' => '🌤️', 'label' => 'Afternoon', 'class' => 'tod-afternoon'],
        'night'     => ['icon' => '🌙', 'label' => 'Night',     'class' => 'tod-night'],
        default     => ['icon' => '🕐', 'label' => ucfirst($tod), 'class' => 'tod-morning'],
    };
}

/**
 * Advance time by $periods time-period steps.
 * Handles day rollover (night → morning = new day) and annual aging rolls.
 *
 * Returns an aging result array if a year rolled over, else null.
 */

// ─── Calendar ────────────────────────────────────────────────────────────────

/**
 * Convert game_day + character age into a real calendar date.
 *
 * The world epoch is June 6th, 1026. All characters are born in year 1026,
 * so the current year = 1026 + age. game_day 0 = June 6 of that year.
 *
 * Returns: ['day'=>int, 'month'=>string, 'month_short'=>string, 'year'=>int, 'display'=>string]
 */
function getCalendarDate(Character $character): array
{
    // June 6 = day index 156 in a 0-based 365-day year
    // (31+28+31+30+31 = 151 days before June, +5 for Jun 1-5 = 156)
    $startDayOfYear = 156;

    $months = [
        ['January',   'Jan', 31], ['February', 'Feb', 28], ['March',    'Mar', 31],
        ['April',     'Apr', 30], ['May',       'May', 31], ['June',     'Jun', 30],
        ['July',      'Jul', 31], ['August',    'Aug', 31], ['September','Sep', 30],
        ['October',   'Oct', 31], ['November',  'Nov', 30], ['December', 'Dec', 31],
    ];

    $absoluteDay = $startDayOfYear + $character->game_day;
    $yearOffset  = intdiv($absoluteDay, 365);
    $dayOfYear   = $absoluteDay % 365;  // 0-based within the year
    $currentYear = 1026 + $character->age + $yearOffset;

    $dayNum    = 1;
    $monthName = 'June';
    $monthShort= 'Jun';
    $remaining = $dayOfYear;
    foreach ($months as [$name, $short, $days]) {
        if ($remaining < $days) {
            $dayNum     = $remaining + 1;
            $monthName  = $name;
            $monthShort = $short;
            break;
        }
        $remaining -= $days;
    }

    return [
        'day'         => $dayNum,
        'month'       => $monthName,
        'month_short' => $monthShort,
        'year'        => $currentYear,
        'display'     => "{$dayNum} {$monthName}, {$currentYear}",
    ];
}

function advanceTime(Character $character, int $periods = 1): ?array
{
    $agingResult = null;

    for ($i = 0; $i < $periods; $i++) {
        $character->periods_awake++;
        $character->periods_without_food++;

        $idx = array_search($character->time_of_day, TIME_ORDER, true);
        if ($idx === false) $idx = 0;

        if ($idx >= 3) {
            // Night → Morning: new day begins
            $character->time_of_day = 'morning';
            $character->game_day++;

            // Sleep deprivation drain: every 4 periods once past 16 (4 days without sleep)
            if ($character->periods_awake >= 16 && $character->periods_awake % 4 === 0) {
                applyDeprivationDrain($character, 'exhaustion');
            }

            // Food deprivation drain: every 4 periods once past 32 (8 days without food)
            if ($character->periods_without_food >= 32 && $character->periods_without_food % 4 === 0) {
                applyDeprivationDrain($character, 'starvation');
            }

            // Monthly income payout: every 30 days, credit pensions + assets
            if ($character->game_day > 0 && $character->game_day % 30 === 0) {
                $monthlyIncome = 0;
                foreach ($character->pensions as $p) $monthlyIncome += (int)($p['monthly_value'] ?? 0);
                foreach ($character->assets   as $a) $monthlyIncome += (int)($a['monthly_value'] ?? 0);
                if ($monthlyIncome > 0) {
                    $character->money += $monthlyIncome;
                    $character->adventure_journal[] = [
                        'text'      => "Month {$character->game_day}: Income payment — +{$monthlyIncome} silver from pensions and assets.",
                        'timestamp' => date('c'),
                        'auto'      => true,
                    ];
                    $_SESSION['adv_notices'][] = "Monthly income received: +{$monthlyIncome} silver.";
                }
            }

            // Annual aging roll: every 365 days, age by 1 year
            if ($character->game_day > 0 && $character->game_day % 365 === 0) {
                $character->age++;
                if (shouldRollAging($character)) {
                    $agingResult = rollAgingCheck($character);
                    $yr = (int)floor($character->game_day / 365);
                    $character->adventure_journal[] = [
                        'text'      => "Year {$yr}: A year passes. Aging — {$agingResult['desc']} (2d6={$agingResult['roll']}, −{$agingResult['penalty']} → {$agingResult['adjusted']}).",
                        'timestamp' => date('c'),
                        'auto'      => true,
                    ];
                    $hasEffect = ($agingResult['phys_by_2'] + $agingResult['phys_by_1'] + $agingResult['mental_by_1']) > 0;
                    if ($hasEffect) {
                        $_SESSION['pending_aging'] = array_merge($agingResult, ['context' => 'adventure', 'age' => $character->age]);
                    } else {
                        $character->history[] = "Age {$character->age}: Annual aging check — no effect.";
                    }
                }
            }
        } else {
            $character->time_of_day = TIME_ORDER[$idx + 1];
        }
    }

    // Tick PC companion hunger and exhaustion counters (batch: one DB op per companion)
    foreach ($character->companions as $comp) {
        $uuid = $comp['character_uuid'] ?? null;
        if (!$uuid) continue;
        $c = loadCharacterFromDb($uuid);
        if (!$c) continue;
        $c->periods_awake        = min($c->periods_awake + $periods, 200);
        $c->periods_without_food = min($c->periods_without_food + $periods, 200);
        saveCharacter($c);
    }

    return $agingResult;
}

/**
 * Drain one point from a physical stat due to deprivation (Endurance → Strength → Agility).
 */
function applyDeprivationDrain(Character $character, string $cause): void
{
    $order = ['Endurance', 'Strength', 'Agility'];
    foreach ($order as $stat) {
        if (($character->stats[$stat] ?? 0) > 0) {
            $character->stats[$stat]--;
            $character->adventure_journal[] = [
                'text'      => ucfirst($cause) . " is taking its toll. {$stat} reduced by 1.",
                'timestamp' => date('c'),
                'auto'      => true,
            ];
            break;
        }
    }

    // Check if all physical stats are now 0
    $allGone = ($character->stats['Strength'] ?? 1) <= 0
            && ($character->stats['Endurance'] ?? 1) <= 0
            && ($character->stats['Agility'] ?? 1) <= 0;

    if ($allGone) {
        $causeLabel = $cause === 'starvation' ? 'Died of starvation.' : 'Died of exhaustion.';
        handleAdventureModeDeath($character, $causeLabel);
    }
}

/**
 * Perform a sleep action.
 *
 * Restores lost physical stats:
 *   - With inn room (has_inn_room = true): full recovery to stats_max
 *   - Without room (rough sleep): floor((max − cur) / 2) + cur
 *   - At temple infirmary: same as inn room (bonus: full)
 *
 * Resets periods_awake to 0.
 * Advances to morning of the next day.
 * Triggers an aging roll if a year boundary is crossed.
 *
 * Returns array: ['restored'=>[stat=>delta,...], 'had_room'=>bool, 'aging'=>result|null]
 */
function doSleep(Character $character, bool $fullRest = false): array
{
    $hasRoom   = $character->has_inn_room || $fullRest;
    $restored  = [];

    foreach (['Strength', 'Agility', 'Endurance'] as $stat) {
        $cur = (int)($character->stats[$stat] ?? 0);
        $max = (int)($character->stats_max[$stat] ?? $cur);
        if ($cur < $max) {
            $newVal = $hasRoom
                ? $max
                : (int)floor(($max - $cur) / 2 + $cur);
            if ($newVal > $cur) {
                $restored[$stat]          = $newVal - $cur;
                $character->stats[$stat]  = $newVal;
            }
        }
    }

    // Advance time to morning of next day
    $character->time_of_day  = 'morning';
    $character->periods_awake        = 0;
    $character->periods_without_food = 0; // sleeping assumes the character has eaten
    $character->has_inn_room         = false;

    // Increment day counter (sleeping always costs one day)
    $character->game_day++;
    $agingResult = null;
    if ($character->game_day > 0 && $character->game_day % 365 === 0) {
        $character->age++;
        if (shouldRollAging($character)) {
            $agingResult = rollAgingCheck($character);
            $yr = (int)floor($character->game_day / 365);
            $character->adventure_journal[] = [
                'text'      => "Year {$yr}: A year passes in your sleep. Aging — {$agingResult['desc']} (2d6={$agingResult['roll']}, −{$agingResult['penalty']} → {$agingResult['adjusted']}).",
                'timestamp' => date('c'),
                'auto'      => true,
            ];
            $hasEffect = ($agingResult['phys_by_2'] + $agingResult['phys_by_1'] + $agingResult['mental_by_1']) > 0;
            if ($hasEffect) {
                $_SESSION['pending_aging'] = array_merge($agingResult, ['context' => 'adventure', 'age' => $character->age]);
            } else {
                $character->history[] = "Age {$character->age}: Annual aging check — no effect.";
            }
        }
    }

    // Sleep PC companions: restore stats, reset counters, advance day
    foreach ($character->companions as $comp) {
        $uuid = $comp['character_uuid'] ?? null;
        if (!$uuid) continue;
        $c = loadCharacterFromDb($uuid);
        if (!$c) continue;
        $compFull = $fullRest || $c->has_inn_room;
        foreach (['Strength', 'Agility', 'Endurance'] as $stat) {
            $cur = (int)($c->stats[$stat] ?? 0);
            $max = (int)($c->stats_max[$stat] ?? $cur);
            if ($cur < $max) {
                $c->stats[$stat] = $compFull ? $max : (int)floor(($max - $cur) / 2 + $cur);
            }
        }
        $c->periods_awake        = 0;
        $c->periods_without_food = 0;
        $c->has_inn_room         = false;
        $c->time_of_day          = 'morning';
        $c->game_day++;
        saveCharacter($c);
    }

    return [
        'restored' => $restored,
        'had_room' => $hasRoom,
        'aging'    => $agingResult,
    ];
}

/**
 * Exhaustion level based on periods awake without sleep.
 * 0 = fine, 1 = tired, 2 = exhausted, 3 = collapsing
 */
function getExhaustionLevel(Character $character): int
{
    $p = $character->periods_awake;
    if ($p < EXHAUSTION_TIRED)      return 0;
    if ($p < EXHAUSTION_EXHAUSTED)  return 1;
    if ($p < EXHAUSTION_COLLAPSING) return 2;
    return 3;
}

/**
 * Bump the character up exactly one exhaustion level.
 * Rested→Tired→Exhausted→Collapsing. Already collapsing: +4 periods.
 */
function incrementExhaustionLevel(Character &$character): void
{
    foreach ([EXHAUSTION_TIRED, EXHAUSTION_EXHAUSTED, EXHAUSTION_COLLAPSING] as $thresh) {
        if ($character->periods_awake < $thresh) {
            $character->periods_awake = $thresh;
            return;
        }
    }
    $character->periods_awake += 4;
}

/**
 * Human-readable exhaustion label and CSS class.
 */
function getExhaustionInfo(Character $character): array
{
    return match(getExhaustionLevel($character)) {
        0 => ['label' => 'Rested',     'class' => 'exh-fine',       'penalty' => 0],
        1 => ['label' => 'Tired',      'class' => 'exh-tired',      'penalty' => 0],
        2 => ['label' => 'Exhausted',  'class' => 'exh-exhausted',  'penalty' => -1],
        3 => ['label' => 'Collapsing', 'class' => 'exh-collapsing', 'penalty' => -2],
        default => ['label' => 'Rested', 'class' => 'exh-fine', 'penalty' => 0],
    };
}

/**
 * Venues that allow sleeping, and whether they count as full rest.
 * Key = venue_id, value = 'full' | 'rough'
 * 'full'  → same as having a private room (full stat recovery)
 * 'rough' → partial recovery (uses unconscious formula)
 */
function sleepVenues(): array
{
    return [
        'inn_common_room'   => 'rough',   // floor/shared, unless has_inn_room
        'inn_back_corridor' => 'rough',
        'village_inn'       => 'rough',   // floor unless has_inn_room
        'forest_clearing'   => 'rough',
        'road_waystation'   => 'rough',
        'temple_infirmary'  => 'full',    // temple healers, always full rest
    ];
}

/**
 * Whether the character can sleep at their current venue.
 * Also checks new-world building sleep_quality.
 */
function canSleepHere(Character $character): bool
{
    // New world: check building sleep_quality
    if (isNewWorldCity($character->current_location) && $character->current_building) {
        $building = getCharacterBuilding($character);
        if ($building) {
            return isset($building['sleep_quality']) && $building['sleep_quality'] !== null;
        }
    }
    // Legacy: check session venue
    $venueId = $_SESSION['adv_venue'] ?? null;
    if (!$venueId) return false;
    return array_key_exists($venueId, sleepVenues());
}

/**
 * Return the open time-of-day periods for a venue.
 * Empty array = open at all times.
 */
function venueOpenTimes(string $venueId): array
{
    static $gates = [
        // Markets / shops
        'market_square'      => ['morning', 'midday', 'afternoon'],
        'market_back_alleys' => ['afternoon', 'night'],   // underworld hours
        'harbor_chandlery'   => ['morning', 'midday', 'afternoon'],

        // Taverns / inns (open mid-day onward, not at dawn except for breakfast)
        'market_tavern'      => ['midday', 'afternoon', 'night'],

        // Outdoor / public (empty/dangerous at night, not locked — just a warning)
        // (These are allowed access but carry a risk note rather than a hard gate.)

        // Guild / formal business
        'guild_reception'    => ['morning', 'midday', 'afternoon'],
        'guild_meeting_room' => ['midday', 'afternoon'],

        // Military
        'keep_garrison'      => ['morning', 'midday'],

        // Noble court
        'court_antechamber'  => ['morning', 'midday'],

        // Healers
        'temple_infirmary'   => ['morning', 'midday', 'afternoon'],

        // Academic
        'scholars_library'   => ['morning', 'midday', 'afternoon'],

        // Stables (stable hands sleep)
        'inn_stable'         => ['morning', 'midday', 'afternoon'],

        // Undertown (comes alive at night)
        'undertown_drop'     => ['afternoon', 'night'],
    ];

    return $gates[$venueId] ?? [];
}

/**
 * Whether a venue is open at the given time of day.
 * Venues with no time gate are always open.
 * For new-world building IDs, delegates to isBuildingOpen() using session character state.
 */
function isVenueOpen(string $venueId, string $timeOfDay): bool
{
    $times = venueOpenTimes($venueId);
    if (empty($times)) return true;
    return in_array($timeOfDay, $times, true);
}

