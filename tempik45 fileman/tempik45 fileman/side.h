#pragma once
#include <Windows.h>
#include <io.h>
#include <string>
#include "vec.h"
#include <iomanip>
#include <ctime>
#include <iostream>

using std::string;
using std::cout;
using std::endl;

class side
{
public:
	side(string p, size_t x, size_t y) : indexFile(0), upIndexFile(0), path(std::move(p)), posX(x), posY(y), countFiles(20)
	{
		if (!fillFiles())
			throw string("Can't read the directory: " + path);
	}


	static HANDLE hand;

// private:
	bool fillFiles()
	{
		files.clear();
		_finddata_t finfo;
		intptr_t done = _findfirst((path + "\\*.*").c_str(), &finfo);
		if (done == -1)
			return false;
		files.push_back(finfo);

		while (_findnext(done, &finfo) != -1)
			files.push_back(finfo);

		_findclose(done);

		return true;
	}

	void show()
	{
		if (!files.size())
			throw string("Nothing to show in func show()");

		string bufLine;
		for (size_t a = 0; a < countFiles; ++a)
		{
			SetConsoleCursorPosition(hand, { posX, posY + a });
			if (a < files.size())
			{
				SetConsoleTextAttribute(hand, a == indexFile ? 7 | 2 << 4 : 7);
				makeLine(files[a], bufLine);
				cout << bufLine;
			}
			else
			{
				SetConsoleTextAttribute(hand, 7);
				//printf_s("%c%s%c$s%c%s%c%s%c", 179, "                ", 16, 179, "       ", 7, 179, "        ", 8, 179, "    ", 4, 179);
				printf_s("%c                   %c       %c          %c", 179, 179, 179, 179);
			}
		}

	}
	

	void makeLine(_finddata_t &finfo, string &str)
	{
		str.clear();
		str += char(179);
		
		/*name*/
		if (strlen(finfo.name) > 19)
			str += string(finfo.name, 19);
		else
			str += finfo.name + string(19 - strlen(finfo.name), ' ');
		str += char(179);
		
		/*size*/
		
		string size;
		if (finfo.size > 1024 * 1024 * 1024)  // > 1 gb
			size = std::to_string(finfo.size / (1024 * 1024 * 1024)) + ',' + std::to_string(finfo.size % (1024 * 1024 * 1024) * 100 / (1024 * 1024 * 1024)) + 'G';
		else if (finfo.size > 1024 * 1024)  // > 1 mb < 1 gb
			size = std::to_string(finfo.size / (1024 * 1024)) + ',' + std::to_string(finfo.size % (1024 * 1024) * 100 / (1024 * 1024)) + 'M';
		else if (finfo.size > 1024)  // > 1 kb < 1 mb
			size = std::to_string(finfo.size / 1024) + ',' + std::to_string(finfo.size % 1024 * 100 / 1024) + 'K';
		else // < 1 kb
			size = std::to_string(finfo.size) + 'B';

		if (size.size() > 7)
			throw string("lenght of str:size > 7 : ") + size;

		if (size.size() < 7)
			size.insert(0, 7 - size.size(), ' ');

		str += size + char(179);

		/*date*/
		tm t;
		localtime_s(&t, &finfo.time_write);
		if (t.tm_mday < 10)
			str += '0';
		str += std::to_string(t.tm_mday) + '.';
		if (t.tm_mon < 10)
			str += '0';
		str += std::to_string(t.tm_mon + 1) + '.' + std::to_string(t.tm_year + 1900); 
		str += char(179);


	}

	vec<_finddata_t> files;
	size_t indexFile;
	size_t upIndexFile;
	size_t posX;
	size_t posY;
	string path;

	const size_t countFiles;
};

