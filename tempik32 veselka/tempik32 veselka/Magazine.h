#pragma once
#include "Item.h"

class Magazine : public Item
{
public:
	Magazine(std::string _name = "", int _price = 0, bool _isNew = 0);

	friend std::ostream & operator<<(std::ostream & os, const Magazine & i);
	
};

