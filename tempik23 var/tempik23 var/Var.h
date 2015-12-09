#pragma once
#include "Xstring.h"
#define _STD_BEGIN	namespace std {
#define _STD_END		}

_STD_BEGIN
class Var
{
public:
	Var() : type(INT), Ivar(0) {}
	Var(const int i) : type(INT), Ivar(i) {}
	Var(const double d) : type(DOUBLE), Dvar(d) {}
	Var(const std::Xstring x) : type(XS), Xvar(x) {}
	explicit Var(const char* s) : type(XS), Xvar(s) {}
		
	Var& operator+=(int i)
	{
		switch (type)
		{
		case INT:
			Ivar +=  i;
			break;
		case DOUBLE:
			Dvar +=  i;
			break;
		case XS:
			char ch[20] = {};
			_itoa_s(i, ch, 20, 10);
			Xvar += ch;
			break;
		}
		return *this;
	}
	Var& operator+=(double d)
	{
		switch (type)
		{
		case INT:
			Ivar += d;
			break;
		case DOUBLE:
			Dvar += d;
			break;
		case XS:
			char ch[20] = {};
			Xvar += std::to_string(d).c_str();
			break;
		}
		return *this;
	}
	Var& operator+=(const Xstring & xs)
	{
		
		switch (type)
		{
		case INT:
			Ivar += xs;
			break;
		case DOUBLE:
			Dvar += xs;
			break;
		case XS:
			Xvar += xs;
			break;
		}
		return *this;
	}

	template<typename T>
	friend T operator+=(T &t, const Var& v)
	{
		switch (v.type)
		{
		case INT:
			return t += v.Ivar;	break;
		case DOUBLE:
			return t += v.Dvar;	break;
		case XS:
			return t += v.Xvar;	break;
		}
		return 0;
	}

	Var operator+(int i)
	{
		Var tempVar(*this);
		tempVar += i;
		return tempVar;
	}
	template<typename T>
	friend T operator+(const T &t, const Var& v)
	{
		T t2 = t;
		t2 += v;
		return t2;
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
	enum {INT,DOUBLE,XS} type;
};

_STD_END