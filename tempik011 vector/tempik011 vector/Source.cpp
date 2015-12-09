#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <vector>

using namespace std;


class A
{
	int a;
public:
	A(int _a) : a(_a) {}
	virtual void f() { cout << "In A. a = " << a << endl; }
};

class B : public A
{
	int b;
public:
	B(int _a, int _b) : A(_a), b(_b) {}
	final void f() 
	{ 
		cout << "In B.";
		A::f();
		cout << "b = " << b << endl; 
	}

	void f1() { cout << "asdasd" << endl; }
};


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	/*A a(1);
	a.f();
*/
	B b(1,2);
	//b.f();
	

	cout << "*a1" << endl;
	A *a1 = &b;
	a1->f();
	


	return 0;
}