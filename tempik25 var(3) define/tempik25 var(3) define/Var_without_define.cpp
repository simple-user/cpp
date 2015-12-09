#include "Var.h"
#define _STD_BEGIN	namespace std {
#define _STD_END		}


_STD_BEGIN
std::Xstring& operator-=(std::Xstring& xs1, const std::Xstring& xs2)
{
	return xs1;
}

Var& Var::operator += (int i)
{
	switch (type)
	{
	case INT: Ivar += i;
		break;
	case DOUBLE: Dvar += i;
		break;
	case XS: char ch[20] =
	{
	}
			 ;
			 _itoa_s(i, ch, 20, 10);
			 Xvar += ch;
			 break;
	}
	return *this;
}
Var& Var::operator -= (int i)
{
	switch (type)
	{
	case INT: Ivar -= i;
		break;
	case DOUBLE: Dvar -= i;
		break;
	case XS: char ch[20] =
	{
	}
			 ;
			 _itoa_s(i, ch, 20, 10);
			 Xvar -= ch;
			 break;
	}
	return *this;
}
Var& Var::operator *= (int i)
{
	switch (type)
	{
	case INT: Ivar *= i;
		break;
	case DOUBLE: Dvar *= i;
		break;
	case XS: char ch[20] =
	{
	}
			 ;
			 _itoa_s(i, ch, 20, 10);
			 Xvar *= ch;
			 break;
	}
	return *this;
}
Var& Var::operator += (double d)
{
	switch (type)
	{
	case INT: Ivar += d;
		break;
	case DOUBLE: Dvar += d;
		break;
	case XS: Xvar += std::to_string(d).c_str();
		break;
	}
	return *this;
}
Var& Var::operator -= (double d)
{
	switch (type)
	{
	case INT: Ivar -= d;
		break;
	case DOUBLE: Dvar -= d;
		break;
	case XS: Xvar -= std::to_string(d).c_str();
		break;
	}
	return *this;
}
Var& Var::operator *= (double d)
{
	switch (type)
	{
	case INT: Ivar *= d;
		break;
	case DOUBLE: Dvar *= d;
		break;
	case XS: Xvar *= std::to_string(d).c_str();
		break;
	}
	return *this;
}
Var& Var::operator += (const Xstring & xs)
{
	switch (type)
	{
	case INT: Ivar += xs;
		break;
	case DOUBLE: Dvar += xs;
		break;
	case XS: Xvar += xs;
		break;
	}
	return *this;
}
Var& Var::operator -= (const Xstring & xs)
{
	switch (type)
	{
	case INT: Ivar -= xs;
		break;
	case DOUBLE: Dvar -= xs;
		break;
	case XS: Xvar -= xs;
		break;
	}
	return *this;
}
Var& Var::operator *= (const Xstring & xs)
{
	switch (type)
	{
	case INT: Ivar *= xs;
		break;
	case DOUBLE: Dvar *= xs;
		break;
	case XS: Xvar *= xs;
		break;
	}
	return *this;
}

Var Var::operator + (int i)
{
	Var tempVar(*this);
	tempVar += i;
	return tempVar;
}
Var Var::operator - (int i)
{
	Var tempVar(*this);
	tempVar -= i;
	return tempVar;
}
Var Var::operator * (int i)
{
	Var tempVar(*this);
	tempVar *= i;
	return tempVar;
}
Var Var::operator + (double i)
{
	Var tempVar(*this);
	tempVar += i;
	return tempVar;
}
Var Var::operator - (double i)
{
	Var tempVar(*this);
	tempVar -= i;
	return tempVar;
}
Var Var::operator * (double i)
{
	Var tempVar(*this);
	tempVar *= i;
	return tempVar;
}
Var Var::operator + (Xstring i)
{
	Var tempVar(*this);
	tempVar += i;
	return tempVar;
}
Var Var::operator - (Xstring i)
{
	Var tempVar(*this);
	tempVar -= i;
	return tempVar;
}
Var Var::operator * (Xstring i)
{
	Var tempVar(*this);
	tempVar *= i;
	return tempVar;
}

