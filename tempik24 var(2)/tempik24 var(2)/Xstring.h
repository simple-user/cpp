#pragma once
#include<string>
#include<iostream>
#define _STD_BEGIN	namespace std {
#define _STD_END		}

_STD_BEGIN
class Xstring
{
public:
	Xstring(); //+
	Xstring(const char* s); //+
	
	Xstring(const Xstring& s); //+
	Xstring(Xstring &&s); //+

	Xstring& operator=(Xstring s); //+
	
	Xstring operator+(const Xstring &s) const; //+
	friend Xstring operator+(const char* s, const Xstring& xs); //+
	
	Xstring operator*(const Xstring &s) const; //+
	friend Xstring operator*(char* s, const Xstring& xs); //+
	
	Xstring operator/(const Xstring &s) const; //+
	friend Xstring operator/(const char* s, const Xstring& xs); //+

	Xstring& operator+=(const Xstring &s); //+

	Xstring& operator*=(const Xstring &s); //+

	Xstring& operator/=(const Xstring &s); //+

	char operator[](const int index) const; //+
	Xstring operator()(const int start, const int len) const; //+

	bool operator>(const Xstring &s); //+
	friend bool operator>(const char *s, const Xstring &xs); //+

	bool operator>=(const Xstring &s); //+
	friend bool operator>=(const char *s, const Xstring &xs); //+

	bool operator<(const Xstring &s); //+
	friend bool operator<(const char *s, const Xstring &xs); //+

	bool operator<=(const Xstring &s); //+
	friend bool operator<=(const char *s, const Xstring &xs); //+

	bool operator==(const Xstring &s); //+
	bool operator==(const char* s); //+
	friend bool operator==(const char *s, const Xstring &xs); //+

	bool operator!=(const Xstring &s); //+
	friend bool operator!=(const char *s, const Xstring &xs); //+

	explicit operator int() const;
	explicit operator double() const;

	friend std::ostream& operator<<(std::ostream &os, const Xstring& xs); //+
	friend void swap(Xstring& s1, Xstring& s2);

	const char* c_str() const;

	~Xstring(); //+

private:
	inline void plus(Xstring& res, const char* str1, const int len1, const char* str2, const int len2) const;
	inline void mult(Xstring & xs, const char* str1, const int len1, const char* str2) const;
	inline void div(Xstring & xs, const char* str1, const int len1, const char* str2) const;
	inline void setStr(char *& dest, const char * const sorce, int lenSorce);
	char *Str;
	int LenText;
};

_STD_END
