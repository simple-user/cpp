#pragma once
#include <string>
#include <exception>

class Item
{
public:
	Item(std::string _name, int _price, bool _isNew);

	Item(Item &&i);


	void setName(std::string _name);
	void setPrice(int _price);
	void setIsNew(bool _isNew);

	const std::string & getName() const;
	int getPrice() const;
	bool isItNew() const;

	friend std::ostream & operator<<(std::ostream & os, const Item & i);
	
	virtual ~Item() = 0;
protected:
	std::string name;
	int         price;
	bool        isNew;
};

