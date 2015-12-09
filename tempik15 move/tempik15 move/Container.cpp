#include "Container.h"


//Container();
Container::Container()
{
	std::cout << "$$$Container::Container()" << std::endl;
}

//Container(const MyString & m);
Container::Container(const MyString &m) : mstr(m)
{
	std::cout << "$$$Container::Container(const MyString &m(" << m << "))" << std::endl;
}

//Container(const MyString &&m);
Container::Container(MyString &&m) : mstr(std::move(m)) 
{
	std::cout << "$$$Container::Container(MyString &&m(" << m << "))" << std::endl;
}

//Container(const Container& c);
Container::Container(const Container &c) : mstr(c.mstr)
{
	std::cout << "$$$Container::Container(const Container &c(" << c.mstr << "))" << std::endl;
}

//Container(Container &&c);
Container::Container(Container &&c) : mstr(std::move(c.mstr))
{
	std::cout << "$$$Container::Container(Container &&c(" << c.mstr << "))" << std::endl;
}

//
//friend Container operator+(const Container& c1, const Container& c2);
Container operator+(const Container& c1, const Container& c2)
{
	std::cout << "$$$Container operator+(const Container& c1(" << c1.mstr << "), const Container& c2(" << c2.mstr << "))" << std::endl;
	Container t(c1.mstr + c2.mstr);
	return t;
}

//Container& operator=(const Container &c);
Container& Container::operator=(const Container &c)
{
	std::cout << "$$$Container& Container::operator=(const Container &c(" << c.mstr << "))" << std::endl;
	mstr = c.mstr;
	return *this;
}

//Container& operator=(Container &&c);
Container& Container::operator=(Container &&c)
{
	std::cout << "$$$Container& Container::operator=(Container &&c(" << c.mstr << "))" << std::endl;
	mstr = std::move(c.mstr);
	return *this;
}

//friend std::ostream& operator<<(std::ostream &os, const Container c)
std::ostream& operator<<(std::ostream &os, const Container& c)
{
	os << c.mstr;
	return os;
}

//~Container();
Container::~Container()
{
	std::cout << "$$$Container::~Container() for " << mstr << std::endl;
}
