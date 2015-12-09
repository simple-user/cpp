#pragma once
#include<string>
#include<iostream>
class Xstring
{
public:
	Xstring();
	Xstring(const char* s);
	
	Xstring(const Xstring& s);
	Xstring(Xstring &&s);

	Xstring& operator=(const Xstring& s);
	Xstring& operator=(Xstring&& s);
	
	Xstring operator+(const Xstring &s) const;
	Xstring operator+(const char *s) const;
	friend Xstring operator+(const char* s, const Xstring& xs);

	Xstring operator*(const Xstring &s) const;
	Xstring operator*(const char *s) const;
	friend Xstring operator*(char* s, const Xstring& xs);
	
	Xstring operator/(const Xstring &s) const;
	Xstring operator/(const char *s) const;
	friend Xstring operator/(char* s, const Xstring& xs);

	Xstring& operator+=(const Xstring &s);
	Xstring& operator+=(const char *s);

	Xstring& operator*=(const Xstring &s);
	Xstring& operator*=(const char *s);

	Xstring& operator/=(const Xstring &s);
	Xstring& operator/=(const char *s);

	char operator[](const int index) const;
	Xstring operator()(const int start, const int len) const;

	bool operator>(const Xstring &s);
	bool operator>(const char* s);
	friend bool operator>(const char *s, const Xstring &xs);

	bool operator>=(const Xstring &s);
	bool operator>=(const char* s);
	friend bool operator>=(const char *s, const Xstring &xs);

	bool operator<(const Xstring &s);
	bool operator<(const char* s);
	friend bool operator<(const char *s, const Xstring &xs);

	bool operator<=(const Xstring &s);
	bool operator<=(const char* s);
	friend bool operator<=(const char *s, const Xstring &xs);

	bool operator==(const Xstring &s);
	bool operator==(const char* s);
	friend bool operator==(const char *s, const Xstring &xs);

	bool operator!=(const Xstring &s);
	bool operator!=(const char* s);
	friend bool operator!=(const char *s, const Xstring &xs);

	friend std::ostream& operator<<(std::ostream &os, const Xstring& xs);

	~Xstring();
private:
	Xstring& plus()
	inline void setStr(char *& dest, const char * const sorce, int lenSorce);
	char *Str;
	int LenText;
};

