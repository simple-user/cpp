#ifndef _CONTAINER_
#define _CONTAINER_
#include "MyString.h"

class Container
{
private:
	MyString mstr;
public:
	Container();
	Container(const MyString & m);
	Container(MyString &&m);
	Container(const Container& c);
	Container(Container &&c);

	friend Container operator+(const Container& c1, const Container& c2);
	Container& operator=(const Container &c);
	Container& operator=(Container &&c);

	friend std::ostream& operator<<(std::ostream &os, const Container& c);

	~Container();
	
};

#endif

