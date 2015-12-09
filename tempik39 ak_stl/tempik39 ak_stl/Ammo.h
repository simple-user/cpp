#pragma once
//#include <random>
#include <ctime>
#include <cstdlib>

class Ammo
{
public:
	Ammo() : number(numberStar++)	{};
	Ammo(size_t num) : number(num) {} // для копіювання магазинів хоч би як воно абсурдно не звучало :)))
	
	bool pif() // повертає попав у ціль чи ні
	{
		return rand() % 99 < 70;
	}

	size_t getNumber() const
	{
		return number;
	}

	static size_t numberStar;
private:
	size_t number;
};

