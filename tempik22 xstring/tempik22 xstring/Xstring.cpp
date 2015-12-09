#include "Xstring.h"

_STD_BEGIN

void Xstring::setStr(char *& dest, const char * const sorce, int lenSorce)
{
	delete[] dest;

	if (sorce)
	{
		dest = new char[lenSorce + 1];
		strcpy_s(dest, lenSorce + 1, sorce);
	}
	else
		dest = nullptr;
}
void swap(Xstring& s1, Xstring& s2)
{
	std::swap(s1.LenText, s2.LenText);
	std::swap(s1.Str, s2.Str);
}

Xstring::Xstring() : Str(nullptr), LenText(0)
{
	setStr(Str,"",0);
}
Xstring::Xstring(const char* s) : Str(nullptr), LenText(strlen(s))
{
	setStr(Str,s,strlen(s));
}
Xstring::Xstring(const Xstring& s) : Str(nullptr), LenText(s.LenText)
{
	setStr(Str,s.Str, s.LenText);	
}
Xstring::Xstring(Xstring &&s) : LenText(s.LenText)
{
	Str=s.Str;
	s.Str=nullptr;
}


// Xstring s = "asdasd";  move c - tor
// Xstring s1 = s;        copy c - tor
Xstring& Xstring::operator=(Xstring s)  
{
	swap(*this, s);
	return *this;
}

std::ostream& operator<<(std::ostream &os, const Xstring& xs)
{
	os << xs.Str;
	return os;
}

inline void Xstring::plus(Xstring& res, const char* str1, const int len1, const char* str2, const int len2) const
{
	res.LenText = len1 + len2;
	res.Str = new char[res.LenText + 1];
	*res.Str = 0;
	strcat_s(res.Str, res.LenText + 1, str1);
	strcat_s(res.Str, res.LenText + 1, str2);
}
Xstring Xstring::operator+(const Xstring &s) const
{
	Xstring t;
	plus(t, Str, LenText, s.Str, s.LenText);
	return t;

}
Xstring operator+(const char* s, const Xstring& xs)
{
	Xstring t;
	xs.plus(t, s, strlen(s), xs.Str, xs.LenText);
	return t;
}

inline void Xstring::mult(Xstring & xs, const char* str1, const int len1, const char* str2) const
{
	int index = 0;
	const char *c = str1;
	char *res = new char[len1 + 1];
	do
	{
		c = strpbrk(c, str2);
		if (c)
		{
			res[index] = *c;
			index++;
			c++;
		}
	} while (c);
	res[index] = 0;

	delete[] xs.Str;
	xs.Str = res;
	xs.LenText = index + 1;
}
Xstring Xstring::operator*(const Xstring &s) const
{
	Xstring t;
	mult(t, Str, LenText, s.Str);
	return t;
}
Xstring operator*(char* s, const Xstring& xs)
{
	Xstring t;
	t.mult(t, s, strlen(s), xs.Str);
	return t;
}

inline void Xstring::div(Xstring & xs, const char* str1, const int len1, const char* str2) const
{
	char * const res = new char[len1+ 1];
	*res = 0;
	strcpy_s(res, len1+ 1, str1);
	char *c = res;
	do
	{
		c = strpbrk(c, str2);
		if (c)
			strcpy_s(c, len1 + 1 - (c - res), c + 1);
	} while (c);

	delete[] xs.Str;
	xs.Str = res;
	xs.LenText = strlen(res);
}
Xstring Xstring::operator/(const Xstring &s) const
{
	Xstring t;
	div(t, Str, LenText, s.Str);
	return t;
}
Xstring operator/(const char* s, const Xstring& xs) 
{
	Xstring t;
	t.div(t, s, strlen(s), xs.Str);
	return t;
}

Xstring& Xstring::operator+=(const Xstring &s)
{
	LenText += s.LenText;
	char *t = new char[LenText+1];
	strcpy_s(t, LenText + 1, Str);
	strcat_s(t, LenText + 1, s.Str);
	delete[] Str;
	Str = t;
	return *this;
}

Xstring& Xstring::operator*=(const Xstring &s)
{
	int index = 0;
	const char *c = Str;
	do
	{
		c = strpbrk(c, s.Str);
		if (c)
		{
			Str[index] = *c;
			index++;
			c++;
		}
	} while (c);
	Str[index] = 0;

	return *this;
}

Xstring& Xstring::operator/=(const Xstring &s)
{
	char *c = Str;
	do
	{
		c = strpbrk(c, s.Str);
		if (c)
			strcpy_s(c, LenText + 1 - (c - Str), c + 1);
	} while (c);

	return *this;
}

char Xstring::operator[](const int index) const
{
	if (index >= 0 && index < LenText)
		return Str[index];
	else
		return 0;
}
Xstring Xstring::operator()(const int start, const int len) const
{
	Xstring xs;
	if (start >= 0 && start < LenText && len <= LenText - start)
	{
		char *t = new char[len + 1];
		strncpy_s(t, len + 1, Str + start, len);
		delete[] xs.Str;
		xs.Str = t;
		xs.LenText = len;
	}

	return xs;
}

bool Xstring::operator>(const Xstring &s)
{
	return strcmp(Str, s.Str) > 0;
}
bool operator>(const char *s, const Xstring &xs)
{
	return strcmp(s, xs.Str) > 0;
}

bool Xstring::operator>=(const Xstring &s)
{
	return strcmp(Str, s.Str) >= 0;
}
bool operator>=(const char *s, const Xstring &xs)
{
	return strcmp(s, xs.Str) >= 0;
}

bool Xstring::operator<(const Xstring &s)
{
	return strcmp(Str, s.Str) < 0;
}
bool operator<(const char *s, const Xstring &xs)
{
	return strcmp(s, xs.Str) < 0;
}

bool Xstring::operator<=(const Xstring &s)
{
	return strcmp(Str, s.Str) <= 0;
}
bool operator<=(const char *s, const Xstring &xs)
{
	return strcmp(s, xs.Str) <= 0;
}

bool Xstring::operator==(const Xstring &s)
{
	return strcmp(Str, s.Str) == 0;
}
bool Xstring::operator==(const char* s)
{
	return strcmp(Str, s) == 0;
}
bool operator==(const char *s, const Xstring &xs)
{
	return strcmp(s, xs.Str) == 0;
}

bool Xstring::operator!=(const Xstring &s)
{
	return strcmp(Str, s.Str) != 0;
}
bool operator!=(const char *s, const Xstring &xs)
{
	return strcmp(s, xs.Str) != 0;
}

const char* Xstring::c_str() const
{
	return Str;
}

Xstring::~Xstring()
{
	delete []Str;
}

_STD_END