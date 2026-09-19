<?php
// src/Character.php
class Character {
    public string $id = "";          // UUID v4, assigned once at creation
    public string $name = "";
    public int $age = 16;

    public array $stats = [
        "Strength" => 0,
        "Agility" => 0,
        "Endurance" => 0,
        "Perception" => 0,
        "Intellect" => 0,
        "Education" => 0,
        "Presence" => 0,
        "Social Standing" => 0
    ];

    /**
     * Maximum (undamaged) values for each stat. Seeded from $stats at adventure start
     * if absent. Combat damage only reduces $stats; $stats_max never changes from combat.
     */
    public array $stats_max = [];
    public string $gender = "";
    public string $heritage = "";
    public string $current_title = "Unformed";
    public array $skills = [];
    public array $items = [];

    /**
     * Explicitly worn/wielded items, keyed by slot name.
     * null means the slot is empty. Item IDs reference entries in items.json.
     * Inventory ($items) and equipment are independent: equipping does not
     * remove an item from $items.
     */
    public array $equipment = [
        'head'            => null,
        'chest'           => null,
        'hands_shoulders' => null,
        'legs_feet'       => null,
        'cloak'           => null,
        'main_hand'       => null,
        'off_hand'        => null,
    ];

    /**
     * Pre-combat formation assignment. Keyed by 'player' or 'companion_{idx}'.
     * Values: 'front_line'|'mid_line'|'support_line'|'back_line'
     * Empty string or missing key = auto (weapon-based preferred line).
     */
    public array $formation = [];
    public int $money = 0;
    public array $history = [];
    public array $notices = [];
    public array $career_history = [];
    public string $current_career = "";
    public int $terms_served = 0;
    public string $current_assignment = "";
    public int $rank = 0;
    public bool $commissioned = false;
    public bool $military_academy_graduate = false;
    public int $total_terms = 0;
    public array $connections = [];   // allies, contacts, rivals, enemies
    public array $career_stints = []; // keyed by career id; stores last assignment/rank/commissioned
    public array $pensions = [];      // each entry: ['name'=>..., 'monthly_value'=>..., 'source'=>...]
    public int $aging_terms = 0;     // legacy: number of aging rolls taken during character creation
    public int $cash_rolls_used = 0; // lifetime cap: max 3 cash rolls across all careers

    /**
     * Injury records. Each entry:
     *   [ 'severity'    => 'catastrophic'|'major'|'minor',
     *     'description' => string,          // e.g. "Shattered leg"
     *     'source'      => string,          // e.g. "Combat: wolf attack"
     *     'treated'     => bool,            // true if downgraded by a healer
     *     'original_severity' => string ]   // severity before treatment (if treated)
     */
    public array $injuries = [];

    /**
     * Current time of day. Advances as the player acts.
     * Cycle: morning → midday → afternoon → night → (sleep) → morning
     */
    public string $time_of_day = 'morning';   // 'morning'|'midday'|'afternoon'|'night'

    /**
     * Total in-game days elapsed since adventure start.
     * Every 365 days = 1 year; used to trigger annual aging rolls.
     */
    public int $game_day = 0;

    /**
     * Number of time-period advances since last sleep.
     * 0–7 = fine, 8–11 = tired, 12–15 = exhausted (−1 penalty), 16+ = collapsing.
     */
    public int $periods_awake = 0;

    /**
     * True if the character has paid for a proper room tonight.
     * Set via inn dialogue. Cleared after sleeping. Enables full stat recovery on sleep.
     */
    public bool $has_inn_room = false;

    // ---------------------------------------------------------------
    // Reputation & social identity
    // ---------------------------------------------------------------

    /**
     * Earned prestige from actions, quests, and events.
     * Distinct from Social Standing (inherited status).
     * 0 = unknown,  2-3 = known,  4-5 = respected,
     * 6-7 = renowned,  8-9 = celebrated,  10+ = legendary
     */
    public int $prestige = 0;

    // ── Arcane ───────────────────────────────────────────────────────
    /** Spell IDs this character has learned from hermit teachers. */
    public array $known_spells = [];

