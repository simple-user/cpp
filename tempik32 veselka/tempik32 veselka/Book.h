#pragma once
#include "Item.h"

class Book : public Item
{
public:
	Book(std::string publ = "", std::string auth = "", std::string _name = "", int _price =0, bool _isNew =0);

	// конструктор копії стандартний підходить memberwise copy
	// Book(Book&)

	Book(Book &&b);

	void setPublication(std::string publ);
	void setAuthor(std::string auth);

	const std::string & getPublication() const;
	const std::string & getAuthor() const;

	friend std::ostream & operator<<(std::ostream & os, const Book & i);
	
	// оператор присваювання дефолтний підходить memberwise copy
	// Book& operator=(const Book& b);

private:
	std::string publication;
	std::string author;
};

