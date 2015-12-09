#include <iostream>
#include <Windows.h>

using namespace std;


class A
{
public:
	int a;
	char *c;
	A() : a(10), c("text null")
	{
		cout << "A()" << endl;
	}
	A(int t) 
	{
		cout << "A(int t)" << endl;
		if (a==10)
			cout << "Òóò âæå º 10!!!\n";

		a = t; 
		c = "TTTTT";
	}
	
	~A()
	{
		cout << "~A()" << endl;
	}
};

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	A a1; 
	cout << "a1: a - " << a1.a << " c - " << a1.c << endl;
	a1 = 4;
	cout << "a1: a - " << a1.a << " c - " << a1.c << endl;

	return 0;

}

