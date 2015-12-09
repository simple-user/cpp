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
	
private:
	std::vector<Unit*> Units;
};

