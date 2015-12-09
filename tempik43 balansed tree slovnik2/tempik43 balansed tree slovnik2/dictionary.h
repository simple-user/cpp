#pragma once
#include <string>
#include <fstream>
#include "myMap.h"

using std::string;
using std::ofstream;
using std::ifstream;
using std::fstream;

class dictionary : protected myMap<string, string>
{
public:
	dictionary(string fName) : fileName(fName)
	{
		fstream f(fileName, std::ios::in | std::ios::out);
		if (!f.is_open())
			ofstream f(fileName, std::ios::out);
		else
		{
			char sline[80];
			string strLine;
			size_t posZnak1 = 0;
			size_t posZnak2 = 0;
			f.seekg(0, std::ios::beg);
			f.seekp(0, std::ios::beg);
			while (!f.eof())
			{
				f.getline(sline, 79, '\n');
				sline[79] = '\0';
				strLine = sline;
				posZnak1 = strLine.find_first_of('-');
				posZnak2 = strLine.find_first_of(';');
				if (posZnak1 == string::npos || posZnak2 == string::npos)
					continue; // якщо якийсь баг - тупо ігноримо :)
				push(string(strLine.cbegin(), strLine.cbegin() + posZnak1), string(strLine.cbegin() + posZnak1 + 1, strLine.cbegin() + posZnak2));
			}
		}
		f.close();
	}

	~dictionary()
	{
		ofstream f(fileName, std::ios::out);
		f.seekp(0, std::ios::beg);
		for (size_t a = 0; a < getSize(); ++a)
		{
			// записуємо перше значення
			for (size_t b = 0; b < (*this)[a].first.size(); ++b)
				f.put((*this)[a].first[b]);
			f.put('-');
			// записуємо друге значення
			for (size_t b = 0; b < (*this)[a].second.size(); ++b)
				f.put((*this)[a].second[b]);
			f.put(';');
			f.put('\n');
		}
	
		f.close();

	}

	void setFilename(const string &newFileName)
	{
		fileName = newFileName;
	}

	string & getFileName()
	{
		return fileName;
	}

	void addWord(const string &lng1, const string &lng2)
	{
		push(lng1, lng2);
	}
	void addWord(const char *lng1, const char *lng2)
	{
		push(lng1, lng2);
	}

	string * translate(const string &s)
	{
		pval tpval = findByKey(s);
		if (!tpval.first)
			return nullptr;
		else
			return tpval.second;
	}
	// void translate(const char*s);



private:
	string fileName;
};

