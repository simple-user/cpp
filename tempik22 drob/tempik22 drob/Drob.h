#include <iostream>
using namespace std;


class Drob
{
private:
	int A;
	int B;
public:
	Drob() : A(0), B(1){}
	Drob(int a) : A(a), B(1){}
	Drob(int a, int b);
	Drob(double);
	friend ostream& operator<<(ostream &os, const Drob &d);
	Drob operator+(const Drob&) const;
	Drob operator+(const int) const;
	friend Drob operator+(const int, const Drob&);
	
	Drob operator-(const Drob&) const;
	Drob operator-(const int) const;
	friend Drob operator-(const int, const Drob&);
	
	Drob operator*(const Drob&) const;
	Drob operator*(const int) const;
	friend Drob operator*(const int, const Drob&);
	
	Drob operator/(const Drob&) const;
	Drob operator/(const int) const;
	friend Drob operator/(const int, const Drob&);
	
	Drob& operator++();
	Drob operator++(int opa);

	Drob& operator--();
	Drob operator--(int opa);

	operator int();
	operator double();

	void sprost();
};

