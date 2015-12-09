#include <iostream>
#include <Windows.h>

using namespace std;


class A
{
public:
	virtual void f() { cout << "in A \n"; }
};

class B : public A
{
public:
	//virtual void f() { cout << "in B \n"; }


};


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	A a; 
	B b;
	A *p = &a;
	p->f();
	p = &b;
	p->f();
	
	return 0;

}

