// BattleCatsGame.cpp
// A turn-based Battle Cats inspired game.

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <chrono>
using namespace std;

// ============================== FUNCTIONS ==============================
#include "CatUnit.h"
void PrintCharacter(const CatUnit& c);
CatUnit CreateCharacter();
void StartBattle(vector<CatUnit>& players, vector<CatUnit>& enemies);
void ListCharacters(const vector<CatUnit>& list);
void DeleteCharacter(vector<CatUnit>& list);
void EditCharacter(vector<CatUnit>& list);
bool AllDead(const vector<int>& hp);

// ============================== MAIN ==============================
int main()
{
    srand(static_cast<unsigned int>(time(0)));

    vector<CatUnit> playerCats;
    vector<CatUnit> enemyCats;

    int choice = -1;

    while (choice != 0)
    {
        cout << "\n====================================\n";
        cout << "      BATTLE CATS MAIN MENU\n";
        cout << "====================================\n";
        cout << "1. Add Player Cat\n";
        cout << "2. Add Enemy Cat\n";
        cout << "3. List Player Cats\n";
        cout << "4. List Enemy Cats\n";
        cout << "5. Edit Player Cat\n";
        cout << "6. Edit Enemy Cat\n";
        cout << "7. Delete Player Cat\n";
        cout << "8. Delete Enemy Cat\n";
        cout << "9. Start Battle\n";
        cout << "0. Exit\n";
        cout << "====================================\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            playerCats.push_back(CreateCharacter());
            break;

        case 2:
            enemyCats.push_back(CreateCharacter());
            break;

        case 3:
            ListCharacters(playerCats);
            break;

        case 4:
            ListCharacters(enemyCats);
            break;

        case 5:
            EditCharacter(playerCats);
            break;

        case 6:
            EditCharacter(enemyCats);
            break;

        case 7:
            DeleteCharacter(playerCats);
            break;

        case 8:
            DeleteCharacter(enemyCats);
            break;

        case 9:
            StartBattle(playerCats, enemyCats);
            break;

        case 0:
            cout << "Exiting game...\n";
            break;

        default:
            cout << "Invalid option.\n";
            break;
        }
    }

    return 0;
}

// ============================== CHARACTER CREATION ==============================
CatUnit CreateCharacter()
{
    string name;
    string type;

    int level;
    int hp;
    int attack;
    int defense;
    int speed;
    int special;

    cout << "Enter cat name: ";
    cin >> ws;
    getline(cin, name);

    cout << "Enter unit type (Normal/Uber Rare/Special/etc): ";
    getline(cin, type);

    cout << "Enter level: ";
    cin >> level;

    cout << "Enter HP: ";
    cin >> hp;

    cout << "Enter attack: ";
    cin >> attack;

    cout << "Enter defense: ";
    cin >> defense;

    cout << "Enter speed: ";
    cin >> speed;

    cout << "Enter special power strength: ";
    cin >> special;

    return CatUnit(name, type, level, hp,
        attack, defense, speed, special);
}

// ============================== CHARACTER PRINTER ==============================
void PrintCharacter(const CatUnit& c)
{
    cout << "Name: " << c.GetCharacterName() << "\n";
    cout << "Type: " << c.GetUnitType() << "\n";
    cout << "Level: " << c.GetLevel() << "\n";
    cout << "HP: " << c.GetHealthPoints() << "\n";
    cout << "Attack: " << c.GetAttack() << "\n";
    cout << "Defense: " << c.GetDefense() << "\n";
    cout << "Speed: " << c.GetSpeed() << "\n";
    cout << "Special Power: " << c.GetSpecialPower() << "\n";
    cout << "XP: " << c.GetExperience() << "/100\n";
}

// ============================== CHARACTER LISTS ==============================
void ListCharacters(const vector<CatUnit>& list)
{
    if (list.empty())
    {
        cout << "No units available.\n";
        return;
    }

    for (int i = 0; i < list.size(); i++)
    {
        cout << "\nIndex: " << i << "\n";
        PrintCharacter(list[i]);
        cout << "--------------------------\n";
    }
}

// ============================== CHARACTER DELETER ==============================
void DeleteCharacter(vector<CatUnit>& list)
{
    if (list.empty())
    {
        cout << "No units to delete.\n";
        return;
    }

    int index;

    cout << "Enter index to delete: ";
    cin >> index;

    if (index < 0 || index >= list.size())
    {
        cout << "Invalid index.\n";
        return;
    }

    cout << list[index].GetCharacterName() << " was removed.\n";

    list.erase(list.begin() + index);
}

