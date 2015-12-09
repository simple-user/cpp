#pragma once
#include <exception>
#include <string>
#include <Windows.h>
#include <iostream>
#include <array>
#include <vector>
#include <fstream>

using std::string;
using std::exception;
using std::cout;
using std::array;
using std::vector;

bool operator==(COORD a, COORD b);


class Pole
{
public:
	Pole(size_t x, size_t y, size_t w, size_t h);

	size_t xPos;
	size_t yPos;
	size_t width;
	size_t height;
	size_t xMin;
	size_t xMax;
	size_t yMin;
	size_t yMax;
	HANDLE hand; // лінь з ним возитись!
	struct point
	{
		bool zan;
		WORD color;
		char ch;
	};

	void drawPole() const;
	bool chekCoord(size_t x, size_t y) const;  // зяйнято - 1, пусто - 0
	void setCoord(size_t x, size_t y, bool b, WORD color, char ch);  // 1 - зайняті всі, 0 - є ще вільні
	// void setTwoCoords( /* size_t x, size_t y, bool b*/);  // для змійки. 1 -включити, один виключити
	bool isFree() const;                        // 1 - є ще вільні, 0 - зайняті всі 
	size_t getCountFree() const	{ return leftFree;}
	void clearPole() 
	{
		delvecPole();
		leftFree = width * height;
	}

	void delvecPole()
	{
		vecPole.clear();
	}

	void rewritePole() const
	{
		COORD co;
		for (size_t a = 0; a < width; ++a)
		{
			for (size_t b = 0; b < height; ++b)
			{
					co = { a + xMin, b + yMin };
					SetConsoleCursorPosition(hand, co);
					SetConsoleTextAttribute(hand, vecPole[a][b].color);
					cout << vecPole[a][b].ch;
			}
		}
	}

	void setPoint(size_t x, const point& p)
	{
		if (vecPole.size() < x + 1)
		{
			vecPole.resize(vecPole.size() + 1);
		}
		//if (vecPole.size()  < x+1)
		//	throw exception("Фігня при загрузці vecPole[x].push_back(p)");
		vecPole[x].push_back(p);
	}

	const point & getPoint(size_t x, size_t y)
	{
		return vecPole[x][y];
	}

	void init()
	{
		vecPole.resize(width);
		for (auto &a : vecPole)
		{
			a.resize(height);
			for (auto &b : a)
			{
				b.ch = ' ';
				b.zan = false;
				b.color = 0;
			}

		}
	}
	
	void writeToFile(std::ofstream & ff)
	{
		ff.write((char*)&xPos,sizeof(xPos));
		ff.write((char*)&yPos, sizeof(yPos));
		ff.write((char*)&width, sizeof(width));
		ff.write((char*)&height, sizeof(height));
		ff.write((char*)&xMin, sizeof(xMin));
		ff.write((char*)&xMax, sizeof(xMax));
		ff.write((char*)&yMin, sizeof(yMin));
		ff.write((char*)&yMax, sizeof(yMax));
		ff.write((char*)&coord, sizeof(coord));
		ff.write((char*)&leftFree, sizeof(leftFree));
	}

	void writeToFile(std::fstream & ff)
	{
		ff.write((char*)&xPos, sizeof(xPos));
		ff.write((char*)&yPos, sizeof(yPos));
		ff.write((char*)&width, sizeof(width));
		ff.write((char*)&height, sizeof(height));
		ff.write((char*)&xMin, sizeof(xMin));
		ff.write((char*)&xMax, sizeof(xMax));
		ff.write((char*)&yMin, sizeof(yMin));
		ff.write((char*)&yMax, sizeof(yMax));
		ff.write((char*)&coord, sizeof(coord));
		ff.write((char*)&leftFree, sizeof(leftFree));
	}

	void readFromFile(std::ifstream & f)
	{
		f.read((char*)&xPos, sizeof(xPos));
		f.read((char*)&yPos, sizeof(yPos));
		f.read((char*)&width, sizeof(width));
		f.read((char*)&height, sizeof(height));
		f.read((char*)&xMin, sizeof(xMin));
		f.read((char*)&xMax, sizeof(xMax));
		f.read((char*)&yMin, sizeof(yMin));
		f.read((char*)&yMax, sizeof(yMax));
		f.read((char*)&coord, sizeof(coord));
		f.read((char*)&leftFree, sizeof(leftFree));
	}

	size_t getSizeSkip() const{ return sizeof(xPos)+sizeof(yPos)+sizeof(width)+sizeof(height)+sizeof(xMin)+sizeof(xMax)+sizeof(yMin)+sizeof(yMax)+sizeof(coord)+sizeof(leftFree); }

private:
	static const size_t XMAX = 78;
	static const size_t YMAX = 23;
	static const char borderChar = '#';
	mutable COORD coord;
	size_t leftFree;
	vector<vector<point>> vecPole; // все поле - зайнята клітинка чи вільна. 
};



