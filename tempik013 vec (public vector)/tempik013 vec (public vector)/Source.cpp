#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <vector>
#include <iterator>
#include <vector>
#include <algorithm>
#include <string>
#include <iomanip>
#include "vec.h"

using std::vector;
using std::string;
using std::cout;
using std::endl;

template<typename type>
inline void printVec(const vec<type> & vecRef, const string & name)
{
	cout << "Printing vec (" << name << "): ";
	std::for_each(vecRef.cbegin(), vecRef.cend(), [](type t) {cout << std::setw(5) << t; });
	cout << "   //end.\n";
}


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	vec<int> v1;
	printVec(v1, "v1");
	
	vec<int> v2(5);
	printVec(v2, "v2");
	
	vec<int> v3(10, 6);
	printVec(v3, "v3");

	vec<int> v4(v3);
	printVec(v4, "v4");

	vec<int> v5(v4.cbegin(), v4.cbegin() + 3);
	printVec(v5, "v5");

	return 0;
}