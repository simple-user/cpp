#pragma once
#include "Xstring.h"
#include "string"
#define _STD_BEGIN	namespace std {
#define _STD_END		}


_STD_BEGIN

enum Type { INT, DOUBLE, XS };

Xstring& operator-=(Xstring& xs1, const Xstring& xs2);

class Var
{
public:
	Var() : type(INT), Ivar(0) {}
	Var(const int i) : type(INT), Ivar(i) {}
	Var(const double d) : type(DOUBLE), Dvar(d) {}
	Var(const std::Xstring x) : type(XS), Xvar(x) {}
	Var(Var &&v) : type(v.type), Ivar(v.Ivar), Dvar(v.Dvar), Xvar(std::move(v.Xvar)) {}
	explicit Var(const char* s) : type(XS), Xvar(s) {}
		
	
	Var& operator += (int i);
	Var& operator -= (int i);
	Var& operator *= (int i);
	Var& operator += (double d);
	Var& operator -= (double d);
	Var& operator *= (double d);
	Var& operator += (const Xstring & xs);
	Var& operator -= (const Xstring & xs);
	Var& operator *= (const Xstring & xs);
	template<typename T> friend T operator += (T &t, const Var& v)
	{
		switch (v.type)
		{
		case INT: return t += v.Ivar;
			break;
		case DOUBLE: return t += v.Dvar;
			break;
		case XS: return t += v.Xvar;
			break;
		}
		return 0;
	}
	template<typename T> friend T operator -= (T &t, const Var& v)
	{
		switch (v.type)
		{
		case INT: return t -= v.Ivar;
			break;
		case DOUBLE: return t -= v.Dvar;
			break;
		case XS: return t -= v.Xvar;
			break;
		}
		return 0;
	}
	template<typename T> friend T operator *= (T &t, const Var& v)
	{
		switch (v.type)
		{
		case INT: return t *= v.Ivar;
			break;
		case DOUBLE: return t *= v.Dvar;
			break;
		case XS: return t *= v.Xvar;
			break;
		}
		return 0;
	}

	Var operator + (int i);
	Var operator - (int i);
	Var operator * (int i);
	Var operator + (double;
	Var operator - (double i);
	Var operator * (double i);
	Var operator + (Xstring i);
	Var operator - (Xstring i);
	Var operator * (Xstring i);
	template<typename T> friend T operator + (const T &t, const Var& v)
	{
		T t2 = t;
		t2 += v;
		return t2;
	}
	template<typename T> friend T operator - (const T &t, const Var& v)
	{
		T t2 = t;
		t2 -= v;
		return t2;
	}
	template<typename T> friend T operator * (const T &t, const Var& v)
	{
		T t2 = t;
		t2 *= v;
		return t2;
	}

	bool operator < (int i);
	bool operator <= (int i);
	bool operator > (int i);
	bool operator >= (int i);
	bool operator == (int i);
	bool operator != (int i);
	bool operator < (double i);
	bool operator <= (double i);
	bool operator > (double i);
	bool operator >= (double i);
	bool operator == (double i);
	bool operator != (double i);
	Var& operator < (const Xstring & xs);
	Var& operator <= (const Xstring & xs);
	Var& operator > (const Xstring & xs);
	Var& operator >= (const Xstring & xs);
	Var& operator == (const Xstring & xs);
	Var& operator != (const Xstring & xs);
	template<typename T> friend T operator < (const T &t, const Var& v)
	{
		switch (v.type)
		{
		case INT: return t < v.Ivar;
			break;
		case DOUBLE: return t < v.Dvar;
			break;
		case XS: return t < v.Xvar;
			break;
		}
		return 0;
	}
	template<typename T> friend T operator >(const T &t, const Var& v)
	{
		switch (v.type)
		{
		case INT: return t > v.Ivar;
			break;
		case DOUBLE: return t > v.Dvar;
			break;
		case XS: return t > v.Xvar;
			break;
		}
		return 0;
	}
	template<typename T> friend T operator <= (const T &t, const Var& v)
	{
		switch (v.type)
		{
		case INT: return t <= v.Ivar;
			break;
		case DOUBLE: return t <= v.Dvar;
			break;
		case XS: return t <= v.Xvar;
			break;
		}
		return 0;
	}
	template<typename T> friend T operator >= (const T &t, const Var& v)
	{
		switch (v.type)
		{
		case INT: return t >= v.Ivar;
			break;
		case DOUBLE: return t >= v.Dvar;
			break;
		case XS: return t >= v.Xvar;
			break;
		}
		return 0;
	}
	template<typename T> friend T operator == (const T &t, const Var& v)
	{
		switch (v.type)
		{
		case INT: return t == v.Ivar;
			break;
		case DOUBLE: return t == v.Dvar;
			break;
		case XS: return t == v.Xvar;
			break;
		}
		return 0;
	}
	template<typename T> friend T operator != (const T &t, const Var& v)
	{
		switch (v.type)
		{
		case INT: return t != v.Ivar;
			break;
		case DOUBLE: return t != v.Dvar;
			break;
		case XS: return t != v.Xvar;
			break;
		}
		return 0;
	}
	
	friend ostream& operator<<(ostream& os, const Var& var);
	friend istream& operator>>(istream& is, Var& var);

private:
	int Ivar;
	double Dvar;
	std::Xstring Xvar;
	Type type;
};

_STD_END