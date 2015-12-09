#pragma once
#include <exception>
#include <string>
#include <Windows.h>
#include <iostream>
#include <array>
#include <vector>

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

	const size_t xPos;
	const size_t yPos;
	const size_t width;
	const size_t height;
	const size_t xMin;
	const size_t xMax;
	const size_t yMin;
	const size_t yMax;
	const HANDLE hand; // лінь з ним возитись!
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
		//а от фіг вам! :(( std::for_each(vecPole.begin(), vecPole.end(), [](vector<bool> &a){ std::for_each(a.begin(), a.end(), [](bool &b){b = false; }); });

		for (auto &a : vecPole)
			for (auto &b : a)
			{
				b.ch = ' ';
				b.zan = false;
				b.color = 0;
			}
			
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
		if (vecPole.size() - 1 < x)
			vecPole.push_back(vector<point>());

		if (vecPole.size() - 1 < x)
			throw exception("Фігня при загрузці vecPole[x].push_back(p)");
		vecPole[x].push_back(p);
	}

	const point & getPoint(size_t x, size_t y)
	{
		return vecPole[x][y];
	}
	
private:

	
	vector<vector<point>> vecPole; // все поле - зайнята клітинка чи вільна. 

	
	static const size_t XMAX = 78;
	static const size_t YMAX = 23;
	static const char borderChar = '#';
	
	mutable COORD coord;
	size_t leftFree;
};

