#include <iostream>
#include <array>
#include <algorithm>
#include <string>
#include <functional>
#include <fstream>
#include <Windows.h>

using namespace std;


class A
{
public:
	A(int _a, int _b) : a(_a), b(_b) {}
	const int a;
	const int b;
};



int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	A a(1, 2);
	cout << a.a << endl;
	cout << a.b << endl;

	return 0;
}