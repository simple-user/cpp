#include <iostream>
#include <array>
#include <algorithm>

using namespace std;

class A
{
public:
	// A() : publicA(1), privateA(2) {}
	A(int i1) : publicA(i1) {}
	int publicA;
	int getA() { return privateA; }
private:
	int privateA;
};

class B1 : virtual public A
{
public:
	// B1() : publicB1(3), privateB1(4) {}
	B1(int b1, int a) : publicB1(b1),  A(a) {}
	int publicB1;
	int getB1() { return privateB1; }
private:
	int privateB1;
};

class B2 : virtual public A
{
public:
	// B2() : publicB2(3), privateB2(4) {}
	B2(int b2, int a) : publicB2(b2), A(a) {}
	int publicB2;
	int getB2() { return privateB2; }
private:
	int privateB2;
};


class C : public B1, public B2
{
public:
	C(int c, int b1, int b1a, int b2, int b2a, int a) : publicC(c),  B1(b1, b1a), B2(b2,b2a), A(a) {}
	int publicC;
	int getC() { return privateC; }
private:
	int privateC;


};


int main()
{

	A a(1);
	cout << "a.publicA = " << a.publicA << endl;

	B1 b1(3,2);
	cout << "b1.publicA = " << b1.publicA << endl;
	cout << "b1.publikB1 = " << b1.publicB1 << endl;

	B2 b2(5,4);
	cout << "b2.publicA = " << b2.publicA << endl;
	cout << "b2.publikB1 = " << b2.publicB2 << endl;

	C c(6, 3, 2, 5, 4, 1);

	cout << "c.publicA = " << c.publicA << endl;
	cout << "c.publicB1 = " << c.publicB1 << endl;
	cout << "c.publicB2 = " << c.publicB2 << endl;
	cout << "c.publicC = " << c.publicC << endl;


	return 0;
}