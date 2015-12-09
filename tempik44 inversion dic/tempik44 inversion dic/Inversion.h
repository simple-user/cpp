#pragma once
#include <set>
#include <string>
#include <algorithm>
#include <fstream>

using std::set;
using std::string;


struct myComp : public std::binary_function<string, string, bool>
{
	bool operator()(const string &str1, const string str2)
	{
		return std::lexicographical_compare(str1.crbegin(), str1.crend(), str2.crbegin(), str2.crend());
	}

};

class Inversion
{
public:
	Inversion(string fName) : fileName(fName)
	{
		std::fstream f(fileName, std::ios::in | std::ios::out);
		if (!f.is_open())
			std::ofstream f(fileName, std::ios::out);
		else
		{
			char sline[80];
			string strLine;
			size_t pos = 0;
			f.seekg(0, std::ios::beg);
			f.seekp(0, std::ios::beg);
			while (!f.eof())
			{
				f.getline(sline, 79, '\n');
				sline[79] = '\0';
				strLine = sline;
				// posZnak1 = strLine.find_first_of(';');
				if ((pos = strLine.find_first_not_of("абвгдеєжзиіїйклмнопрстуфхцчшщьеюя", 0)) != string::npos)
					continue; // якщо якийсь баг - тупо ігноримо :)
				dic.insert(strLine);
			}
		}
		f.close();
	};

	~Inversion()
	{
		std::ofstream f(fileName, std::ios::out);
		f.seekp(0, std::ios::beg);
		for (const auto &a : dic)
		{
			// записуємо значення
			for (size_t b = 0; b < a.size(); ++b)
				f.put(a[b]);
			f.put('\n');
		}

	}


	set<string, myComp>::const_iterator cbegin()
	{
		return dic.cbegin();
	}

	set<string, myComp>::const_iterator cend()
	{
		return dic.cend();
	}
		
	set<string, myComp>::iterator begin()
	{
		return dic.begin();
	}

	set<string, myComp>::iterator end()
	{
		return dic.end();
	}

	void push(string s)
	{
		size_t pos = 0;
		std::transform(s.begin(), s.end(), s.begin(), tolower);
		if ((pos = s.find_first_not_of("абвгдеєжзиіїйклмнопрстуфхцчшщьеюя", 0)) != string::npos)
			throw std::logic_error(string("wrong symbol") + s[pos]);

		dic.insert(std::move(s));
	}

private:
	set<string, myComp> dic;
	string fileName;
};

