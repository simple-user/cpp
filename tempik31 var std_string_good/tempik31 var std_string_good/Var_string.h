#pragma once
#include "string"
#define _STD_BEGIN	namespace std {
#define _STD_END		}


_STD_BEGIN

enum Type { INT, DOUBLE, XS };


class Var
{
private:
	struct Indexator;
public:
	Var() : type(INT), Ivar(0){}
	Var(const int i) : type(INT), Ivar(i){}
	Var(const double d) : type(DOUBLE), Dvar(d) {}
	Var(const std::string x) : type(XS), Xvar(x) {}
	Var(Var &&v) : type(v.type), Ivar(v.Ivar), Dvar(v.Dvar), Xvar(std::move(v.Xvar)) {}
	explicit Var(const char* s) : type(XS), Xvar(s) {}
		
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
	Indexator operator[](int index);
	inline void assign()
	{
		// дана функц≥€ викликаЇтьс€ в кожн≥й операц≥њ
		// тому щоб кругом не видал€ти показую що вона пуста ≥ н≥чого не робить
	}

private:
	int Ivar;
	double Dvar;
	std::string Xvar;
	Type type;
	
	struct Indexator
	{
		Indexator(int &i, double &d, string &x, Type t, int index) :  I(&i), D(&d), X(&x), T(t), Index(index) {}

		Indexator & operator=(char ch)
		{

			(*X)[Index] = ch;

			if (T == XS)
				return *this;
			
			if (ch < '0' || ch > '9')
				throw std::invalid_argument(std::string("Invalid argument by operator[]. \"") + ch + "\" is not a number!");

			switch (T)
			{
			case std::INT:
				*I = std::stoi(*X);
				break;
			case std::DOUBLE:
				*D = std::stod(*X);
				break;
			}
			return *this;
		}

		friend ostream& operator<<(ostream &os, const Indexator &ind)
		{
			os << (*ind.X)[ind.Index];
			return os;
		}

		// без вказ≥вник≥в щось нав≥ть не у€вл€ю €к написати... 
		int *I;
		double *D;
		string *X;
		Type T;
		int Index;
	};

};

_STD_END