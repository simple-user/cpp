#pragma once
#include <string>

using std::string;

class my : public string
{
public:
	my() : string(), countCharsComp(0) {}
	my(const string &str) : string(str), countCharsComp(0) {}
	my(const char* str) : string(str), countCharsComp(0) {}

	bool friend operator==(const my &str1, const my &str2)
	{
		if (str1.size() < str2.countCharsComp || str2.size() < str2.countCharsComp)
			return false;

		if (str1.compare(str1.size() - str2.countCharsComp, str2.countCharsComp, str2, str2.size() - str2.countCharsComp, str2.countCharsComp))
			return false;
		else
			return true;

	}
	
	void setCountCharsComp(size_t c)
	{
		countCharsComp = c;
	}

	size_t getCountCharsComp() const
	{
		return countCharsComp;
	}

private:
	size_t countCharsComp; // dafault = 0
};



//class myString
//{
//public:
//	myString() : str(), countCharsComp(4) {}
//	myString(const string &str) : str(str), countCharsComp(4) {}
//	myString(const char* str) : str(str), countCharsComp(4) {}
//
//	bool friend operator==(const myString &str1, const myString &str2)
//	{
//		if (str1.str.compare(str1.str.size() - str2.countCharsComp, str2.countCharsComp, str2.str, str2.str.size() - str2.countCharsComp, str2.countCharsComp))
//			return false;
//		else
//			return true;
//	}
//
//	void setCountCharsComp(size_t c)
//	{
//		countCharsComp = c;
//	}
//
//private:
//	string str;
//	size_t countCharsComp; // dafault = 4
//};

