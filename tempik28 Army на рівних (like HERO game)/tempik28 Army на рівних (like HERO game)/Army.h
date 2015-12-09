#pragma once
#include "Unit.h"
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iostream>
class Army
{
public:
	Army(int countUnits);
	void printArmy() const;
	bool delVarior(int index);
	bool attack(Army &ar);
	~Army();
	bool aliveArmy() const
	{
		return Units.size();
	}
	
private:
	bool pvp(Army &ar, int myWarior, int opponentWarior, bool answer=0);
	std::vector<Unit*> Units;
};

