#pragma once
#include <vector>
#include <Windows.h>
#include <conio.h>
#include <map>
#include "Pole.h"
#include "Nyamka.h"

using std::vector;
using std::map;
enum Dir {LEFT, UP, RIGHT, DOWN};
enum Key { LEFTk = 75, UPk = 72, RIGHTk = 77, DOWNk = 80 };

class Snake
{
public:
	Snake(size_t size, Pole &p, Nyamka &n);
	int step(); // 0  - все звичайно, 1 - нямка, 2 -  сам себе клацнув
	int move();
	void setSpeed(time_t speed) { snakeSpeed = speed; }
	time_t getSpeed() const { return snakeSpeed; }
	void init();
	void clear() { snakeArr.clear(); }

private:
	vector<COORD> snakeArr;
	size_t indexHead;
	Dir snakeDir;
	bool dirUp;
	time_t snakeSpeed;
	Pole &pole;
	Nyamka &nyamLink;
	static const char snakeZnak = '@';
	WORD colorSnake;
	size_t startSize;

	void changeDir();

	void replaceIndex(const COORD newCo)  // переміщаємо індекс голови :)
	{
		if (dirUp)
		{
			indexHead = (indexHead - 1 + snakeArr.size()) % snakeArr.size();
		}
		else
		{
			indexHead = (indexHead + 1) % snakeArr.size();
		}
		showOne(snakeArr[indexHead], 7, false);
		pole.setCoord(snakeArr[indexHead].X, snakeArr[indexHead].Y, false);
		snakeArr[indexHead] = newCo;
		showOne(newCo, colorSnake);
		pole.setCoord(newCo.X, newCo.Y, true);
	}


	void showOne(COORD co, WORD color = 7, bool enable = true)
	{
		co.X += pole.xMin;
		co.Y += pole.yMin;
		SetConsoleCursorPosition(pole.hand, co);
		SetConsoleTextAttribute(pole.hand, color);
		cout << (enable ? snakeZnak : ' ');
	}

};

