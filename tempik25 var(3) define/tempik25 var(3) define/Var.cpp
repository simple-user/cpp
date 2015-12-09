#include "Var.h"
#define _STD_BEGIN	namespace std {
#define _STD_END		}


_STD_BEGIN
std::Xstring& operator-=(std::Xstring& xs1, const std::Xstring& xs2)
{
	return xs1;
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

