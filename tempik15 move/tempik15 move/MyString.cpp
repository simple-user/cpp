#include "MyString.h"


//explicit MyString();
MyString::MyString() : str(nullptr), size(0) 
{
	std::cout << "### MyString::MyString()" << std::endl;
}

//MyString(const char *s);
MyString::MyString(const char* s) : size(strlen(s))
{
	std::cout << "### MyString::MyString(const char* s), s: " << s << std::endl;
	str = new char[size + 1];
	strcpy_s(str, size + 1, s);
}

//MyString(const MyString &s);
MyString::MyString(const MyString& s) : size(s.size)
{
	std::cout << "### MyString::MyString(const MyString& s), s: " << s.str << std::endl;
	str = new char[size + 1];
	strcpy_s(str, size + 1, s.str);
}

//MyString(MyString&& s);
MyString::MyString(MyString &&s) : size(s.size)
{
	std::cout << "### MyString::MyString(MyString &&s), s: " << s.str << std::endl;
	str = s.str;
	s.str = nullptr;
	s.size = 0;
}

//friend MyString operator+(const MyString &s1, const MyString &s2);
MyString operator+(const MyString &s1, const MyString &s2)
{
	std::cout << "### MyString operator+(const MyString &s1 (" << s1.str << "), const MyString &s2 (" << s2.str << "))" << std::endl;
	MyString t;
	t.size = s1.size + s2.size;
	t.str = new char[t.size + 1];
	strcpy_s(t.str, t.size + 1, s1.str);
	strcat_s(t.str, t.size + 1, s2.str);
	return t;
}

//MyString& operator=(const MyString& s);
MyString& MyString::operator=(const MyString& s)
{
	std::cout << "### MyString& MyString::operator=(const MyString& s (" << s.str << "))" << std::endl;
	if (str)
		delete[] str;
	size = s.size;
	str = new char[size + 1];
	strcpy_s(str, size + 1, s.str);
	return *this;
}

//MyString& operator=(MyString &&s);
MyString& MyString::operator=(MyString &&s)
{
	std::cout << "### MyString& MyString::operator=(MyString &&s (" << s.str << "))" << std::endl;
	size = s.size;
	str = s.str;
	s.str = nullptr;
	s.size = 0;
	return *this;
}

//friend std::ostream& operator<<(std::ostream& os, MyString& s);
std::ostream& operator<<(std::ostream& os, const MyString& s)
{
	std::cout << "### std::ostream& operator<<" << std::endl;
	if (s.str)
		os << s.str;
	return os;
}

//void giveMemoryBuffer(int aditionalMemory);
void MyString::giveMemoryBuffer(int add)
{
	std::cout << "### void MyString::giveMemoryBuffer(int add=" << add << " size=" << size << ")" << std::endl;
	char *t = str;
	size += add;
	str = new char[size + 1];
	strcpy_s(str, size + 1, t);
	delete[] t;
}

//friend std::istream& operator>>(std::istream& is, MyString& s);
std::istream& operator>>(std::istream& is, MyString& s)
{
	std::cout << "### std::istream& operator>>" << std::endl;
	if (s.str)
		delete[] s.str;
	
	char ch = 0;
	int index = 0;
	s.size = 10;
	s.str = new char[10 + 1];
	s.str[10] = '\0';
	while (!strchr(" \n", ch = is.get()))
	{
		if (index >= s.size)
			s.giveMemoryBuffer(10);
		s.str[index] = ch;
		index++;
	}

	s.str[index] = '\0';
	s.size = index; // лишніх пару байт не підчищаю
	
	return is;
}


MyString::~MyString()
{
	std::cout << "### MyString::~MyString() for: " << (str ? str : "null") << std::endl;
	if (str)
		delete[] str;
}
