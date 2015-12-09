#pragma once
#include "Xstring.h"
#define _STD_BEGIN	namespace std {
#define _STD_END		}

_STD_BEGIN
enum Type { INT, DOUBLE, XS };
class Var
{
public:
	Var() : type(INT), Ivar(0) {}
	Var(const int i) : type(INT), Ivar(i) {}
	Var(const double d) : type(DOUBLE), Dvar(d) {}
	Var(const std::Xstring x) : type(XS), Xvar(x) {}
	explicit Var(const char* s) : type(XS), Xvar(s) {}
		

	void * sum(void* i1, void* i2, Type type)
	{
		switch (type)
		{
		case INT:
			int *temp = new int(*((int*)i1) + *((int*)i2));
			return temp;
			break;
		}
	}

	friend Var calc(const Var& v1, const Var& v2, void* (*oper)(void*, void*, Type))
	{
		Var res;
		switch (v1.type)
		{
		case INT: 
			switch (v2.type)
			{
			case INT:
				int *temp = (int*)oper(&v1.Ivar, &v2.type, INT);
				res.type = INT;
				res.Ivar = *temp;
				delete temp;
				break;
			}
			break;
		}
	}


	Var operator+(const Var& v)
	{
		return calc(*this, v, );
	}
	Var operator-(const Var& v);
	Var operator*(const Var& v);
	Var operator/(const Var& v);

	friend ostream& operator<<(ostream& os, const Var& var)
	{
		switch (var.type)
		{
		case INT:
			os << var.Ivar;
			break;
		case DOUBLE:
			os << var.Dvar;
			break;
		case XS:
			os << var.Xvar;
			break;
		}
		return os;
	}


private:
	int Ivar;
	double Dvar;
	std::Xstring Xvar;
	Type type;
};

_STD_END