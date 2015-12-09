#pragma once
#include <set>
#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <Windows.h>
#include "myString.h"
#include "vec.h"

using std::cout;
using std::endl;
using std::set;
using std::string;


struct myComp : public std::binary_function<my, my, bool>
{
	virtual bool operator()(const my &str1, const my &str2)
	{
		size_t countChars = str2.getCountCharsComp() ? str2.getCountCharsComp() : str1.getCountCharsComp();
	
		if (!countChars)
		{
			bool res = std::lexicographical_compare(str1.crbegin(), str1.crend(), str2.crbegin(), str2.crend());
			return res;
		}
		else
		{
			/*if (str1.size() < countChars || str2.size() < countChars)
				return false;*/
			
			bool res = 0;
			/*
			if (str2.getCountCharsComp() && str2.getCountCharsComp() > str2.size())
			{
				res = std::lexicographical_compare(str1.crbegin(), str1.crend(),
					str2.crbegin(), str2.crend());
			}
			else if (str1.getCountCharsComp() && str1.getCountCharsComp() > str1.size())
			{
				res = std::lexicographical_compare(str1.crbegin(), str1.crend(),
					str2.crbegin(), str2.crend());
			}
			*/

			if (countChars && (countChars > str2.size() || countChars > str1.size()))
				res = std::lexicographical_compare(str1.crbegin(), str1.crend(),
				str2.crbegin(), str2.crend());
			else
				res = std::lexicographical_compare(str1.crbegin(), str1.crbegin() + countChars,
					str2.crbegin(), str2.crbegin() + countChars);
			return res;
		}
		
	}

};


/*
if (str1.size() < str2.countCharsComp || str2.size() < str2.countCharsComp)
return false;

if (str1.compare(str1.size() - str2.countCharsComp, str2.countCharsComp, str2, str2.size() - str2.countCharsComp, str2.countCharsComp))
return false;
else
return true;

*/



struct myComp2 : public myComp
{
	virtual bool operator()(const my &str1, const my &str2) override
	{
		if (str1.size() < str2.getCountCharsComp())
			return false;
		return std::lexicographical_compare(str1.crbegin(), str1.crbegin()+str2.getCountCharsComp(), 
			           str2.crbegin(), str2.crbegin()+str2.getCountCharsComp());
	}

};

class Inversion
{
public:
	Inversion(string fName);

	void testik(size_t countLet, size_t countFinded);
	
	~Inversion();


	set<my, myComp>::const_iterator cbegin()
	{
		return dic.cbegin();
	}

	set<my, myComp>::const_iterator cend()
	{
		return dic.cend();
	}
		
	set<my, myComp>::iterator begin()
	{
		return dic.begin();
	}

	set<my, myComp>::iterator end()
	{
		return dic.end();
	}

	void push(string s);

	bool find(my m, vec<my> &arrVec);

private:
	set<my, myComp> dic;
	string fileName;
	size_t countWords;
	const static HANDLE hand;
};

