import random
import json
import os

SAVE_FILE = "save_data.json"

QUEST_FILE = "quests.json"

MONSTER_FILE = "monsters.json"

DUNGEON_FILE = "dungeons.json"

ITEMS_FILE = "items.json"

ADVENTURES_FILE = "adventures.json"

def load_adventures():
    if not os.path.exists(ADVENTURES_FILE):
        print("❌ Adventures file not found! Make sure adventures.json is in the same directory.")
        return {"adventures": []}

    with open(ADVENTURES_FILE, "r", encoding="utf-8") as f:
        return json.load(f)

adventure_data = load_adventures()

def start_adventure():
    if not adventure_data["adventures"]:
        print("❌ No adventures available.")
        return

    adventure = random.choice(adventure_data["adventures"])
    print(f"\n🗺️ {adventure['title']}")
    print(f"{adventure['intro']}")
    
    current_path = "entrance"  # Always starts at the 'entrance' node
    while current_path:
        encounter = adventure["paths"][current_path]
        print(f"\n{encounter['description']}")

        # Handle Choices
        if "choices" in encounter:
            print("Your options:")
            for choice in encounter["choices"]:
                print(f" - {choice}")
            
            selected_choice = input("What do you choose? ").strip().lower()
            result = encounter["choices"].get(selected_choice)

            if isinstance(result, dict):  # Result may include rewards or penalties
                print(result.get("result", "Nothing notable happens."))
                if "reward" in result:
                    apply_rewards(result["reward"])
                if "penalty" in result:
                    apply_penalty(result["penalty"])

                current_path = result.get("next")
            else:
                current_path = encounter["next"].get(selected_choice)
        
        # Handle Combat Encounters
        elif encounter.get("type") == "combat":
            enemy = generate_monster(encounter["enemy"])
            fight(enemy)
            current_path = encounter.get("next")
        
        # Handle Endings
        elif "ending" in encounter:
            print(f"\n🏁 {encounter['ending']}")
            return
        
        else:
            print("❌ An unexpected error occurred. Returning to the surface.")
            return

def apply_rewards(reward):
    if "gold" in reward:
        player_data["stats"]["gold"] += reward["gold"]
        print(f"💰 Gained {reward['gold']} gold!")
    if "xp" in reward:
        player_data["stats"]["xp"] += reward["xp"]
        print(f"✨ Gained {reward['xp']} XP!")
        check_level_up()

def apply_penalty(penalty):
    if "health" in penalty:
        player_data["stats"]["health"] -= penalty["health"]
        print(f"💔 Lost {penalty['health']} HP!")
        if player_data["stats"]["health"] <= 0:
            game_over()
def handle_adventure_encounter(encounter):
    print(f"\n{encounter['description']}")

    if encounter["type"] == "combat":
        enemy = generate_monster(encounter["enemy"])
        fight(enemy)
    elif encounter["type"] == "puzzle":
        answer = input("Enter the solution: ").strip().upper()
        if answer == encounter["solution"]:
            print("✅ Correct! The puzzle unlocks a new path.")
        else:
            print("❌ Incorrect answer. The puzzle remains unsolved.")
    elif encounter["type"] == "dialogue":
        print("Your choices:")
        for choice in encounter["choices"]:
            print(f" - {choice}")
        choice = input("What do you choose? ").strip().lower()
        result = encounter["choices"].get(choice, "Nothing happens.")
        if isinstance(result, dict):
            print(result.get("result", "Your decision had an unexpected outcome."))
        else:
            print(result)
def load_items():
    if not os.path.exists(ITEMS_FILE):
        print("❌ Items file not found! Make sure items.json is in the same directory.")
        return {"weapons": {}, "armor": {}, "potions": {}}

    with open(ITEMS_FILE, "r", encoding="utf-8") as f:
        return json.load(f)

item_data = load_items()

dungeon_active = False

def load_dungeons():
    if not os.path.exists(DUNGEON_FILE):
        print("❌ Dungeons file not found! Make sure dungeons.json is in the same directory.")
        return {"dungeons": []}

    with open(DUNGEON_FILE, "r", encoding="utf-8") as f:
        return json.load(f)

dungeon_data = load_dungeons()

def enter_dungeon():
    global dungeon_active

    dungeon = random.choice(dungeon_data["dungeons"])
    print(f"🏰 You have discovered a dungeon: {dungeon['name']}!")

    # Display a teaser encounter (e.g., a trap, room, or puzzle as a preview)
    encounter_type = random.choice(["traps", "rooms", "corridors"])
    encounter = random.choice(dungeon_data["encounters"][encounter_type])
    
    print(f"📜 As you approach, you notice: {encounter['description']}")
    
    choice = input("Do you wish to enter? (yes/no): ").strip().lower()

    if choice == "yes":
        print(f"⚔️ You bravely enter the {dungeon['name']}...")
        dungeon_active = True
        explore_dungeon(dungeon)
    else:
        print("🏃 You decide to leave the dungeon alone.")

