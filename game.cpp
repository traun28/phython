#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <limits>
using namespace std;

// --- Utility Functions ---
void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int random(int min, int max) {
    return rand() % (max - min + 1) + min;
}

// --- Character Base Class ---
class Character {
protected:
    string name;
    int health;
    int attack;
    int defense;

public:
    Character(string n, int h, int a, int d)
        : name(n), health(h), attack(a), defense(d) {}

    virtual void displayStats() const {
        cout << "Name: " << name << " | HP: " << health
             << " | ATK: " << attack << " | DEF: " << defense << endl;
    }

    bool isAlive() const {
        return health > 0;
    }

    virtual int takeDamage(int dmg) {
        int damageTaken = dmg - defense;
        if (damageTaken < 0) damageTaken = 0;
        health -= damageTaken;
        if (health < 0) health = 0;
        return damageTaken;
    }

    virtual int attackTarget(Character& target) {
        int damage = random(attack / 2, attack);
        return target.takeDamage(damage);
    }

    string getName() const {
        return name;
    }

    int getHealth() const {
        return health;
    }

    void heal(int amount) {
        health += amount;
        if (health > 100) health = 100;
    }
};

// --- Player Class ---
class Player : public Character {
private:
    vector<string> inventory;

public:
    Player(string n)
        : Character(n, 100, 20, 5) {
        inventory.push_back("Potion");
    }

    void showInventory() {
        cout << "\nInventory: ";
        if (inventory.empty()) {
            cout << "Empty\n";
        } else {
            for (const auto& item : inventory) {
                cout << item << " ";
            }
            cout << endl;
        }
    }

    void useItem() {
        if (inventory.empty()) {
            cout << "No items to use!\n";
            return;
        }

        cout << "Using " << inventory.back() << "...\n";
        if (inventory.back() == "Potion") {
            heal(30);
            cout << "Healed 30 HP!\n";
        }
        inventory.pop_back();
    }

    void addItem(string item) {
        inventory.push_back(item);
    }
};

// --- Enemy Class ---
class Enemy : public Character {
public:
    Enemy(string n, int h, int a, int d)
        : Character(n, h, a, d) {}

    static Enemy generateRandom() {
        vector<string> names = {"Goblin", "Orc", "Dark Elf", "Skeleton"};
        string name = names[random(0, names.size() - 1)];
        int health = random(50, 100);
        int attack = random(10, 25);
        int defense = random(2, 10);
        return Enemy(name, health, attack, defense);
    }
};

// --- Game Functions ---
void battle(Player& player, Enemy& enemy) {
    cout << "\nBattle begins between " << player.getName() << " and " << enemy.getName() << "!\n";
    while (player.isAlive() && enemy.isAlive()) {
        cout << "\n-- " << player.getName() << "'s Turn --\n";
        player.displayStats();
        enemy.displayStats();

        cout << "\n1. Attack\n2. Use Item\nChoose action: ";
        int choice;
        cin >> choice;
        clearInputBuffer();

        if (choice == 1) {
            int dmg = player.attackTarget(enemy);
            cout << "You dealt " << dmg << " damage!\n";
        } else if (choice == 2) {
            player.useItem();
        } else {
            cout << "Invalid choice.\n";
        }

        if (!enemy.isAlive()) break;

        cout << "\n-- " << enemy.getName() << "'s Turn --\n";
        int dmg = enemy.attackTarget(player);
        cout << enemy.getName() << " dealt " << dmg << " damage!\n";
    }

    if (player.isAlive()) {
        cout << "\nYou defeated " << enemy.getName() << "!\n";
        if (random(1, 100) <= 40) {
            player.addItem("Potion");
            cout << "You found a Potion!\n";
        }
    } else {
        cout << "\nYou were defeated...\n";
    }
}

// --- Main Game ---
int main() {
    srand((unsigned)time(0));

    cout << "Welcome to the RPG Battle Simulator!\nEnter your character's name: ";
    string playerName;
    getline(cin, playerName);

    Player player(playerName);

    while (true) {
        cout << "\n-- Main Menu --\n";
        cout << "1. Fight an enemy\n";
        cout << "2. Show stats\n";
        cout << "3. Inventory\n";
        cout << "4. Exit\n";
        cout << "Choose an action: ";
        int choice;
        cin >> choice;
        clearInputBuffer();

        switch (choice) {
            case 1:
                if (!player.isAlive()) {
                    cout << "You're too injured to fight.\n";
                } else {
                    Enemy enemy = Enemy::generateRandom();
                    battle(player, enemy);
                }
                break;
            case 2:
                player.displayStats();
                break;
            case 3:
                player.showInventory();
                break;
            case 4:
                cout << "Thanks for playing!\n";
                return 0;
            default:
                cout << "Invalid option.\n";
        }
    }

    return 0;
}

