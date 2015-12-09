#pragma once
#include "string"
#define _STD_BEGIN	namespace std {
#define _STD_END		}


_STD_BEGIN

enum Type { INT, DOUBLE, XS };


class Var
{
public:
	Var() : type(INT), Ivar(0), indexator(0){}
	Var(const int i) : type(INT), Ivar(i),  indexator(0){}
	Var(const double d) : type(DOUBLE), Dvar(d), indexator(0) {}
	Var(const std::string x) : type(XS), Xvar(x), indexator(0) {}
	Var(Var &&v) : type(v.type), Ivar(v.Ivar), Dvar(v.Dvar), Xvar(std::move(v.Xvar)), indexator(v.indexator) {}
	explicit Var(const char* s) : type(XS), Xvar(s), indexator(0) {}
		
	Var& operator += (int i);
	Var& operator -= (int i);
	Var& operator *= (int i);
	Var& operator += (double d);
	Var& operator -= (double d);
	Var& operator *= (double d);
	Var& operator += (const string & xs);
	Var& operator -= (const string & xs);
	Var& operator *= (const string & xs);

	template<typename T> friend T operator += (T &t, Var& v)
	{
		v.assign();
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
	template<typename T> friend T operator -= (T &t, Var& v)
	{
		v.assign(); 
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
	template<typename T> friend T operator *= (T &t, Var& v)
	{
		v.assign();
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
	Var operator + (double i);
	Var operator - (double i);
	Var operator * (double i);
	Var operator + (string i);
	Var operator - (string i);
	Var operator * (string i);

	template<typename T> friend T operator + (T &t, Var& v)
	{
		v.assign();
		T t2 = t;
		t2 += v;
		return t2;
	}
	template<typename T> friend T operator - (T &t, Var& v)
	{
		v.assign();
		T t2 = t;
		t2 -= v;
		return t2;
	}
	template<typename T> friend T operator * (T &t, Var& v)
	{
		v.assign();
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
	bool operator < (const string & xs);
	bool operator <= (const string & xs);
	bool operator > (const string & xs);
	bool operator >= (const string & xs);
	bool operator == (const string & xs);
	bool operator != (const string & xs);
	
	template<typename T> friend bool operator < (T &t, Var& v)
	{
		v.assign();
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
	template<typename T> friend bool operator > (T &t, Var& v)
	{
		v.assign();
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
	template<typename T> friend bool operator <= (T &t, Var& v)
	{
		// v.assign();
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
	template<typename T> friend bool operator >= (T &t, Var& v)
	{
		v.assign();
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
	template<typename T> friend bool operator == (T &t, Var& v)
	{
		v.assign();
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
	template<typename T> friend bool operator != (T &t, Var& v)
	{
		v.assign();
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
	
	friend ostream& operator<<(ostream& os, Var& var);
	friend istream& operator>>(istream& is, Var& var);
	
	char & operator[](int index);
	
private:
	int Ivar;
	double Dvar;
	std::string Xvar;
	Type type;
	bool indexator;
	int symbIndex;
	void assign();
};

_STD_END