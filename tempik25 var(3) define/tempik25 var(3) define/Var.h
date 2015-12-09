#pragma once
#include "Xstring.h"
#include "string"
#define _STD_BEGIN	namespace std {
#define _STD_END		}

#define VAR_ZN_DOR_INT(_ZN_) Var& operator _ZN_ (int i) \
	{													\
		switch (type)									\
		{												\
		case INT:										\
			Ivar _ZN_ i;								\
			break;										\
		case DOUBLE:									\
			Dvar _ZN_ i;								\
			break;										\
		case XS:										\
			char ch[20] = {};							\
			_itoa_s(i, ch, 20, 10);						\
			Xvar _ZN_ ch;								\
			break;										\
		}												\
		return *this;									\
	} 

#define VAR_ZN_DOR_DOUBLE(_ZN_) 	Var& operator _ZN_ (double d)	\
	{																\
		switch (type)												\
		{															\
		case INT:													\
			Ivar _ZN_ d;											\
			break;													\
		case DOUBLE:												\
			Dvar _ZN_ d;											\
			break;													\
		case XS:													\
			Xvar _ZN_ std::to_string(d).c_str();					\
			break;													\
		}															\
		return *this;												\
	}

#define VAR_ZN_DOR_XS(_ZN_) Var& operator _ZN_ (const Xstring & xs) \
{																	\
	switch (type)													\
	{																\
	case INT:														\
		Ivar _ZN_ xs;												\
		break;														\
	case DOUBLE:													\
		Dvar _ZN_ xs;												\
		break;														\
	case XS:														\
		Xvar _ZN_ xs;												\
		break;														\
	}																\
	return *this;													\
}

#define TEMPLATE_T_ZN_DOR_VAR(_ZN_) template<typename T>	\
friend T operator _ZN_ (T &t, const Var& v)					\
{															\
	switch (v.type)											\
	{														\
	case INT:												\
		return t _ZN_ v.Ivar;	break;						\
	case DOUBLE:											\
		return t _ZN_ v.Dvar;	break;						\
	case XS:												\
		return t _ZN_ v.Xvar;	break;						\
	}														\
	return 0;												\
}

#define VAR_ZN_INT(_ZN_) Var operator _ZN_ (int i)	\
	{												\
		Var tempVar(*this);							\
		tempVar _ZN_= i;							\
		return tempVar;								\
	}

#define VAR_ZN_DOUBLE(_ZN_) Var operator _ZN_ (double i)	\
	{														\
	Var tempVar(*this);										\
	tempVar _ZN_= i;										\
	return tempVar;											\
}

#define VAR_ZN_XS(_ZN_) Var operator _ZN_ (Xstring i)	\
	{													\
	Var tempVar(*this);									\
	tempVar _ZN_= i;									\
	return tempVar;										\
	}

#define TEMPLATE_T_ZN_VAR(_ZN_) template<typename T>	\
friend T operator _ZN_ (const T &t, const Var& v)		\
{														\
	T t2 = t;											\
	t2 _ZN_= v;											\
	return t2;											\
}

#define VAR_ZN_BS_INT(_ZN_) bool operator _ZN_ (int i)  \
	{													\
		switch (type)									\
		{												\
		case INT:										\
			return Ivar _ZN_ i;							\
			break;										\
		case DOUBLE:									\
			return Dvar _ZN_ i;							\
			break;										\
		case XS:										\
			char ch[20] = {};							\
			_itoa_s(i, ch, 20, 10);						\
			return strcmp(Xvar.c_str(), ch) _ZN_ 0;		\
			break;										\
		}												\
		return 0;										\
	} 

#define VAR_ZN_BS_DOUBLE(_ZN_) bool operator _ZN_ (double i)		\
	{																\
		switch (type)												\
		{															\
		case INT:													\
			return Ivar _ZN_ i;										\
			break;													\
		case DOUBLE:												\
			return Dvar _ZN_ i;										\
			break;													\
		case XS:													\
			char ch[20] = {};										\
			return strcmp(Xvar.c_str(), std::to_string(i).c_str()) _ZN_ 0;	\
			break;													\
		}															\
		return 0;													\
	} 