    // ── Legacy tracking ──────────────────────────────────────────────
    /** Accumulated heroic reputation: heroic deeds, titles, discoveries, charity. */
    public int $renown = 0;
    /** Accumulated dark reputation: murders, betrayals, crimes. */
    public int $infamy = 0;
    /** Set at death. */
    public string $cause_of_death = '';

    // ── Combat & achievement tracking ────────────────────────────────
    /** Number of combat encounters survived. Incremented on combat victory. */
    public int $combats_survived = 0;
    /** Number of times a lethal outcome was averted. */
    public int $deaths_averted   = 0;
    /** Total confirmed kills (enemies defeated). */
    public int $kill_count       = 0;
    /** Cumulative silver donated. */
    public int $total_donated    = 0;

    /**
     * Condition of each equipped armor slot.
     * Keys match equipment slot names; values: 'Excellent'|'Good'|'Poor'|'Damaged'|'Broken'.
     * Missing key = 'Excellent' (assumed new).
     */
    public array $armor_condition      = [];

    /**
     * Cumulative AP absorbed by each armor slot since the last condition drop.
     * Resets (mod 5) when a condition step is lost. Used to track degradation threshold.
     */
    public array $armor_ap_accumulated = [];

    /**
     * Remaining uses for multi-use items, keyed by item ID.
     * e.g. ['repair_kit' => 3]  — item stays in $items until uses hit 0.
     */
    public array $item_uses = [];

    /**
     * Items stowed inside the character's pack (backpack_leather or equivalent).
     * Separate from $items (which holds everything carried on the body).
     * Both $items and $pack_items count toward total carried weight.
     * The pack has its own capacity enforced at stow time.
     */
    public array $pack_items = [];

    // ── Deprivation tracking ─────────────────────────────────────────
    /** Periods elapsed since last meal. Resets when character eats. */
    public int $periods_without_food = 0;

    /**
     * True when the character has food poisoning from eating raw meat/fish.
     * Imposes −2 Endurance until treated with a medicine check (DC 8).
     */
    public bool $has_food_poisoning = false;

    /**
     * Background flags representing who the character is and how the world reads them.
     * Set by heritage, career history, events, and quest outcomes.
     * Examples: noble_born, former_criminal, decorated_veteran, academy_privilege_entry
     */
    public array $background_flags = [];

    // ── Criminal record ───────────────────────────────────────────────
    /** True when convicted of killing a guard. Affects NPC and guard reactions globally. */
    public bool $fugitive = false;
    /** Location IDs where the character is actively wanted (guards will arrest on sight). */
    public array $wanted_in = [];
    /**
     * Stolen item IDs keyed by the location ID where they were stolen.
     * e.g. ['harrowport' => ['royal_charter', 'ledger']]
     * Guards in Millhaven won't know about goods stolen in Harrowport.
     */
    public array $stolen_items = [];
    /**
     * Accumulated criminal charges per location ID.
     * e.g. ['harrowport' => ['guards_killed' => 2, 'base_days' => 1]]
     * Used to reconstruct the arrest sentence when caught by a patrol.
     */
    public array $wanted_details = [];

    // ---------------------------------------------------------------
    // Adventure mode
    // ---------------------------------------------------------------
    public bool  $adventure_mode    = false; // true once character creation is finalised
    public array $quests            = [];    // quest objects (see Quest structure in helpers.php)
    public array $adventure_journal = [];    // ['text'=>..., 'timestamp'=>...] entries
    public string $active_quest_id  = '';    // ID of the first tracked quest (backward compat)
    public array  $tracked_quest_ids = [];   // up to 3 tracked IDs; index 0=red 1=blue 2=green
    public string $current_location = '';    // current location ID
    public string $current_district = '';   // current district ID (new world system)
    public string $current_building = '';   // current building ID (new world system)
    public string $current_room     = '';   // current room ID (new world system)

    /**
     * Unique NPC IDs the player has spoken to (used for quest objective tracking).
     */
    public array $npcs_talked_to    = [];

    /**
     * Owned assets that generate monthly income.
     * Converted from 10 shares of the same type.
     * Each entry: ['type'=>string, 'name'=>string, 'monthly_value'=>int, 'source'=>string]
     */
    public array $assets = [];

