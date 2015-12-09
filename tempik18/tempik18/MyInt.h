#pragma once
#include <iostream>
class MyInt
{
private:
	int num;
public:
	MyInt() :num(0) {}
	MyInt(int a) : num(a) {}
	MyInt& operator++()	{ num++; return *this; }
	MyInt operator++(int notused) 
	{ 
		MyInt t(*this);
		num++;
		return t; }
	friend std::ostream& operator<<(std::ostream& os, const MyInt& m) { os << m.num; return os; }
};


