#pragma once
#include <iostream>
#include <string>
#include <array>
#include <Windows.h>
#include <conio.h>
#include "Nyamka.h"
#include "Pole.h"
#include "Snake.h"

using std::string;
using std::array;
enum Buttons { UPm = 72, DOWNm = 80, ESCm = 27, ENTERm = 13, SKIPm = 224 };

class Menu
{
public:
	Menu(Nyamka &n, Pole &p, Snake &s) : nyamLink(n), poleLink(p), snakeLink(s), filename("save.dat") {};

	void runStartMenu()	
	{ 
		while (runMenu(startMenu)) // поки тру (тобто при виході з нижнього рівня знову показувати)
		{
			switch (activeIndexMenu)
			{
			case 0:
				activeIndexMenu = 0;
				while (runMenu(newGame)) // поки тру (тобто при виході з нижнього рівня знову показувати)
				{
					switch (activeIndexMenu)
					{
					case 0:
						size_t t = 0;
						COORD co = { newGame[activeIndexMenu].size() + poleLink.xMin + 1, activeIndexMenu + poleLink.yMin };
						SetConsoleCursorPosition(poleLink.hand, co);
						std::cin >> t;
						nyamLink.setCountNyam(t);
						break;
					}
				}
				break;
			}
		}

	}
	void runPauseMenu()	{ runMenu(pauseMenu);}
	



private:
	array<string, 4> startMenu{ { "1. New Game", "2. Load game", "3. Exit" } };
	array<string, 4> newGame{ { "Count nyam: ", "Speed: ", "GO!" } };
	array<string, 4> pauseMenu{ { "1.Restart", "2.New Game", "3.Save Game", "4.Exit" } };
	
	Nyamka &nyamLink;
	Pole &poleLink;
	Snake &snakeLink;
	
	string filename;
	size_t activeIndexMenu;

	void writeMenu(array<string, 4> &arr, size_t indexStart, size_t indexEnd)
	{
		COORD co = { poleLink.xMin, poleLink.yMin };
		for (size_t a = indexStart; a <=indexEnd; ++a)
		{
			if (a == activeIndexMenu)
				SetConsoleTextAttribute(poleLink.hand, 7 | 9 << 4);
			else
				SetConsoleTextAttribute(poleLink.hand, 7 | 1 << 4);

			co.Y = poleLink.yMin + a;
			SetConsoleCursorPosition(poleLink.hand, co);
			for (size_t b = 0; b < 15; ++b)
			{
				if (b < arr[a].size())
					cout << arr[a][b];
				else
					cout << ' ';
			}
		}
	}

	bool runMenu(array<string, 4> &arr)
	{
		bool res = false;

		activeIndexMenu = 0;
		writeMenu(arr, 0, 3);
		

		int key[2] = {};
		do
		{
			key[0]=_getch();
			if (_kbhit()) key[1] = _getch();
			if (key[0] == ENTERm)
			{
				res = true;
			}
			else if (key[0] == SKIPm)
			{
				switch (key[1])
				{
				case DOWNm:
					if (activeIndexMenu < 3)
					{
						++activeIndexMenu;
						writeMenu(arr, activeIndexMenu - 1, activeIndexMenu);
					}
					break;
				case UPm:
					if (activeIndexMenu >0)
					{
						--activeIndexMenu;
						writeMenu(arr, activeIndexMenu , activeIndexMenu+1);
					}
					break;
				}
			}

		} while (key[0]!=ESCm && key[0]!=ENTERm);

		return res;
	}


};