    /**
     * NPC companions traveling with the character.
     * Each entry: ['id'=>string, 'name'=>string, 'stats'=>['Perception'=>int,...],
     *              'skills'=>['investigation'=>int,'stealth'=>int,...]]
     */
    public array $companions        = [];

    // ---------------------------------------------------------------
    // UUID helper
    // ---------------------------------------------------------------

    public static function generateId(): string
    {
        $data = random_bytes(16);
        $data[6] = chr((ord($data[6]) & 0x0f) | 0x40); // version 4
        $data[8] = chr((ord($data[8]) & 0x3f) | 0x80); // variant RFC 4122
        return vsprintf('%s%s-%s-%s-%s-%s%s%s', str_split(bin2hex($data), 4));
    }

    // ---------------------------------------------------------------
    // Serialisation — for file saves / export
    // ---------------------------------------------------------------

    public function toArray(): array
    {
        return [
            'id'                       => $this->id,
            'name'                     => $this->name,
            'age'                      => $this->age,
            'stats'                    => $this->stats,
            'stats_max'                => $this->stats_max,
            'gender'                   => $this->gender,
            'heritage'                 => $this->heritage,
            'current_title'            => $this->current_title,
            'skills'                   => $this->skills,
            'items'                    => $this->items,
            'equipment'                => $this->equipment,
            'money'                    => $this->money,
            'history'                  => $this->history,
            'notices'                  => $this->notices,
            'career_history'           => $this->career_history,
            'current_career'           => $this->current_career,
            'terms_served'             => $this->terms_served,
            'current_assignment'       => $this->current_assignment,
            'rank'                     => $this->rank,
            'commissioned'             => $this->commissioned,
            'military_academy_graduate'=> $this->military_academy_graduate,
            'total_terms'              => $this->total_terms,
            'connections'              => $this->connections,
            'career_stints'            => $this->career_stints,
            'pensions'                 => $this->pensions,
            'aging_terms'              => $this->aging_terms,
            'injuries'                 => $this->injuries,
            'time_of_day'              => $this->time_of_day,
            'game_day'                 => $this->game_day,
            'periods_awake'            => $this->periods_awake,
            'has_inn_room'             => $this->has_inn_room,
            'prestige'                 => $this->prestige,
            'background_flags'         => $this->background_flags,
            'adventure_mode'           => $this->adventure_mode,
            'quests'                   => $this->quests,
            'adventure_journal'        => $this->adventure_journal,
            'active_quest_id'          => $this->active_quest_id,
            'current_location'         => $this->current_location,
            'current_district'         => $this->current_district,
            'current_building'         => $this->current_building,
            'current_room'             => $this->current_room,
            'npcs_talked_to'           => $this->npcs_talked_to,
            'companions'               => $this->companions,
            'assets'                   => $this->assets,
            'renown'                   => $this->renown,
            'infamy'                   => $this->infamy,
            'cause_of_death'           => $this->cause_of_death,
            'periods_without_food'     => $this->periods_without_food,
            'has_food_poisoning'       => $this->has_food_poisoning,
            'combats_survived'         => $this->combats_survived,
            'deaths_averted'           => $this->deaths_averted,
            'kill_count'               => $this->kill_count,
            'total_donated'            => $this->total_donated,
            'armor_condition'          => $this->armor_condition,
            'armor_ap_accumulated'     => $this->armor_ap_accumulated,
            'item_uses'                => $this->item_uses,
            'pack_items'               => $this->pack_items,
            'fugitive'                 => $this->fugitive,
            'wanted_in'                => $this->wanted_in,
            'stolen_items'             => $this->stolen_items,
            'wanted_details'           => $this->wanted_details,
            'formation'                => $this->formation,
        ];
    }

