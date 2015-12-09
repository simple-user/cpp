#ifndef _MYSTRING_
#define _MYSTRING_
#include <iostream>

class MyString
{
private:
	char *str;
	int size;
	void giveMemoryBuffer(int aditionalMemory);
public:
	MyString();
	explicit MyString(const char *s);
	MyString(const MyString &s);
	MyString(MyString&& s);

	friend MyString operator+(const MyString &s1, const MyString &s2);
	MyString& operator=(const MyString& s);
	MyString& operator=(MyString &&s);
	//MyString& operator=(const char *s)
	//{
	//	std::cout << "MyString& operator=(const char *s)" << std::endl;
	//	return *this;
	//}
	friend std::ostream& operator<<(std::ostream& os, const MyString& s);
	friend std::istream& operator>>(std::istream& is, MyString& s);

	int getSize();

	~MyString();
};

#endif