def explore_dungeon(dungeon):
    global dungeon_active
    print(f"📜 Entering {dungeon['name']}...")

    # Randomly pull encounters
    for _ in range(dungeon["num_traps"]):
        trap = random.choice(dungeon_data["encounters"]["traps"])
        print(f"🪤 {trap['description']} You lose {trap['damage']} HP!")
        player_data['stats']['health'] -= trap['damage']

    for _ in range(dungeon["num_puzzles"]):
        puzzle = random.choice(dungeon_data["encounters"]["puzzles"])
        print(f"🧩 Puzzle Encounter: {puzzle['description']}")

        if "question" in puzzle:
            answer = input(f"❓ {puzzle['question']} ").strip().lower()
            if answer == puzzle.get('answer', '').strip().lower():
                print("✅ Correct! The puzzle unlocks a new path forward.")
            else:
                print("❌ Incorrect answer! The puzzle remains unsolved.")
        
        elif "pattern" in puzzle:
            print(f"🧩 The lock shows symbols: {' - '.join(puzzle['pattern'])}")
            pattern_guess = input("Enter the symbols in order (e.g., circle triangle square): ").strip().lower()
            if pattern_guess == ' '.join(puzzle['pattern']).lower():
                print("✅ The symbols align perfectly! The door opens.")
            else:
                print("❌ The symbols misalign! The path remains blocked.")
        else:
            print("❓ This puzzle seems unsolvable... Maybe something else will trigger it.")

    for _ in range(dungeon["num_rooms"]):
        room = random.choice(dungeon_data["encounters"]["rooms"])
        print(f"🚪 {room['description']}")

        if room["type"] == "combat":
            enemy = generate_monster(room["enemy"])
            fight(enemy)
        elif room["type"] == "treasure":
            player_data['stats']['gold'] += room["gold"]
            print(f"💰 You found {room['gold']} gold!")
        elif room["type"] == "loot":
            add_to_inventory(room["item"])
            print(f"🎁 Found loot: {room['item']}")

    for _ in range(dungeon["num_corridors"]):
        corridor = random.choice(dungeon_data["encounters"]["corridors"])
        print(f"🌫️ {corridor['description']}")

    if dungeon["boss"]:
        boss = random.choice(dungeon_data["encounters"]["boss_fights"])
        print(f"🔥 Boss Encounter: {boss['description']}")
        enemy = generate_monster(boss["enemy"])
        fight(enemy)

    print(f"🎯 Dungeon Complete! You found {dungeon['reward']['gold']} gold and gained {dungeon['reward']['xp']} XP!")
    player_data['stats']['gold'] += dungeon['reward']['gold']
    player_data['stats']['xp'] += dungeon['reward']['xp']

    if 'item' in dungeon['reward']:
        add_to_inventory(dungeon['reward']['item'])

    dungeon_active = False
    check_level_up()

def load_monsters():
    if not os.path.exists(MONSTER_FILE):
        print("❌ Monsters file not found! Make sure monsters.json is in the same directory.")
        return {"monsters": []}

    with open(MONSTER_FILE, "r", encoding="utf-8") as f:  # 🔥 Force UTF-8 encoding
        return json.load(f)

monster_data = load_monsters()

# New function for purchasing stat upgrades
def upgrade_stats():
    print("\n💪 Welcome to the Training Grounds! 💪")
    print(f"💰 You have {player_data['stats']['gold']} gold.")

    print("Available Upgrades:")
    print("1️⃣ Increase Power (+1) - 500 Gold")
    print("2️⃣ Increase Defense (+1) - 500 Gold")
    print("3️⃣ Increase Max Health (+10) - 400 Gold")
    print("4️⃣ Increase Max Mana (+10) - 200 Gold")
    print("5️⃣ Exit Training Grounds")

    while True:
        choice = input("Choose an upgrade (1/2/3) or '4' to leave: ").strip()
        if choice == "1" and player_data['stats']['gold'] >= 500:
            player_data['stats']['power'] += 1
            player_data['stats']['gold'] -= 500
            print("✅ Power increased by 1!")
        elif choice == "2" and player_data['stats']['gold'] >= 500:
            player_data['stats']['defense'] += 1
            player_data['stats']['gold'] -= 500
            print("✅ Defense increased by 1!")
        elif choice == "3" and player_data['stats']['gold'] >= 400:
            player_data['stats']['health'] += 10
            player_data['stats']['gold'] -= 400
            print("✅ Max Health increased by 10!")
        elif choice == "4" and player_data['stats']['gold'] >= 200:
            player_data['stats']['mana'] += 10
            player_data['stats']['gold'] -= 200
            print("✅ Max Health increased by 10!")
        elif choice == "5":
            print("🏋️ Training session complete!")
            break
        else:
            print("❌ Invalid choice or insufficient gold.")

    save_game()
    
def load_quests():
    if not os.path.exists(QUEST_FILE):
        print("❌ Quests file not found! Make sure quests.json is in the same directory.")
        return {"quests": []}

    with open(QUEST_FILE, "r") as f:
        return json.load(f)

quest_data = load_quests()