bool Var::operator < (int i)
{
	switch (type)
	{
	case INT: return Ivar < i;
		break;
	case DOUBLE: return Dvar < i;
		break;
	case XS: char ch[20] =
	{
	}
			 ;
			 _itoa_s(i, ch, 20, 10);
			 return strcmp(Xvar.c_str(), ch) < 0;
			 break;
	}
	return 0;
}
bool Var::operator <= (int i)
{
	switch (type)
	{
	case INT: return Ivar <= i;
		break;
	case DOUBLE: return Dvar <= i;
		break;
	case XS: char ch[20] =
	{
	}
			 ;
			 _itoa_s(i, ch, 20, 10);
			 return strcmp(Xvar.c_str(), ch) <= 0;
			 break;
	}
	return 0;
}
bool Var::operator > (int i)
{
	switch (type)
	{
	case INT: return Ivar > i;
		break;
	case DOUBLE: return Dvar > i;
		break;
	case XS: char ch[20] =
	{
	}
			 ;
			 _itoa_s(i, ch, 20, 10);
			 return strcmp(Xvar.c_str(), ch) > 0;
			 break;
	}
	return 0;
}
bool Var::operator >= (int i)
{
	switch (type)
	{
	case INT: return Ivar >= i;
		break;
	case DOUBLE: return Dvar >= i;
		break;
	case XS: char ch[20] =
	{
	}
			 ;
			 _itoa_s(i, ch, 20, 10);
			 return strcmp(Xvar.c_str(), ch) >= 0;
			 break;
	}
	return 0;
}
bool Var::operator == (int i)
{
	switch (type)
	{
	case INT: return Ivar == i;
		break;
	case DOUBLE: return Dvar == i;
		break;
	case XS: char ch[20] =
	{
	}
			 ;
			 _itoa_s(i, ch, 20, 10);
			 return strcmp(Xvar.c_str(), ch) == 0;
			 break;
	}
	return 0;
}
bool Var::operator != (int i)
{
	switch (type)
	{
	case INT: return Ivar != i;
		break;
	case DOUBLE: return Dvar != i;
		break;
	case XS: char ch[20] =
	{
	}
			 ;
			 _itoa_s(i, ch, 20, 10);
			 return strcmp(Xvar.c_str(), ch) != 0;
			 break;
	}
	return 0;
}
bool Var::operator < (double i)
{
	switch (type)
	{
	case INT: return Ivar < i;
		break;
	case DOUBLE: return Dvar < i;
		break;
	case XS: char ch[20] =
	{
	}
			 ;
			 return strcmp(Xvar.c_str(), std::to_string(d).c_str()) < 0;
			 break;
	}
	return 0;
}
bool Var::operator <= (double i)
{
	switch (type)
	{
	case INT: return Ivar <= i;
		break;
	case DOUBLE: return Dvar <= i;
		break;
	case XS: char ch[20] =
	{
	}
			 ;
			 return strcmp(Xvar.c_str(), std::to_string(d).c_str()) <= 0;
			 break;
	}
	return 0;
}
bool Var::operator > (double i)
{
	switch (type)
	{
	case INT: return Ivar > i;
		break;
	case DOUBLE: return Dvar > i;
		break;
	case XS: char ch[20] =
	{
	}
			 ;
			 return strcmp(Xvar.c_str(), std::to_string(d).c_str()) > 0;
			 break;
	}
	return 0;
}
bool Var::operator >= (double i)
{
	switch (type)
	{
	case INT: return Ivar >= i;
		break;
	case DOUBLE: return Dvar >= i;
		break;
	case XS: char ch[20] =
	{
	}
			 ;
			 return strcmp(Xvar.c_str(), std::to_string(d).c_str()) >= 0;
			 break;
	}
	return 0;
}
bool Var::operator == (double i)
{
	switch (type)
	{
	case INT: return Ivar == i;
		break;
	case DOUBLE: return Dvar == i;
		break;
	case XS: char ch[20] =
	{
	}
			 ;
			 return strcmp(Xvar.c_str(), std::to_string(d).c_str()) == 0;
			 break;
	}
	return 0;
}
bool Var::operator != (double i)
{
	switch (type)
	{
	case INT: return Ivar != i;
		break;
	case DOUBLE: return Dvar != i;
		break;
	case XS: char ch[20] =
	{
	}
			 ;
			 return strcmp(Xvar.c_str(), std::to_string(d).c_str()) != 0;
			 break;
	}
	return 0;
}
Var& Var::operator < (const Xstring & xs)
{
	switch (type)
	{
	case INT: return Ivar < xs;
		break;
	case DOUBLE: return Dvar < xs;
		break;
	case XS: return Xvar < xs;
		break;
	}
	return 0;
}
Var& Var::operator <= (const Xstring & xs)
{
	switch (type)
	{
	case INT: return Ivar <= xs;
		break;
	case DOUBLE: return Dvar <= xs;
		break;
	case XS: return Xvar <= xs;
		break;
	}
	return 0;
}
Var& Var::operator > (const Xstring & xs)
{
	switch (type)
	{
	case INT: return Ivar > xs;
		break;
	case DOUBLE: return Dvar > xs;
		break;
	case XS: return Xvar > xs;
		break;
	}
	return 0;
}
Var& Var::operator >= (const Xstring & xs)
{
	switch (type)
	{
	case INT: return Ivar >= xs;
		break;
	case DOUBLE: return Dvar >= xs;
		break;
	case XS: return Xvar >= xs;
		break;
	}
	return 0;
}
Var& Var::operator == (const Xstring & xs)
{
	switch (type)
	{
	case INT: return Ivar == xs;
		break;
	case DOUBLE: return Dvar == xs;
		break;
	case XS: return Xvar == xs;
		break;
	}
	return 0;
}
Var& Var::operator != (const Xstring & xs)
{
	switch (type)
	{
	case INT: return Ivar != xs;
		break;
	case DOUBLE: return Dvar != xs;
		break;
	case XS: return Xvar != xs;
		break;
	}
	return 0;
}


ostream& operator<<(ostream& os, const Var& var)
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

istream& operator>>(istream& is, Var& var)
{
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
_STD_END

