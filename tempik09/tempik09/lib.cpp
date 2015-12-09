#include "Header.h"
using namespace std;


Monitor::Monitor():type(COOL),manufacturer(nullptr){}

Monitor::Monitor(const char* m, Type t) : type(t), manufacturer(nullptr)
{
	int len = strlen(m);
	if (len)
	{
		manufacturer = new char[len + 1];
		strcpy_s(manufacturer, len + 1, m);
	}
}

Monitor::Monitor(const Monitor &m) : type(m.type)
{
	int len = strlen(m.manufacturer);
	if (len)
	{
		manufacturer = new char[len + 1];
		strcpy_s(manufacturer, len + 1, m.manufacturer);
	}

}

Monitor::Monitor(Monitor&& m)
{
	manufacturer = m.manufacturer;
	type = m.type;

	m.manufacturer = nullptr;
}

void Monitor::printInf() const
{
	cout << "Type: " << type << ", mnaufacturer: " << manufacturer<< endl;
}

ostream& operator<<(ostream& os, Monitor& m)
{
	return (os << "Type: " << m.type << ", manufacturer: " << m.manufacturer);
}

Monitor& Monitor::operator=(Monitor m)
{
	std::swap(this->type, m.type);
	std::swap(this->manufacturer, m.manufacturer);
	return *this;
}

const Monitor& Monitor::returnMeLink() const
{
	return *this;
}

Monitor  Monitor::returnMeValue() const
{
	Monitor t = *this;
	return t;
}


void Monitor::setType(Type t)
{
	type = t;
}

void Monitor::setManufacturer(const char *m)
{
	if (manufacturer != m)
	{
		int len = strlen(m);
		if (manufacturer)
			delete[] manufacturer;
		
		manufacturer = new char[len + 1];
		strcpy_s(manufacturer, len + 1, m);
	}
}

Type Monitor::getType() const
{
	return type;
}

const char* Monitor::getManufacturer() const
{
	return manufacturer;
}

Monitor::~Monitor()
{
	delete[] manufacturer;
}



