#include "Item.h"


Item::Item(std::string _name, int _price, bool _isNew)
: name(std::move(_name)), price(_price), isNew(_isNew) {}

Item::Item(Item &&i)
{
	name = std::move(i.name);
	price = i.price;
	isNew = i.isNew;
}

Item::~Item() {}

void Item::setName(std::string _name)
{
	name = std::move(_name);
}

void Item::setPrice(int _price)
{
	if (price < 0)
		throw std::invalid_argument("Price below zero!");
	price = _price;
}

void Item::setIsNew(bool _isNew)
{
	isNew = _isNew;
}

const std::string & Item::getName() const
{
	return name;
}

int Item::getPrice() const
{
	return price;
}

bool Item::isItNew() const
{
	return isNew;
}

std::ostream & operator<<(std::ostream & os, const Item & i)
{
	os << "name: " << i.name << ", price: " << (i.price / 100) << '.' << (i.price % 100) << " USD ";
	os << (i.isNew ? "new" : "pre-owned");
	return os;
}