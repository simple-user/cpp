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
enum Key { LEFTk = 75, UPk = 72, RIGHTk = 77, DOWNk = 3 };

class Snake
{
public:
	Snake(size_t size, time_t speed, Pole &p, Nyamka &n);
	int step(); // 0  - ��� ��������, 1 - �����, 2 -  ��� ���� �������
	int move();

private:
	vector<COORD> snakeArr;
	size_t indexHead;
	Dir snakeDir;
	bool dirUp;
	time_t snakeSpeed;
	Pole &pole;
	Nyamka &nyamLink;
	static const char snakeZnak = '@';

	

	void replaceIndex(const COORD newCo)  // ��������� ������ ������ :)
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
		pole.setCoord(snakeArr[indexHead].X, snakeArr[indexHead].Y, false);
		snakeArr[indexHead] = newCo;
		showOne(newCo);
		pole.setCoord(newCo.X, newCo.Y, true);
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

