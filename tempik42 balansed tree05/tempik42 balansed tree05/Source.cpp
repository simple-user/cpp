#include <iostream>
#include <ctime>
#include <Windows.h>
#include <conio.h>
#include <string>
#include "myMap.h"
#include "BinaryTreeInt.h"
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;
using std::string;
using std::vector;

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


	vector<std::pair<unsigned, unsigned>> results;
	size_t sizeSorce = 10;
	vector<size_t> sorceArr(sizeSorce);
	
	for (size_t a = 0; a < sizeSorce; ++a)
		sorceArr[a] = a;

	BinaryTreeInt btr1;
	myMap<int, int> mm1;

	for (size_t a = 0; a < 15; ++a)
	{
		 std::random_shuffle(sorceArr.begin(), sorceArr.end());
		 cout << "progress: \n";
		for (size_t a = 0; a < sizeSorce; ++a)
		{
			if (a % (sizeSorce/10) ==0)
				cout << '+';
			btr1.add(sorceArr[a], string());
			mm1.push(sorceArr[a], a);
		}
		cout << endl;
		results.push_back(std::make_pair(btr1.height(), mm1.height())); // впринципі можна ж відразі вивести тай усе)

		cout << "height of selfOrganization tree = " << btr1.height() << endl;
		cout << "height of ruleSorted tree = " << static_cast<int>(mm1.height()) << endl;
		
		cout << endl;
		
		btr1.clear();
		mm1.clear();

	}


	

	

	_EXEPT_END
	return 0;
}
