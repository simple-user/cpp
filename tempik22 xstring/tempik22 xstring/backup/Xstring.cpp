#include "Xstring.h"

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


Xstring& Xstring::operator=(const Xstring& s)
{
	LenText = s.LenText;
	setStr(Str,s.Str, s.LenText);
	return *this;
}

Xstring& Xstring::operator=(Xstring&& s)
{
	
	delete[] Str;

	LenText = s.LenText;
	Str=s.Str;
	s.Str=nullptr;
	return *this;
}

std::ostream& operator<<(std::ostream &os, const Xstring& xs)
{
	os << xs.Str;
	return os;
}


Xstring Xstring::operator+(const Xstring &s) const
{
	Xstring t;
	t.LenText=LenText+s.LenText;
	t.Str = new char[t.LenText+1];
	*t.Str=0;
	strcat_s(t.Str,t.LenText+1,Str);
	strcat_s(t.Str,t.LenText+1,s.Str);
	return t;

}
Xstring Xstring::operator+(const char *s) const
{
	Xstring t;
	t.LenText=strlen(s)+LenText;
	t.Str = new char[t.LenText+1];
	*t.Str=0;
	strcat_s(t.Str,t.LenText+1,Str);
	strcat_s(t.Str,t.LenText+1,s);
	return t;
}

Xstring operator+(const char* s, const Xstring& xs)
{
	Xstring t;
	t.LenText=strlen(s)+xs.LenText;
	t.Str = new char[t.LenText+1];
	*t.Str=0;
	strcat_s(t.Str,t.LenText+1,s);
	strcat_s(t.Str,t.LenText+1,xs.Str);
	return t;
}
//

Xstring Xstring::operator*(const Xstring &s) const
{
	int index=0;
	const char *c = Str;
	char *res = new char[LenText + 1];
	do
	{
		c=strpbrk(c,s.Str);
		if(c)
		{
			res[index]=*c;
			index++;
			c++;
		}
	} while (c);
	res[index]=0;

	Xstring t(res);

	delete[] res;

	return t;
}
Xstring Xstring::operator*(const char *s) const
{
	int index=0;
	const char *c = Str;
	char *res = new char[LenText + 1];
	do
	{
		c=strpbrk(c,s);
		if(c)
		{
			res[index]=*c;
			index++;
			c++;
		}
	} while (c);
	res[index]=0;

	Xstring t(res);

	delete[] res;

	return t;
}

Xstring operator*(char* s, const Xstring& xs)
{
	const char *c=nullptr;
	int index=0;
	int pos=0;
	char *res = new char[strlen(s)+1];
	do
	{
		c=strpbrk(s+pos,xs.Str);
		if(c)
		{
			res[index]=*c;
			index++;
			pos=(c-s)+1;
		}
	} while (c);
	res[index]=0;

	Xstring t(res);

	delete[] res;

	return t;
}

Xstring::~Xstring()
{

	delete []Str;
}