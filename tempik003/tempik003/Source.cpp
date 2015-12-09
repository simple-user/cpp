#include <iostream>
#include <array>
#include <algorithm>

using namespace std;

class A
{
public:
	A() : publicA(1), privateA(2) {}
	int publicA;
	int getA() { return privateA; }
private:
	int privateA;
};

class B : public A
{
public:
	B() : publicB(3), privateB(4) {}
	int publicB;
	int getB() { return privateB; }
private:
	int privateB;
};

int f(int a)
{
	return 1;
}





int main()
{

	int(*some)(int);
	typedef int(*some1)(int);

	some = f;
	some1 f0 = f;


	A a;
	cout << "pub A = " << a.publicA << endl;
	cout << "priv A = " << a.getA() << endl;
	cout << endl;
	B b;
	b.publicA = 5;
	cout << "pub B = " << b.publicB << endl;
	cout << "priv B = " << b.getB() << endl;
	cout << "pub Ba = " << b.publicA << endl;
	cout << "priv Ba = " << b.getA() << endl;

	a = b;

	cout << "pub A = " << a.publicA << endl;
	cout << "priv A = " << a.getA() << endl;


	return 0;
}