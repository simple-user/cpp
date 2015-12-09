#include <iostream>
#include <ctime>
#include <Windows.h>
#include <conio.h>
#include <string>
#include "myMap.h"

using std::cout;
using std::endl;
using std::string;

#define br cout << endl

#define _EXEPT_START try {
#define _EXEPT_END } \
	catch (std::exception &e) { \
	std::cout << "Error: " << e.what(); \
} \
catch (...) { \
	std::cout << "Что-то пошло не так... Chrome.(c) "; \
}


struct myPair
{
	int n;
	string s;
	myPair(int n, const string &s) : n(n), s(s){};
};

bool operator==(const myPair &m1, const myPair &m2)
{
	return m1.n == m2.n;
}

bool operator<=(const myPair &m1, const myPair &m2)
{
	return m1.n <= m2.n;
}

std::ostream & operator<<(std::ostream &o, const myPair &m)
{
	o << m.s << " = " << m.n << endl;
	return o;
}


int main() 
{
	_EXEPT_START

	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	myMap<int, int> mm1;
	for (int a = 1; a < 1000000; ++a)
		mm1.push(a, a);
	cout << "height of a tree = " << static_cast<int>(mm1.height()) << endl;
	// mm1.show();

	_EXEPT_END
	return 0;
}
