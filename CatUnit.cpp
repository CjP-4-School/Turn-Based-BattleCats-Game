#include "CatUnit.h"
#include <iostream>

using namespace std;

string CatUnit::GetCharacterName() const
{
	return characterName;
}

string CatUnit::GetUnitType() const
{
	return unitType;
}

int CatUnit::GetLevel() const
{
	return level;
}

int CatUnit::GetExperience() const
{
	return experience;
}

int CatUnit::GetHealthPoints() const
{
	return healthPoints;
}

int CatUnit::GetAttack() const
{
	return attack;
}

int CatUnit::GetDefense() const
{
	return defense;
}

int CatUnit::GetSpeed() const
{
	return speed;
}

int CatUnit::GetSpecialPower() const
{
	return specialPower;
}

// Setters
