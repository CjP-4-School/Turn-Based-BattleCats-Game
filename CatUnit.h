#pragma once
using namespace std;
#include <string>
#include <iostream>

class CatUnit
{
private:
    std::string characterName;
    string unitType;
    int level;
    int experience;
    int healthPoints;
    int attack;
    int defense;
    int speed;
    int specialPower;

public:
    // Constructors
    CatUnit()
    {
        characterName = "Unknown Cat";
        unitType = "Normal";
        level = 1;
        healthPoints = 100;
        attack = 10;
        defense = 5;
        speed = 5;
        specialPower = 10;
        experience = 0;
    }

    CatUnit(string n, string t, int lvl, int hp,
        int atk, int def, int spd, int sp)
    {
        characterName = n;
        unitType = t;
        level = lvl;
        healthPoints = hp;
        attack = atk;
        defense = def;
        speed = spd;
        specialPower = sp;
        experience = 0;
    }

    // Getters
    string GetCharacterName() const;

    string GetUnitType() const;

    int GetLevel() const;

    int GetExperience() const;
    
    int GetHealthPoints() const;
 
    int GetAttack() const;
  
    int GetDefense() const;

    int GetSpeed() const;
   
    int GetSpecialPower() const;
    
    void SetHealthPoints(int hp)
    {
        healthPoints = hp;
    }

    void GainExperience(int xp)
    {
        experience += xp;

        while (experience >= 100)
        {
            experience -= 100;
            level++;
            healthPoints += 20;
            attack += 5;
            defense += 3;
            specialPower += 4;

            cout << characterName
                << " leveled up to Level "
                << level
                << "!\n";
        }
    }
};

