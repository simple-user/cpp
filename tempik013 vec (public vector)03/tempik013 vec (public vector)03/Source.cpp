#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <vector>
#include <iterator>
#include <vector>
#include <algorithm>
#include <string>
#include <iomanip>
#include <utility>
#include "vec.h"
#include "myException.h"

using std::vector;
using std::string;
using std::cout;
using std::endl;

#define br cout << endl

#define _EXEPT_START try {

#define _EXEPT_END } \
	catch (std::exception &e) {\
	std::cout << "Error: " << e.what(); \
} \
	catch (const char* str) \
{ \
	std::cout << "Error: " << str << endl; \
} \
	catch (const int i) \
{ \
	std::cout << "Error: " << i << endl; \
} \
	catch (...) \
{	\
	std::cout << "Что-то пошло не так... Chrome.(c) "; \
} 





template<typename type>
inline void printVec(const vec<type> & vecRef, const string & name)
{
	cout << "Printing vec (" << name << "): ";
	std::for_each(vecRef.cbegin(), vecRef.cend(), [](type t) {cout << std::setw(5) << t; });
	cout << "   //end.\n";
}


int main()
{
	_EXEPT_START
		SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	//myException<3, string, int> e1{ { "Eror in vector v45", -1 }, { "size", 4 }, {"now", 12} };
	//for (size_t a = 0; a < e1.getSize(); ++a)
	//{
	//	if (e1.getPtrPair(a))
	//		cout << e1.getPtrPair(a)->first << " - " << e1.getPtrPair(a)->second << endl;
	//}


	
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

	vec<int> v6{ 2, 2, 3, 3, 4, 4 };
	printVec(v6, "v6");

	v5 = v6;
	printVec(v5, "v5");

	v5 = { 0, 0, 9, 9, 8, 8 };
	printVec(v5, "v5");

	cout << "v5[2](9) = " << v5[2] << endl;
	cout << "at(2)(9) = " << v5.at(2) << endl;
	cout << "v5[10](9) = " << v5[10] << endl;

	_EXEPT_END

	return 0;

}