player_data = {
    "name": "",
    "progress": 0,
    "inventory": ["dagger", "armor, light"],
    "quest_items": [],  # Separate list for quest items
    "equipped": {"weapon": None, "armor": None, "amulet": None, "ring": None},
    "stats": {"health": 100, "max_health": 100, "mana": 100, "max_mana": 100, "power": 1, "defense": 1, "gold": 0, "xp": 0},
    "quest_log": []  # Track active quests
}

def generate_monster(enemy_id=None):
    if not monster_data["monsters"]:
        print("❌ No monsters available!")
        return None

    if enemy_id:
        monster_template = next((m for m in monster_data["monsters"] if m["id"] == enemy_id), None)
        if not monster_template:
            print(f"❌ Error: Monster ID '{enemy_id}' not found. Generating a random monster instead.")
            monster_template = random.choice(monster_data["monsters"])
    else:
        monster_template = random.choice(monster_data["monsters"])

    # Scale monster difficulty based on player progress
    monster = {
        "id": monster_template["id"],
        "name": monster_template["name"],
        "health": monster_template["base_health"] + (player_data["progress"] * 3),
        "power": monster_template["base_power"] + (player_data["progress"] // 2),
        "defense": monster_template["base_defense"] + (player_data["progress"] // 3),
        "ability": monster_template["ability"],
        "loot": monster_template["loot"],
        "dialogue": random.choice(monster_template["dialogue"])  # Pick a random line
    }
    return monster


def activate_enemy_ability(enemy):
    if enemy["ability"] == "steal":
        stolen_gold = random.randint(5, 15)
        player_data["stats"]["gold"] = max(0, player_data["stats"]["gold"] - stolen_gold)
        print(f"💰 The {enemy['name']} steals {stolen_gold} gold from you!")

    elif enemy["ability"] == "dodge":
        if random.randint(1, 3) == 1:  # 33% chance to dodge
            print(f"⚡ The {enemy['name']} dodges your attack!")

    elif enemy["ability"] == "resurrect":
        if enemy["health"] <= 0 and random.randint(1, 4) == 1:  # 25% chance to revive
            enemy["health"] = 15
            print(f"🦴 The {enemy['name']} resurrects with 15 HP!")

    elif enemy["ability"] == "berserk":
        if enemy["health"] < 20:
            enemy["power"] += 3
            print(f"💢 The {enemy['name']} enters a rage, increasing its attack!")

    elif enemy["ability"] == "fireball":
        if random.randint(1, 3) == 1:  # 33% chance to cast fireball
            fireball_damage = random.randint(10, 20)
            player_data["stats"]["health"] -= fireball_damage
            print(f"🔥 The {enemy['name']} casts a fireball, dealing {fireball_damage} damage!")

    elif enemy["ability"] == "curse":
        if random.randint(1, 3) == 1:  # 33% chance to curse
            drain = int(player_data["stats"]["power"] * 0.10)
            player_data["stats"]["power"] -= drain
            print(f"💀 You have been cursed, your power has been drained by {drain}!")

    elif enemy["ability"] == "power_strike":
        if random.randint(1, 5) == 1:  # 20% chance to power strike
            strike_damage = random.randint(20, 40)
            player_data["stats"]["health"] -= strike_damage
            print(f"💥 The {enemy['name']} unleashes a devastating Power Strike, dealing {strike_damage} damage!")

    elif enemy["ability"] == "firestorm":
        if random.randint(1, 4) == 1:  # 25% chance for devastating firestorm
            firestorm_damage = random.randint(30, 50)
            player_data["stats"]["health"] -= firestorm_damage
            print(f"🔥🔥 The {enemy['name']} engulfs the battlefield in flames, dealing {firestorm_damage} damage!")

    elif enemy["ability"] == "aerial_strike":
        if random.randint(1, 4) == 1:  # 25% chance to strike from above
            aerial_damage = random.randint(15, 30)
            player_data["stats"]["health"] -= aerial_damage
            print(f"🦇 The {enemy['name']} swoops down and slashes you for {aerial_damage} damage!")

    elif enemy["ability"] == "petrify":
        if random.randint(1, 4) == 1:  # 25% chance to petrify
            print(f"🐍 The {enemy['name']} gazes at you... you feel your limbs turning to stone!")
            player_data["stats"]["defense"] = max(1, player_data["stats"]["defense"] // 2)

    elif enemy["ability"] == "triple_strike":
        if random.randint(1, 3) == 1:  # 33% chance to strike three times
            for _ in range(3):
                strike_damage = random.randint(5, 10)
                player_data["stats"]["health"] -= strike_damage
                print(f"🦁🐐🐍 The {enemy['name']} strikes fiercely for {strike_damage} damage!")

    elif enemy["ability"] == "regenerate":
        if enemy["health"] > 0 and random.randint(1, 4) == 1:  # 25% chance to regenerate
            regen_amount = random.randint(20, 40)
            enemy["health"] += regen_amount
            print(f"🐉🐉🐉 The {enemy['name']} regenerates {regen_amount} health!")

    elif enemy["ability"] == "earthquake":
        if random.randint(1, 3) == 1:  # 33% chance to shake the battlefield
            quake_damage = random.randint(25, 45)
            player_data["stats"]["health"] -= quake_damage
            print(f"🏔️ The {enemy['name']} unleashes a devastating earthquake, dealing {quake_damage} damage!")

def save_game():
    with open(SAVE_FILE, "w") as f:
        json.dump(player_data, f, indent=4)
    print("Game saved!")

def load_game():
    if os.path.exists(SAVE_FILE):
        with open(SAVE_FILE, "r") as f:
            saved_data = json.load(f)
            player_data.update(saved_data)  # Update in-place for flexibility
        print(f"✅ Save data loaded successfully! Welcome back, {player_data['name']}!")
    else:
        print("❌ No saved game found. Starting a new adventure.")
   
def offer_quest():
    if player_data["quest_log"]:
        print("📜 You already have an active quest.")
        return

    quest = random.choice(quest_data["quests"])
    player_data["quest_log"].append(quest["id"])
    print(f"📜 New Quest: {quest['description']}")
    save_game()

def add_quest_item(item):
    player_data["quest_items"].append(item)
    print(f"📜 You found a {item} and added it to your quest log!")

def check_quest_completion(enemy_name=None):
    completed_quests = []
    
    for quest_id in player_data["quest_log"]:
        quest = next((q for q in quest_data["quests"] if q["id"] == quest_id), None)
        if not quest:
            continue  # Skip if quest not found

        # Fetch Quest Completion
        if quest["type"] == "fetch" and "item" in quest:
            if quest["item"] in player_data["quest_items"]:
                print(f"✅ Quest Completed: {quest['description']}")
                grant_quest_reward(quest)
                player_data["quest_items"].remove(quest["item"])  # Remove quest item after completion
                completed_quests.append(quest_id)

        # Combat Quest Completion
        elif quest["type"] == "combat" and "target" in quest and quest["target"] == enemy_name:
            quest["amount"] -= 1
            print(f"⚔️ Defeated a {quest['target']}! {quest['amount']} remaining.")
            if quest["amount"] <= 0:
                print(f"✅ Quest Completed: {quest['description']}")
                grant_quest_reward(quest)
                completed_quests.append(quest_id)

    for quest_id in completed_quests:
        player_data["quest_log"].remove(quest_id)
    
    save_game()

def grant_quest_reward(quest):
    if "gold" in quest["reward"]:
        player_data["stats"]["gold"] += quest["reward"]["gold"]
        print(f"💰 You received {quest['reward']['gold']} gold!")
    
    if "xp" in quest["reward"]:
        player_data["stats"]["xp"] += quest["reward"]["xp"]
        print(f"✨ You gained {quest['reward']['xp']} XP!")
        check_level_up()

    if "item" in quest["reward"]:
        add_to_inventory(quest["reward"]["item"])

def game_over():
    print("💀 You have perished... Game over!")
    player_data["stats"]["health"] = 100  # Restore health for respawn
    player_data["stats"]["gold"] = max(0, player_data["stats"]["gold"] - 50)  # Lose some gold
    player_data["progress"] = max(0, player_data["progress"] - 1)  # Prevent story skipping
    save_game()
    print("💤 You wake up in a nearby village, bruised but alive...")
      
def explore():
    print("\n🎲 Rolling 1d6...")
    result = roll()
    print(f"You rolled a {result}.")

    # Offer a quest if none is active
    if not player_data["quest_log"] and random.randint(1, 4) == 1:  
        offer_quest()

    event_table(result)
    save_game()

def roll():
    # Roll a six-sided die
    return random.randint(1, 6)
    
victory_messages = [
    "You strike with all your might and your foe crumples to the ground!",
    "A well-placed blow sends your enemy sprawling. Victory is yours!",
    "With a final strike, you stand triumphant over your vanquished opponent!"
]

defeat_messages = [
    "A sharp pain and then... darkness. You have fallen.",
    "Your enemy strikes true! Your journey ends here.",
    "The last thing you see is a victorious smirk before all goes black..."
]

def add_to_inventory(item):
    player_data["inventory"].append(item)
    print(f"You found a {item} and added it to your inventory!")

def use_item():
    potion = [item for item in player_data["inventory"] if "potion" in item]

    if not potion:
        print("❌ You have no potions!")
        return

    print("\n🎒 Your potions:")
    for i, item in enumerate(potion, 1):
        print(f"{i}. {item}")

    choice = input("Enter the number of the item to use (or 'cancel'): ").strip().lower()

    if choice == "cancel":
        print("❌ You chose not to use an item.")
        return

    try:
        item_index = int(choice) - 1
        if 0 <= item_index < len(potion):
            item = potion[item_index]

            if "heal" in item_data["potions"][item]:
                heal_amount = item_data["potions"][item]["heal"]
                heal(heal_amount)

            elif "regen" in item_data["potions"][item]:
                regen_amount = item_data["potions"][item]["regen"]
                restore_mana(regen_amount)

            else:
                print(f"❌ The {item} had no effect!")
            
            # Remove the used potion from inventory
            player_data["inventory"].remove(item)

        else:
            print("❌ Invalid selection.")
    except ValueError:
        print("❌ Invalid input.")

def heal(amount):
    player_data["stats"]["health"] = min(player_data["stats"]["health"] + amount, player_data["stats"]["max_health"])
    print(f"❤️ Healed for {amount} HP. Current health: {player_data['stats']['health']}/{player_data['stats']['max_health']}")

def restore_mana(amount):
    player_data["stats"]["mana"] = min(player_data["stats"]["mana"] + amount, player_data["stats"]["max_mana"])
    print(f"🔵 Mana restored by {amount}. Current mana: {player_data['stats']['mana']}/{player_data['stats']['max_mana']}")


def visit_shop():
    print("\n🛒 Welcome to the Merchant's Shop! 🏪")
    print(f"💰 You have {player_data['stats']['gold']} gold.\n")
    
    while True:
        print("\n📜 Items for Sale:")
        for category, items in item_data.items():
            for item, details in items.items():
                print(f"🔹 {item} - {details['price']} gold")

        print("\nOptions: [buy] item name, [sell] item name, show [inventory], [leave]")
        command = input("What would you like to do? ").strip().lower()

        if command == "leave":
            print("🛑 You leave the shop.")
            break
        elif command.startswith("buy "):
            item_name = command[4:].strip()
            if any(item_name in items for items in item_data.values()):
                buy_item(item_name)
            else:
                print("❌ That item isn't available!")
        elif command.startswith("sell "):
            item_name = command[5:].strip()
            if item_name in player_data["inventory"]:
                sell_item(item_name)
            else:
                print("❌ You don't have that item to sell!")
        elif command == "inventory":
            view_inventory()
        else:
            print("❌ Invalid command. Try again.")
            
def buy_item(item_name):
    for category, items in item_data.items():
        if item_name in items:
            item_details = items[item_name]
            
            if item_details['price'] > player_data['stats']['gold']:
                print("❌ You don't have enough gold!")
                return
            
            if category == "potions":
                player_data["inventory"].append(item_name)
                print(f"✅ You purchased a {item_name}!")
            
            else:
                if item_name in player_data["inventory"] or item_name in player_data["equipped"].values():
                    print(f"⚠️ Warning: You already own {item_name}.")
                    warning = input("Are you sure you would like to continue with the purchase? Yes/No")
                    if warning == "no":
                        return
                    elif warning == "yes":
                        player_data["inventory"].append(item_name)
                        print(f"✅ {item_name} added to your inventory!")
                    else:
                        print("Sorry, couldn't quite catch that")

            player_data["stats"]["gold"] -= item_details['price']
            return

    print("❌ Item not found.")
    
def equip_item():
    print("🎯 Choose an item to equip:")
    print("1️⃣ Weapon")
    print("2️⃣ Armor")
    print("3️⃣ Amulet")
    print("4️⃣ Ring")

    choice = input("Enter your choice (1/2/3/4): ").strip()

    if choice == "1":
        item_type = "weapons"
        equip_slot = "weapon"
    elif choice == "2":
        item_type = "armor"
        equip_slot = "armor"
    elif choice == "3":
        item_type = "amulets"
        equip_slot = "amulet"
    elif choice == "4":
        item_type = "rings"
        equip_slot = "ring"
    else:
        print("❌ Invalid choice.")
        return

    print(f"🛡️ Available {item_type.capitalize()}:")
    for item in item_data[item_type]:
        print(f"- {item}")

    selected_item = input("Enter the item name to equip: ").strip().lower()
    if selected_item in item_data[item_type]:
        player_data["equipped"][equip_slot] = selected_item
        print(f"✅ You equipped {selected_item}!")
    else:
        print("❌ Invalid item selection.")

def sell_item(item_name):
    for category, items in item_data.items():
        if item_name in items:
            sell_price = items[item_name]["price"] // 2
            player_data["stats"]["gold"] += sell_price
            player_data["inventory"].remove(item_name)
            print(f"💰 You sold {item_name} for {sell_price} gold.")
            save_game()
            return
    print("❌ You can't sell that item.")

def check_level_up():
    if player_data["stats"]["xp"] >= 50:
        player_data["stats"]["xp"] = 0

        # Player choice for stat upgrade with retries
        attempts = 0
        while attempts < 3:
            print("🎯 Choose a stat to increase:")
            print("1️⃣ Power (+1)")
            print("2️⃣ Defense (+1)")
            choice = input("Enter your choice (1/2): ").strip()

            if choice == "1":
                player_data["stats"]["power"] += 1
                print("💪 Power increased by 1!")
                break
            elif choice == "2":
                player_data["stats"]["defense"] += 1
                print("🛡️ Defense increased by 1!")
                break
            else:
                attempts += 1
                print(f"❌ Invalid choice. {2 - attempts + 1} attempts remaining.")
                if attempts == 3:
                    print("❌ You wasted your efforts on other affairs. No stat increase this time.")

        # Increase max health and mana, and refill both
        player_data["stats"]["max_health"] += 20
        player_data["stats"]["health"] = player_data["stats"]["max_health"]

        player_data["stats"]["max_mana"] += 20
        player_data["stats"]["mana"] = player_data["stats"]["max_mana"]

        player_data["progress"] += 1
        print("🎉 You have leveled up! Your stats have improved!")

# New function to add spells and abilities
def learn_spells():
    print("\n🧙 Welcome to the Arcane Library! 📜")
    print(f"💰 You have {player_data['stats']['gold']} gold.")

    spells = {
        "fireball": {"cost": 60, "damage": 20},
        "ice_shard": {"cost": 50, "damage": 15},
        "lightning_bolt": {"cost": 70, "damage": 25},
        "heal": {"cost": 50, "healing": 20}
    }

    print("Available Spells:")
    for spell, details in spells.items():
        effect = f"Damage: {details['damage']}" if 'damage' in details else f"Healing: {details['healing']}"
        print(f"🔹 {spell} - {details['cost']} Gold | {effect}")

    print("5️⃣ Exit Arcane Library")

    while True:
        choice = input("Choose a spell to learn (e.g., fireball) or '5' to leave: ").strip().lower()
        if choice in spells and player_data['stats']['gold'] >= spells[choice]['cost']:
            player_data['stats']['gold'] -= spells[choice]['cost']
            player_data.setdefault("spells", []).append(choice)
            print(f"✨ You have learned the spell: {choice}!")
        elif choice == "5":
            print("📚 Arcane knowledge awaits another day.")
            break
        else:
            print("❌ Invalid choice or insufficient gold.")

    save_game()
    
def cast_spell(spell, enemy):
    spells = {
        "fireball": {"cost": 60, "damage": 20},
        "ice_shard": {"cost": 50, "damage": 15},
        "lightning_bolt": {"cost": 70, "damage": 25},
        "heal": {"cost": 50, "healing": 20}
    }

    if spell not in player_data.get("spells", []):
        print("❌ You have not learned this spell yet!")
        return 0

    if spell in spells:
        mana_cost = spells[spell]["cost"] // 2  # Mana drain = 1/2 of spell cost
        if player_data['stats']['mana'] >= mana_cost:
            player_data['stats']['mana'] -= mana_cost
            if 'damage' in spells[spell]:
                print(f"🔥 {spell.capitalize()} cast successfully! Dealt {spells[spell]['damage']} damage!")
                enemy["health"] -= spells[spell]['damage']  # APPLY DAMAGE CORRECTLY HERE
                return spells[spell]['damage']
            elif 'healing' in spells[spell]:
                player_data['stats']['health'] = min(100, player_data['stats']['health'] + spells[spell]['healing'])
                print(f"❤️ {spell.capitalize()} cast successfully! Healed {spells[spell]['healing']} HP!")
                return 0
        else:
            print("❌ Not enough mana!")
            return 0
    else:
        print("❌ Invalid spell name!")
        return 0
            
def get_equipped_stats():
    weapon_bonus = item_data["weapons"].get(player_data["equipped"]["weapon"], {}).get("power", 0)
    armor_bonus = item_data["armor"].get(player_data["equipped"]["armor"], {}).get("defense", 0)
    return weapon_bonus, armor_bonus
    
def flee_enemy(enemy):
    loot = enemy["loot"]
    if "xp" in loot:
        player_data["stats"]["xp"] += loot["xp"]
        print(f"✨ The {enemy['name']} fled in fear! You still gained {loot['xp']} XP!")
        check_level_up()

def player_talk(enemy):
    print("\n🗣️ You have a chance to speak before the battle!")
    print("Options: [taunt] 💢 | [intimidate] 😨 | [negotiate] 🤝 | [fight] ⚔️")

    while True:
        choice = input("What do you want to do? ").strip().lower()

        if choice == "taunt":
            print(f"💢 You taunt the {enemy['name']}!")
            taunt_response = enemy.get("responses", {}).get("taunt", "The enemy doesn't react to your taunt.")
            print(f"🗣️ {enemy['name']} says: \"{taunt_response}\"")

            enemy["power"] += 1
            print("🔥 The enemy is enraged! It fights harder, but might drop better loot!")
            return "fight"

        elif choice == "intimidate":
            print(f"😨 You try to scare the {enemy['name']}!")
            intimidate_response = enemy.get("responses", {}).get("intimidate", "The enemy does not seem intimidated.")
            print(f"🗣️ {enemy['name']} says: \"{intimidate_response}\"")

            if random.randint(1, 3) == 1:  # 33% chance enemy flees
                flee_enemy(enemy)  # Grant XP for successful intimidation
                print(f"🏃 The {enemy['name']} gets scared and runs away!")
                return
            else:
                print(f"❌ The {enemy['name']} is not impressed! Prepare to fight!")
                return "fight"

        elif choice == "negotiate":
            print(f"🤝 You try to make a deal with the {enemy['name']}!")
            negotiate_response = enemy.get("responses", {}).get("negotiate", "The enemy ignores your words.")
            print(f"🗣️ {enemy['name']} says: \"{negotiate_response}\"")

            gold_needed = random.randint(10, 40)
            if player_data["stats"]["gold"] >= gold_needed:
                print(f"💰 The {enemy['name']} accepts {gold_needed} gold and leaves you alone.")
                player_data["stats"]["gold"] -= gold_needed
                return "negotiate"
            else:
                print(f"❌ You don't have enough gold! The {enemy['name']} attacks!")
                return "fight"

        elif choice == "fight":
            print("⚔️ You prepare for battle!")
            return "fight"

        else:
            print("❌ Invalid choice. Try again.")

auto_battle = False
momentum = 0

def toggle_auto_battle():
    global auto_battle
    auto_battle = not auto_battle
    mode = "ON" if auto_battle else "OFF"
    print(f"🔄 Auto-Battle Mode: {mode}")

def fight(enemy):
    global momentum
    momentum = 0  # Reset at start of each battle

    enemy["base_health"] = enemy["health"]  # Ensure 'base_health' is properly initialized

    print(f"\n⚔️ You encounter a {enemy['name']}!")
    print(f"🗣️ {enemy['name']} says: \"{enemy['dialogue']}\"")

    action = player_talk(enemy)

    if action == "flee":
        print(f"🏃 You managed to escape from the {enemy['name']}!")
        return
    if action == "negotiate":
        print(f"🤝 You avoided the fight with the {enemy['name']}.")
        return

    weapon_bonus, armor_bonus = get_equipped_stats()

    while enemy["health"] > 0 and player_data["stats"]["health"] > 0:
        if not auto_battle:
            print("\n🎮 What will you do?")
            print("1️⃣ Attack ⚔️")
            print("2️⃣ Use Item 🏥")
            print("3🔥 Cast Spell")
            print("4 ⃣ Try to Flee 🏃")
            print("5️⃣ Toggle Auto-Battle 🔄")

            player_choice = input("Enter your choice: ").strip()
        else:
            player_choice = "1"  # Auto-battle defaults to attack

        if player_choice == "1":
            crit_chance = random.randint(1, 10) == 1  # 10% chance for critical hit
            base_attack = random.randint(5, 10) + player_data["stats"]["power"] + weapon_bonus
            momentum_bonus = int(base_attack * (momentum * 0.1))
            player_attack = base_attack + momentum_bonus
            crit_text = "💥 CRITICAL HIT! " if crit_chance else ""

            enemy_defense = random.randint(1, 4) + enemy["defense"]

            if player_attack > enemy_defense:
                damage = max(3, player_attack - enemy_defense)
                enemy["health"] -= damage
                momentum += 1  # Increase momentum on successful hits
                print(f"{crit_text}🔥 Momentum Bonus! Damage boosted by {momentum_bonus}! {damage} damage dealt!")
            else:
                print(f"🛡️ The {enemy['name']} blocks your attack!")
                momentum = 0  # Reset on failed attack

        elif player_choice == "2":
            use_item()
            continue  # Skip enemy attack this turn

        elif player_choice == "4":
            if attempt_flee():
                print(f"🏃 You successfully escaped from the {enemy['name']}!")
                return  # Escape battle
            else:
                print(f"🚫 The {enemy['name']} blocks your escape!")
                
        elif player_choice == "3":
            spell_choice = input("Which spell would you like to cast?: ").strip().lower()
            cast_spell(spell_choice, enemy)
            

        elif player_choice == "5":
            toggle_auto_battle()
            continue

        # Finishing Move Opportunity
        if 0 < enemy["health"] <= (enemy["base_health"] * 0.2):
            print(f"🔥 The {enemy['name']} is weakened! Do you want to attempt a Finishing Move? (yes/no)")
            finish_choice = input().strip().lower()
            if finish_choice == "yes":
                if random.randint(1, 3) != 1:  # 66% chance to succeed
                    print(f"💀 You deliver a final blow! The {enemy['name']} is defeated instantly!")
                    grant_enemy_loot(enemy)
                    return
                else:
                    print(f"❌ The {enemy['name']} barely dodges your attempt!")

        # Enemy Attack Phase
        enemy_attack = random.randint(4, 8) + enemy["power"]
        player_defense = random.randint(2, 5) + player_data["stats"]["defense"] + armor_bonus

        if enemy_attack > player_defense:
            damage = max(2, enemy_attack - player_defense)
            player_data["stats"]["health"] -= damage
            print(f"🩸 {enemy['name']} hits: -{damage} HP | 🟢 You: {player_data['stats']['health']} HP")

        if enemy["health"] <= 0:
            print(random.choice(victory_messages))
            grant_enemy_loot(enemy)
            return

        if player_data["stats"]["health"] <= 0:
            game_over()
            return  # End fight

        print(f"⚔️ Your health: {player_data['stats']['health']} | {enemy['name']}'s health: {enemy['health']}")

def grant_enemy_loot(enemy):
    loot = enemy["loot"]
    
    if "gold" in loot:
        player_data["stats"]["gold"] += loot["gold"]
        print(f"💰 You looted {loot['gold']} gold!")

    if "xp" in loot:
        player_data["stats"]["xp"] += loot["xp"]
        print(f"✨ You gained {loot['xp']} XP!")
        check_level_up()

    if "rare_item" in loot:
        add_to_inventory(loot["rare_item"])
        print(f"🎁 You found a rare item: {loot['rare_item']}!")

def attempt_flee():
    flee_chance = random.randint(1, 4)  # 25% chance to fail
    if flee_chance == 1:
        print("🚫 You try to escape... but the enemy blocks your path!")
        return False            
    else:
        print("🏃 You successfully flee from battle!")
        return True

def view_inventory():
    print("\n🎒 Your Inventory:")
    if not player_data["inventory"]:
        print("(Empty)")
    else:
        for i, item in enumerate(player_data["inventory"], 1):
            print(f"{i}. {item}")
    
    choice = input("Do you want to use a potion? (yes/no): ").strip().lower()
    if choice == "yes":
        use_item()

def view_quest_log():
    print("\n📜 Your Active Quests:")
    if not player_data["quest_log"]:
        print("(No active quests)")
    else:
        for quest_id in player_data["quest_log"]:
            quest = next((q for q in quest_data["quests"] if q["id"] == quest_id), None)
            if quest:
                print(f"- {quest['description']}")

def view_stats():
    print("\n📊 Your Stats:")
    print(f"💖 Health: {player_data['stats']['health']}/{player_data['stats']['max_health']}")
    print(f"✨ Mana: {player_data['stats']['mana']}/{player_data['stats']['max_mana']}")
    print(f"⚔️ Power: {player_data['stats']['power']}")
    print(f"🛡️ Defense: {player_data['stats']['defense']}")
    print(f"✨ XP: {player_data['stats']['xp']}")
    print(f"💰 Gold: {player_data['stats']['gold']}")
    print(f"🗡️ Equipped Weapon: {player_data['equipped']['weapon'] or 'None'}")
    print(f"🛡️ Equipped Armor: {player_data['equipped']['armor'] or 'None'}")

def event_table(value):
    match value:
        case 1:
            print("⚠️ The ground suddenly gives way beneath your feet! You barely escape, but lose 10 health!")
            player_data["stats"]["health"] -= 10
            if player_data["stats"]["health"] <= 0:
                game_over()
                return  # End fight

        case 2:
            global dungeon_active

            if dungeon_active:
                print("❌ You cannot flee or save while in a dungeon. Complete the dungeon first!")
                return
            enter_dungeon()  # Replacing the fallen tree with the new dungeon system

        case 3:
            print("🏰 You reach an army checkpoint. Soldiers eye you suspiciously as you approach.")
            if random.randint(1, 2) == 1:
                print("A merchant waves you over! 🏪")
                visit_shop()

        case 4:
            print("🚨 You hear footsteps approaching! A shadowy figure emerges...")
            enemy = generate_monster()
            print(f"⚔️ You are confronted by a {enemy['name']}!")
            print(f"🗣️ {enemy['name']} says: \"{enemy['dialogue']}\"")  # Show enemy speech
            command = input("You can [fight] or [flee]: ").strip().lower()
            if command == "fight":
                fight(enemy)
            elif command == "flee":
                attempt_flee()
            else:
                print(f"❌ The {enemy['name']} doesn't wait for you to decide. It attacks!")
                fight(enemy)
                
        case 5:
            print("🗺️ A mysterious opportunity arises...")
            start_adventure()

        case 6:
            print("🪙 You find an ancient, dust-covered chest! As you open it, your eyes widen at the sight of treasure!")

            drop_chance = random.randint(1, 100)

            # 30% chance for quest items, 70% for shop items
            if drop_chance <= 30:
                possible_quest_items = [
                    quest["item"] for quest in quest_data["quests"]
                    if "item" in quest and quest["item"] not in player_data["quest_items"]
                ]
                found_item = random.choice(possible_quest_items) if possible_quest_items else random.choice(list(item_data["weapons"].keys()))
            else:
                found_item = random.choice(list(item_data["weapons"].keys()) + 
                                           list(item_data["armor"].keys()) + 
                                           list(item_data["potions"].keys()))

            player_data["stats"]["gold"] += random.randint(20, 50)
            add_to_inventory(found_item)

            player_data["stats"]["xp"] += 10
            check_level_up()

        case _:
            print("🌬️ A strange breeze passes... Nothing happens. Or did it? You feel uneasy...")

def main():
    global player_data

    # Load game if save exists
    if os.path.exists(SAVE_FILE):
        choice = input("Load previous game? (yes/no): ").strip().lower()
        if choice == "yes":
            load_game()
        else:
            os.remove(SAVE_FILE)  # Start fresh
            print("Starting a new adventure!")

    # If new game, ask for player name
    if player_data["name"] == "":
        player_data["name"] = input("Hail adventurer, what is your name? ")
        print(f"{player_data['name']}... A name soon to be written in history! Or forgotten.")                                   

    print("Your journey continues...")
    
    while True:
        command = input("Do you want to [explore], [save], [equip], [inventory], [quests], [stats], [train], [learn], or [quit]?: ").strip().lower()

        if command == "quit":
            print("Your adventure is put on hold...")
            break
        elif command == "explore":
            explore()
        elif command == "save":
            save_game()
        elif command == "equip":
            equip_item()
        elif command == "inventory":
            view_inventory()
        elif command == "quests":
            view_quest_log()
        elif command == "stats":
            view_stats()
        elif command == "train":
            upgrade_stats()
        elif command == "learn":
            learn_spells()
        else:
            print("Unknown command.")



if __name__ == "__main__":
    main()
