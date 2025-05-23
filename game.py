import random
import time
import sys

# --- Helper functions ---
def delay_print(s):
    """Print with delay for dramatic effect."""
    for c in s:
        sys.stdout.write(c)
        sys.stdout.flush()
        time.sleep(0.02)
    print()

# --- Character Class ---
class Character:
    def __init__(self, name, health, attack_power, inventory=None):
        self.name = name
        self.health = health
        self.attack_power = attack_power
        self.inventory = inventory if inventory else []

    def is_alive(self):
        return self.health > 0

    def attack(self, target):
        damage = random.randint(1, self.attack_power)
        delay_print(f"{self.name} attacks {target.name} for {damage} damage!")
        target.health -= damage
        return damage

    def heal(self):
        if "potion" in self.inventory:
            self.health += 20
            self.inventory.remove("potion")
            delay_print(f"{self.name} drinks a potion and heals 20 HP!")
        else:
            delay_print(f"{self.name} has no potion!")

# --- Enemy Generator ---
def generate_enemy(level):
    names = ["Skeleton", "Dark Wolf", "Goblin", "Orc", "Shade"]
    name = random.choice(names)
    health = 30 + level * 10
    attack = 5 + level * 2
    return Character(name, health, attack)

# --- Game Locations ---
def forest_path(player):
    delay_print("You walk through the eerie Whispering Forest...")
    if random.random() < 0.7:
        enemy = generate_enemy(1)
        combat(player, enemy)
    else:
        delay_print("You found a health potion on the ground!")
        player.inventory.append("potion")

def cursed_cave(player):
    delay_print("The cave is dark and smells of death...")
    if random.random() < 0.5:
        enemy = generate_enemy(2)
        combat(player, enemy)
    else:
        delay_print("You discover a hidden treasure chest!")
        reward = random.choice(["potion", "ancient sword"])
        player.inventory.append(reward)
        delay_print(f"You obtained: {reward}!")

# --- Combat Loop ---
def combat(player, enemy):
    delay_print(f"A wild {enemy.name} appears!")
    while player.is_alive() and enemy.is_alive():
        delay_print(f"\n{player.name}'s HP: {player.health}")
        delay_print(f"{enemy.name}'s HP: {enemy.health}")
        action = input("Choose action: [A]ttack, [H]eal, [R]un: ").lower()
        if action == "a":
            player.attack(enemy)
            if enemy.is_alive():
                enemy.attack(player)
        elif action == "h":
            player.heal()
            if enemy.is_alive():
                enemy.attack(player)
        elif action == "r":
            if random.random() < 0.5:
                delay_print("You escaped successfully!")
                return
            else:
                delay_print("You failed to escape!")
                enemy.attack(player)
        else:
            delay_print("Invalid action.")

    if not player.is_alive():
        delay_print("You have fallen in battle...")
        exit()
    else:
        delay_print(f"You defeated the {enemy.name}!")

# --- Game Intro ---
def game_intro():
    delay_print("Welcome to the Realm of the Forgotten King.")
    name = input("Enter your hero's name: ")
    player = Character(name, 100, 15, ["potion"])
    delay_print(f"Brave {player.name}, your journey begins now!")
    return player

# --- Main Game Loop ---
def main():
    player = game_intro()

    locations = [forest_path, cursed_cave]
    while True:
        print("\nWhere will you go?")
        print("1. Whispering Forest")
        print("2. Cursed Cave")
        print("3. View Stats")
        print("4. Quit")
        choice = input("Choose: ")

        if choice == "1":
            forest_path(player)
        elif choice == "2":
            cursed_cave(player)
        elif choice == "3":
            delay_print(f"\nName: {player.name}")
            delay_print(f"Health: {player.health}")
            delay_print(f"Attack Power: {player.attack_power}")
            delay_print(f"Inventory: {player.inventory}")
        elif choice == "4":
            delay_print("Thanks for playing. Farewell!")
            break
        else:
            delay_print("Invalid option.")

if __name__ == "__main__":
    main()

