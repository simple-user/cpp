#include <Windows.h>
#include "Var_string.h"
#include <string>
#include <iostream>
#include <exception>
#include <conio.h>

#define br cout << endl
#define _EXEPT_START try {
#define _EXEPT_END } \
	catch (std::exception &e) { \
	std::cout << "Error: " << e.what(); \
	}

using std::cout;
using std::endl;
using std::Var;

int main()
{

	_EXEPT_START
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	Var v(123);
	cout << v << endl;
	cout << v[1] << endl;
	v[1] = '5';
	cout << v << endl;

	//
	//Var v1(4), v2(5.5), v3("asd");
	//int iVar = 1;
	//double dVar = 2;
	//std::string xVar("3");
	//
	//cout << (v1 + v1 + v2 + v3 - v1 - v2 - v3 + 1 + 1.0 + "5" - 1 - 9.7 - "45" + std::string("55")) * v1 * v2 << endl;
	//
	//cout << (v1 > 5 && v2 <= v3 || v3 == "asd" || v2 != 5.7) << endl;
	//
	//cout << "v1 = " << v1 << endl;
	//cout << "v1 += 10 = " << (v1 += 10) << endl;
	//cout << "v1 += \"13\" = " << (v1 += "13") << endl;
	//cout << "v1 += \"asd\" = " << (v1 += "asd") << endl;
	//cout << endl;
	//cout << "v3 = " << v3 << endl;
	//cout << "v3 += 10 = " << (v3 += 10) << endl;
	//cout << "v3 += \"13\" = " << (v3 += "13") << endl;
	//cout << "v3 += \"asd\" = " << (v3 += "asd") << endl;

	//cout << endl;
	//cout << "v2 = " << v3 << endl;
	//cout << "v2 = 10.6 = " << (v2 = 10.6) << endl;
	//cout << "v2 += 10 = " << (v2 += 10) << endl;
	//cout << "v2 += \"13\" = " << (v2 += "13") << endl;
	//cout << "v2 += \"asd\" = " << (v2 += "asd") << endl;
	//cout << "v2 += v1 = " << (v2 += v1) << endl;
	//
	///*
	//Var vTest(12);
	//cout << "vTest > \"5\" = " << (vTest > "5") << endl;
	//*/
	//br;
	//br;
	//cout << "v1 " << v1 << endl;
	//cout << "v2 " << v2 << endl;
	//cout << "v3 " << v3 << endl;
	//br;
	//br;
	//cout << "v1[1]=1 " << endl; v1[1] = '1';
	//// cout << "v1[1]=z " << endl; v1[1] = 'z';
	//cout << "v2[-3]=2 " << endl; v2[-3] = '2';
	//cout << "v3[1]=3 " << endl; v3[1] = '3';
	//br;
	//br;
	//cout << "v1 " << v1 << endl;
	//cout << "v2 " << v2 << endl;
	//cout << "v3 " << v3 << endl;
	//br;
	//br;
	//cout << "v1[0] " << v1[0] << endl;
	//cout << "v2[0] " << v2[0] << endl;
	//cout << "v3[0] " << v3[0] << endl;
	//br;
	//br;
	
	_EXEPT_END
	return 0;
}