#define VAR_ZN_BS_XS(_ZN_) bool operator _ZN_ (const Xstring & xs)	\
{																	\
	switch (type)													\
	{																\
	case INT:														\
		return Ivar _ZN_ xs;										\
		break;														\
	case DOUBLE:													\
		return Dvar _ZN_ xs;										\
		break;														\
	case XS:														\
		return Xvar _ZN_ xs;										\
		break;														\
	}																\
	return 0;														\
}


#define TEMPLATE_T_ZN_BS_VAR(_ZN_) template<typename T>	\
	friend bool operator _ZN_ (const T &t, const Var& v)					\
{															\
	switch (v.type)											\
	{														\
	case INT:												\
	return t _ZN_ v.Ivar;	break;						\
	case DOUBLE:											\
	return t _ZN_ v.Dvar;	break;						\
	case XS:												\
	return t _ZN_ v.Xvar;	break;						\
	}														\
	return 0;												\
}

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
		
	
	VAR_ZN_DOR_INT(+= )
	VAR_ZN_DOR_INT(-= )
	VAR_ZN_DOR_INT(*= )

	VAR_ZN_DOR_DOUBLE(+= )
	VAR_ZN_DOR_DOUBLE(-= )
	VAR_ZN_DOR_DOUBLE(*= )

	VAR_ZN_DOR_XS(+= )
	VAR_ZN_DOR_XS(-= )
	VAR_ZN_DOR_XS(*= )

	TEMPLATE_T_ZN_DOR_VAR(+= )
	TEMPLATE_T_ZN_DOR_VAR(-= )
	TEMPLATE_T_ZN_DOR_VAR(*= )

	VAR_ZN_INT(+)
	VAR_ZN_INT(-)
	VAR_ZN_INT(*)

	VAR_ZN_DOUBLE(+)
	VAR_ZN_DOUBLE(-)
	VAR_ZN_DOUBLE(*)

	VAR_ZN_XS(+)
	VAR_ZN_XS(-)
	VAR_ZN_XS(*)


	TEMPLATE_T_ZN_VAR(+)
	TEMPLATE_T_ZN_VAR(-)
	TEMPLATE_T_ZN_VAR(*)

	VAR_ZN_BS_INT(<)
	VAR_ZN_BS_INT(<=)
	VAR_ZN_BS_INT(>)
	VAR_ZN_BS_INT(>=)
	VAR_ZN_BS_INT(==)
	VAR_ZN_BS_INT(!=)

	VAR_ZN_BS_DOUBLE(<)
	VAR_ZN_BS_DOUBLE(<=)
	VAR_ZN_BS_DOUBLE(>)
	VAR_ZN_BS_DOUBLE(>=)
	VAR_ZN_BS_DOUBLE(==)
	VAR_ZN_BS_DOUBLE(!=)

	VAR_ZN_BS_XS(<)
	VAR_ZN_BS_XS(<=)
	VAR_ZN_BS_XS(>)
	VAR_ZN_BS_XS(>=)
	VAR_ZN_BS_XS(==)
	VAR_ZN_BS_XS(!=)
	
	TEMPLATE_T_ZN_BS_VAR(<)
	TEMPLATE_T_ZN_BS_VAR(>)
	TEMPLATE_T_ZN_BS_VAR(<=)
	TEMPLATE_T_ZN_BS_VAR(>=)
	TEMPLATE_T_ZN_BS_VAR(==)
	TEMPLATE_T_ZN_BS_VAR(!=)
	
	friend ostream& operator<<(ostream& os, const Var& var);
	friend istream& operator>>(istream& is, Var& var);

private:
	int Ivar;
	double Dvar;
	std::Xstring Xvar;
	Type type;
};

_STD_END