    public static function fromArray(array $data): self
    {
        $c = new self();
        $c->id                        = $data['id']                        ?? self::generateId();
        $c->name                      = $data['name']                      ?? '';
        $c->age                       = (int)($data['age']                 ?? 16);
        $c->stats                     = $data['stats']                     ?? $c->stats;
        $c->stats_max                 = $data['stats_max']                 ?? [];
        $c->gender                    = $data['gender']                    ?? '';
        $c->heritage                  = $data['heritage']                  ?? '';
        $c->current_title             = $data['current_title']             ?? 'Unformed';
        $c->skills                    = $data['skills']                    ?? [];
        $c->items                     = $data['items']                     ?? [];
        $c->equipment                 = array_merge($c->equipment, $data['equipment'] ?? []);
        // Schema migration v2: if legacy 'shield' slot key exists, clear all equipment
        if (array_key_exists('shield', $c->equipment)) {
            $c->equipment = defaultEquipment();
        }
        $c->money                     = (int)($data['money']               ?? 0);
        $c->history                   = $data['history']                   ?? [];
        $c->notices                   = $data['notices']                   ?? [];
        $c->career_history            = $data['career_history']            ?? [];
        $c->current_career            = $data['current_career']            ?? '';
        $c->terms_served              = (int)($data['terms_served']        ?? 0);
        $c->current_assignment        = $data['current_assignment']        ?? '';
        $c->rank                      = (int)($data['rank']                ?? 0);
        $c->commissioned              = (bool)($data['commissioned']       ?? false);
        $c->military_academy_graduate = (bool)($data['military_academy_graduate'] ?? false);
        $c->total_terms               = (int)($data['total_terms']         ?? 0);
        $c->connections               = $data['connections']               ?? [];
        $c->career_stints             = $data['career_stints']             ?? [];
        $c->pensions                  = $data['pensions']                  ?? [];
        $c->aging_terms               = (int)($data['aging_terms']         ?? 0);
        $c->injuries                  = $data['injuries']                  ?? [];
        $c->time_of_day               = $data['time_of_day']               ?? 'morning';
        $c->game_day                  = (int)($data['game_day']            ?? 0);
        $c->periods_awake             = (int)($data['periods_awake']       ?? 0);
        $c->has_inn_room              = (bool)($data['has_inn_room']       ?? false);
        $c->prestige                  = (int)($data['prestige']             ?? 0);
        $c->background_flags          = $data['background_flags']           ?? [];
        $c->adventure_mode            = (bool)($data['adventure_mode']     ?? false);
        $c->quests                    = $data['quests']                    ?? [];
        $c->adventure_journal         = $data['adventure_journal']         ?? [];
        $c->active_quest_id           = $data['active_quest_id']           ?? '';
        $c->current_location          = $data['current_location']          ?? '';
        $c->current_district          = $data['current_district']          ?? '';
        $c->current_building          = $data['current_building']          ?? '';
        $c->current_room              = $data['current_room']              ?? '';
        $c->npcs_talked_to            = $data['npcs_talked_to']            ?? [];
        $c->companions                = $data['companions']                ?? [];
        $c->assets                    = $data['assets']                    ?? [];
        $c->renown                    = (int)($data['renown']               ?? 0);
        $c->infamy                    = (int)($data['infamy']               ?? 0);
        $c->cause_of_death            = $data['cause_of_death']             ?? '';
        $c->periods_without_food      = (int)($data['periods_without_food'] ?? 0);
        $c->has_food_poisoning        = (bool)($data['has_food_poisoning']  ?? false);
        $c->known_spells              = $data['known_spells']                ?? [];
        $c->combats_survived          = (int)($data['combats_survived']      ?? 0);
        $c->deaths_averted            = (int)($data['deaths_averted']        ?? 0);
        $c->kill_count                = (int)($data['kill_count']            ?? 0);
        $c->total_donated             = (int)($data['total_donated']         ?? 0);
        $c->armor_condition           = $data['armor_condition']             ?? [];
        $c->armor_ap_accumulated      = $data['armor_ap_accumulated']        ?? [];
        $c->item_uses                 = $data['item_uses']                   ?? [];
        $c->pack_items                = $data['pack_items']                  ?? [];
        $c->fugitive                  = (bool)($data['fugitive']             ?? false);
        $c->wanted_in                 = $data['wanted_in']                   ?? [];
        // Migrate old flat ['itemId', ...] format to location-keyed ['locId' => ['itemId']]
        $rawStolen = $data['stolen_items'] ?? [];
        $c->stolen_items = (array_values($rawStolen) === $rawStolen && !empty($rawStolen) && is_string(reset($rawStolen)))
            ? []
            : $rawStolen;
        $c->wanted_details            = $data['wanted_details']              ?? [];
        $c->formation                 = $data['formation']                   ?? [];
        return $c;
    }
}