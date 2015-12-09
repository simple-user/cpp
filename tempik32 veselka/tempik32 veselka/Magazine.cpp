#include "Magazine.h"

Magazine::Magazine(std::string _name, int _price, bool _isNew): Item(_name, _price, _isNew) {}

std::ostream & operator<<(std::ostream & os, const Magazine & i)
{
	//os << "Magazine:\n";
	os << "name: " << i.name << ", price: " << (i.price / 100) << '.' << (i.price % 100) << " USD, ";
	os << (i.isNew ? "new" : "pre-owned");
	return os;
}

