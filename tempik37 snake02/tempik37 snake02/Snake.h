#pragma once
#include <vector>
#include <Windows.h>
#include "Pole.h"

using std::vector;
enum Dir {LEFT, UP, RIGHT, DOWN};
enum Key { LEFTk = 75, UPk = 72, RIGHTk = 77, DOWNk = 3 };

class Snake
{
public:
	Snake(size_t size, time_t speed, Pole &p);
	void step();

private:
	vector<COORD> snakeArr;
	size_t indexHead;
	Dir snakeDir;
	bool dirUp;
	time_t snakeSpeed;
	Pole &pole;
	static const char snakeZnak = '@';

	void replaceIndex(COORD newCo)  // переміщаємо індекс голови :)
	{
		if (dirUp)
		{
			indexHead = (indexHead - 1 + snakeArr.size()) % snakeArr.size();
		}
		else
		{
			indexHead = (indexHead + 1) % snakeArr.size();
		}
		showOne(snakeArr[indexHead], false);
		snakeArr[indexHead] = newCo;
		showOne(newCo);

	}


	void showOne(COORD co, bool enable = true)
	{
		co.X += pole.xMin;
		co.Y += pole.yMin;
		SetConsoleCursorPosition(pole.hand, co);
		SetConsoleTextAttribute(pole.hand, 7);
		cout << (enable ? snakeZnak : ' ');
	}

};