// ============================== CHARACTER EDITOR ==============================
void EditCharacter(vector<CatUnit>& list)
{
    if (list.empty())
    {
        cout << "No units to edit.\n";
        return;
    }

    int index;

    cout << "Enter index to edit: ";
    cin >> index;

    if (index < 0 || index >= list.size())
    {
        cout << "Invalid index.\n";
        return;
    }

    cout << "Recreating character...\n";

    list[index] = CreateCharacter();

    cout << "Character updated successfully.\n";
}

// ============================== DEATH CHECK ==============================
bool AllDead(const vector<int>& hp)
{
    for (int value : hp)
    {
        if (value > 0)
        {
            return false;
        }
    }

    return true;
}

// ============================== BATTLE SYSTEM ==============================
void StartBattle(vector<CatUnit>& players, vector<CatUnit>& enemies)
{
    if (players.empty() || enemies.empty())
    {
        cout << "Both teams need at least one unit.\n";
        return;
    }

    cout << "\nBattle starting...\n\n";

    auto startTime = chrono::high_resolution_clock::now();

    vector<int> playerHP;
    vector<int> enemyHP;

    for (const auto& p : players)
    {
        playerHP.push_back(p.GetHealthPoints());
    }

    for (const auto& e : enemies)
    {
        enemyHP.push_back(e.GetHealthPoints());
    }

    int round = 1;

    while (true)
    {
        cout << "===================================\n";
        cout << "ROUND " << round << "\n";
        cout << "===================================\n\n";

        // ================= PLAYER TURN =================
        for (int i = 0; i < players.size(); i++)
        {
            if (playerHP[i] <= 0)
            {
                continue;
            }

            vector<int> livingEnemies;

            for (int j = 0; j < enemyHP.size(); j++)
            {
                if (enemyHP[j] > 0)
                {
                    livingEnemies.push_back(j);
                }
            }

            if (livingEnemies.empty())
            {
                break;
            }

            int target = livingEnemies[rand() % livingEnemies.size()];

            int damage = players[i].GetAttack() +
                players[i].GetSpecialPower() -
                enemies[target].GetDefense();

            if (damage < 1)
            {
                damage = 1;
            }

            enemyHP[target] -= damage;

            cout << players[i].GetCharacterName()
                << " attacks "
                << enemies[target].GetCharacterName()
                << " for "
                << damage
                << " damage!\n";

            if (enemyHP[target] <= 0)
            {
                cout << enemies[target].GetCharacterName()
                    << " has been defeated!\n";
            }
        }

        if (AllDead(enemyHP))
        {
            cout << "PLAYER CATS WIN!\n";
            cout << "Awarding XP...\n";

            for (int i = 0; i < players.size(); i++)
            {
                int xpEarned = 50 + (round * 10);

                cout << players[i].GetCharacterName()
                    << " earned "
                    << xpEarned
                    << " XP!\n";

                players[i].GainExperience(xpEarned);
            }
            break;
        }

        // ================= ENEMY TURN =================
        for (int i = 0; i < enemies.size(); i++)
        {
            if (enemyHP[i] <= 0)
            {
                continue;
            }

            vector<int> livingPlayers;

            for (int j = 0; j < playerHP.size(); j++)
            {
                if (playerHP[j] > 0)
                {
                    livingPlayers.push_back(j);
                }
            }

            if (livingPlayers.empty())
            {
                break;
            }

            int target = livingPlayers[rand() % livingPlayers.size()];

            int damage = enemies[i].GetAttack() +
                enemies[i].GetSpecialPower() -
                players[target].GetDefense();

            if (damage < 1)
            {
                damage = 1;
            }

            playerHP[target] -= damage;

            cout << enemies[i].GetCharacterName()
                << " attacks "
                << players[target].GetCharacterName()
                << " for "
                << damage
                << " damage!\n";

            if (playerHP[target] <= 0)
            {
                cout << players[target].GetCharacterName()
                    << " has been defeated!\n";
            }
        }

        if (AllDead(playerHP))
        {
            cout << "\nENEMY CATS WIN!\n";
            break;
        }

        round++;

        cout << "\n";
    }

    auto endTime = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::seconds>(
        endTime - startTime);

    cout << "Battle completed in "
        << duration.count()
        << " seconds.\n";
}