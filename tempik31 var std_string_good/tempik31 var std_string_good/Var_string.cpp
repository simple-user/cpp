#include "Var_string.h"
#define _STD_BEGIN	namespace std {
#define _STD_END		}


_STD_BEGIN
Var& Var::operator += (int i)
{
	assign();
	switch (type)
	{
	case INT: 
		Ivar += i;
		break;
	case DOUBLE: 
		Dvar += i;
		break;
	case XS: 
		Xvar += std::to_string(i);
		break;
	}
	return *this;
}
Var& Var::operator -= (int i)
{
	assign();
	switch (type)
	{
	case INT: Ivar -= i;
		break;
	case DOUBLE: Dvar -= i;
		break;
	case XS: /* Xvar -= std::to_string(i); */
			 break;
	}
	return *this;
}
Var& Var::operator *= (int i)
{
	assign();
	switch (type)
	{
	case INT: Ivar *= i;
		break;
	case DOUBLE: Dvar *= i;
		break;
	case XS: /* Xvar *= to_string(i); */
			 break;
	}
	return *this;
}
Var& Var::operator += (double d)
{
	assign();
	switch (type)
	{
	case INT: Ivar += d;
		break;
	case DOUBLE: Dvar += d;
		break;
	case XS: Xvar += std::to_string(d);
		break;
	}
	return *this;
}
Var& Var::operator -= (double d)
{
	assign();
	switch (type)
	{
	case INT: Ivar -= d;
		break;
	case DOUBLE: Dvar -= d;
		break;
	case XS: /* Xvar -= std::to_string(d); */
		break;
	}
	return *this;
}
Var& Var::operator *= (double d)
{
	assign();
	switch (type)
	{
	case INT: Ivar *= d;
		break;
	case DOUBLE: Dvar *= d;
		break;
	case XS: /* Xvar *= std::to_string(d); */
		break;
	}
	return *this;
}
Var& Var::operator += (const string & xs)
{
	assign();
	switch (type)
	{
	case INT: try { Ivar += stoi(xs); }	catch (...)	{}
		break;
	case DOUBLE: try { Dvar += stod(xs); } catch (...) {}
		break;
	case XS: Xvar += xs;
		break;
	}
	return *this;
}
Var& Var::operator -= (const string & xs)
{
	assign();
	switch (type)
	{
	case INT: try { Ivar -= stoi(xs); } catch (...)	{}
		break;
	case DOUBLE: try { Dvar -= stod(xs); } catch (...) {}
		break;
	case XS: /* Xvar -= xs; */
		break;
	}
	return *this;
}
Var& Var::operator *= (const string & xs)
{
	assign();
	switch (type)
	{
	case INT: try { Ivar *= stoi(xs); } catch (...) {}
		break;
	case DOUBLE: try { Dvar *= stod(xs); } catch (...) {}
		break;
	case XS:/* Xvar *= xs; */
		break;
	}
	return *this;
}

Var Var::operator + (int i)
{
	assign();
	Var tempVar(*this);
	tempVar += i;
	return tempVar;
}
Var Var::operator - (int i)
{
	assign();
	Var tempVar(*this);
	tempVar -= i;
	return tempVar;
}
Var Var::operator * (int i)
{
	assign();
	Var tempVar(*this);
	tempVar *= i;
	return tempVar;
}
Var Var::operator + (double i)
{
	assign();
	Var tempVar(*this);
	tempVar += i;
	return tempVar;
}
Var Var::operator - (double i)
{
	assign();
	Var tempVar(*this);
	tempVar -= i;
	return tempVar;
}
Var Var::operator * (double i)
{
	assign();
	Var tempVar(*this);
	tempVar *= i;
	return tempVar;
}
Var Var::operator + (string i)
{
	assign();
	Var tempVar(*this);
	tempVar += i;
	return tempVar;
}
Var Var::operator - (string i)
{
	assign();
	Var tempVar(*this);
	tempVar -= i;
	return tempVar;
}
Var Var::operator * (string i)
{
	assign();
	Var tempVar(*this);
	tempVar *= i;
	return tempVar;
}

