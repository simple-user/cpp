#include <string.h>
#include <string>
#include "Student.h"


inline void Student::setStr(char *& dest, const char * const sorce)
{
	if (dest)
		delete[] dest;
	if (sorce)
	{
		int len = strlen(sorce);
		dest = new char[len + 1];
		strcpy_s(dest, len + 1, sorce);
	}
	else
		dest = nullptr;
}


Student::Student(const char * const newName, const char * const newSurname) : name(nullptr), surname(nullptr)
{
	setStr(name, newName);
	setStr(surname, newSurname);
}

Student::~Student()
{
	if (name)
		delete[] name;
	if (surname)
		delete[] surname;
}

void Student::setName(const char * const newName)
{
	setStr(name, newName);
}

void Student::setSurname(const char * const newSurname)
{
	setStr(surname, newSurname);
}

const char * const Student::getName() const
{
	return name;
}

const char * const Student::getSurname() const
{
	return surname;
}

