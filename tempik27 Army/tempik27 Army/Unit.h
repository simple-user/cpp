#pragma once
#include <ctime>
#include <cstdlib>
#include <string.h>
class Unit
{
public:
	Unit(const int _hp, const int _dmg, const int _dodge, const char *_name) : hp(_hp), dmg(_dmg), dodge(_dodge) 
	{
		strcpy_s(name, _name);
		
	}
	
	// атака
	bool attack(Unit &u) const
	{
		if (!u.avoid())
		{
			u.hp -= dmg;
			return 1;
		}
		
		return 0;
	}

	// функція яка повертає чи вдалось ухилитись
	bool avoid() const
	{
		srand(unsigned(time(0)));
		if (rand() % 101 <= dodge)
			return 1;
		
		return 0;
	}

	// перевірка чи воїн живий
	bool died() const
	{
		if (hp <= 0)
			return 1;
		return 0;
	}

	int getHp() const
	{
		return hp;
	}

	const char * getName() const
	{
		return name;
	}

private:
	int hp;
	int dmg;
	int dodge;
	char name[20];
};

class Swordsman : public Unit
{
public:
	Swordsman() : Unit(15, 5, 60, "Swordsman") {}
};

class Archer : public Unit
{
public:
	Archer() : Unit(12, 4, 40, "Archer") {}
};

class Mage : public Unit
{
public:
	Mage() : Unit(8, 10, 30, "Mage") {}
};