bool Var::operator < (int i)
{
	assign();
	switch (type)
	{
	case INT: return Ivar < i;
		break;
	case DOUBLE: return Dvar < i;
		break;
	case XS: return Xvar < to_string(i);
			 break;
	}
	return 0;
}
bool Var::operator <= (int i)
{
	assign();
	switch (type)
	{
	case INT: return Ivar <= i;
		break;
	case DOUBLE: return Dvar <= i;
		break;
	case XS: return Xvar <= to_string(i);
			 break;
	}
	return 0;
}
bool Var::operator > (int i)
{
	assign();
	switch (type)
	{
	case INT: return Ivar > i;
		break;
	case DOUBLE: return Dvar > i;
		break;
	case XS: return Xvar > to_string(i);
			 break;
	}
	return 0;
}
bool Var::operator >= (int i)
{
	assign();
	switch (type)
	{
	case INT: return Ivar >= i;
		break;
	case DOUBLE: return Dvar >= i;
		break;
	case XS: return Xvar >= to_string(i);
			 break;
	}
	return 0;
}
bool Var::operator == (int i)
{
	assign();
	switch (type)
	{
	case INT: return Ivar == i;
		break;
	case DOUBLE: return Dvar == i;
		break;
	case XS: return Xvar == to_string(i);
			 break;
	}
	return 0;
}
bool Var::operator != (int i)
{
	assign();
	switch (type)
	{
	case INT: return Ivar != i;
		break;
	case DOUBLE: return Dvar != i;
		break;
	case XS: return Xvar != to_string(i);
			 break;
	}
	return 0;
}
bool Var::operator < (double i)
{
	assign();
	switch (type)
	{
	case INT: return Ivar < i;
		break;
	case DOUBLE: return Dvar < i;
		break;
	case XS: return Xvar < to_string(i);
			 break;
	}
	return 0;
}
bool Var::operator <= (double i)
{
	assign();
	switch (type)
	{
	case INT: return Ivar <= i;
		break;
	case DOUBLE: return Dvar <= i;
		break;
	case XS: return Xvar <= to_string(i);
			 break;
	}
	return 0;
}
bool Var::operator > (double i)
{
	assign();
	switch (type)
	{
	case INT: return Ivar > i;
		break;
	case DOUBLE: return Dvar > i;
		break;
	case XS: return Xvar > to_string(i);
			 break;
	}
	return 0;
}
bool Var::operator >= (double i)
{
	assign();
	switch (type)
	{
	case INT: return Ivar >= i;
		break;
	case DOUBLE: return Dvar >= i;
		break;
	case XS: return Xvar >= to_string(i);
			 break;
	}
	return 0;
}
bool Var::operator == (double i)
{
	assign();
	switch (type)
	{
	case INT: return Ivar == i;
		break;
	case DOUBLE: return Dvar == i;
		break;
	case XS: return Xvar == to_string(i);
			 break;
	}
	return 0;
}
bool Var::operator != (double i)
{
	assign();
	switch (type)
	{
	case INT: return Ivar != i;
		break;
	case DOUBLE: return Dvar != i;
		break;
	case XS: return Xvar != to_string(i);
			 break;
	}
	return 0;
}
bool Var::operator < (const string & xs)
{
	assign();
	switch (type)
	{
	case INT: return Ivar < stoi(xs);
		break;
	case DOUBLE: return Dvar < stod(xs);
		break;
	case XS: return Xvar < xs;
		break;
	}
	return 0;
}
bool Var::operator <= (const string & xs)
{
	assign();
	switch (type)
	{
	case INT: return Ivar <= stoi(xs);
		break;
	case DOUBLE: return Dvar <= stod(xs);
		break;
	case XS: return Xvar <= xs;
		break;
	}
	return 0;
}
bool Var::operator > (const string & xs)
{
	assign();
	switch (type)
	{
	case INT: return Ivar > stoi(xs);
		break;
	case DOUBLE: return Dvar > stod(xs);
		break;
	case XS: return Xvar > xs;
		break;
	}
	return 0;
}
bool Var::operator >= (const string & xs)
{
	assign();
	switch (type)
	{
	case INT: return Ivar >= stoi(xs);
		break;
	case DOUBLE: return Dvar >= stod(xs);
		break;
	case XS: return Xvar >= xs;
		break;
	}
	return 0;
}
bool Var::operator == (const string & xs)
{
	assign();
	switch (type)
	{
	case INT: return Ivar == stoi(xs);
		break;
	case DOUBLE: return Dvar == stod(xs);
		break;
	case XS: return Xvar == xs;
		break;
	}
	return 0;
}
bool Var::operator != (const string & xs)
{
	assign();
	switch (type)
	{
	case INT: return Ivar != stoi(xs);
		break;
	case DOUBLE: return Dvar != stod(xs);
		break;
	case XS: return Xvar != xs;
		break;
	}
	return 0;
}


ostream& operator<<(ostream& os, Var& var)
{
	var.assign();
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
istream& operator>>(istream& is, Var& var)
{
	var.assign();
	switch (var.type)
	{
	case INT:
		is >> var.Ivar;
		break;
	case DOUBLE:
		is >> var.Dvar;
		break;
	case XS:
		is >> var.Xvar;
		break;
	}
	return is;
}

Var::Indexator Var::operator[](int index)
{
	switch (type)
	{
	case std::INT:
		{
			std::string t = to_string(Ivar);
			if (index <0 || index>t.size() - 1)
				throw std::out_of_range("Index " + std::to_string(index) + " out of range. Min=0, max=" + to_string(t.size() - 1) + " in operator[] for int.");
			Xvar = t;
		}
		break;
	case std::DOUBLE:
		{
			std::string t = std::to_string(Dvar);
			size_t i = t.find_first_of(".,");
			if (i == string::npos)
				i = t.size();

			if (index >0 && index > i - 1) // число додатнє і воно більше ніж кількість символів до крапочки -1 (бо індексується з 0)
				throw std::out_of_range("Index " + std::to_string(index) + " out of range. Min=0, max=" + to_string(i) + " in operator[] double.");
			else if (index < 0 && index < (t.size() - i - 1)*-1) //число від'ємне і менше ніж кільк символів після крапки * -1
				throw std::out_of_range("Index " + std::to_string(index) + " out of range. min=0(-1) max=-" + to_string(t.size() - i - 1) + " in operator[] double.");

			Xvar = t;
			if (index < 0)
				index = (index * -1) + i;
		}
		break;
	case std::XS:
		if (index < 0 || index > Xvar.size() - 1)
			throw std::out_of_range("Index " + std::to_string(index) + " out of range. Min=0, max=" + to_string(Xvar.size() - 1) + " in operator[] string.");

		break;
	}
	

	return Indexator(Ivar, Dvar, Xvar, type, index);
}

_STD_END

