#pragma once
#include <iostream>
#include <string>
#include <array>
#include <Windows.h>
#include <conio.h>
#include <vector>
#include <fstream>
#include "Nyamka.h"
#include "Pole.h"
#include "Snake.h"

using std::string;
using std::array;
using std::vector;
enum Buttons { UPm = 72, DOWNm = 80, ESCm = 27, ENTERm = 13, SKIPm = 224 };

class Menu
{
public:
	Menu(Nyamka &n, Pole &p, Snake &s ) : nyamLink(n), poleLink(p), snakeLink(s), filename("save.dat"), filenameL("l.dat"), xStart(30), yStart(6)
	{
		 startMenu = { { "1. New Game" }, { "2. Load game" }, { "3. Exit" } };
		 pauseMenu = { { "1.Restart" }, { "2.New Game" }, { "3.Save Game" }, { "4.Exit" } };
		 newGame = { { "Count nyam: ", std::to_string(nyamLink.getCountNyam()) }, { "Speed: ", std::to_string(snakeLink.getSpeed()) },  { "GO!" } };

	};

	void makeGreen(size_t &t) // виділяєм зеленим
	{
		COORD co = { xStart + newGame[activeIndexMenu][0].size(), activeIndexMenu + yStart };
		SetConsoleCursorPosition(poleLink.hand, co);
		SetConsoleTextAttribute(poleLink.hand, 7 | 2 << 4);
		for (size_t b = newGame[activeIndexMenu][0].size(); b < menuWidth; ++b)
			cout << ' ';
		SetConsoleCursorPosition(poleLink.hand, co);
		std::cin >> t;
		newGame[activeIndexMenu][1] = std::to_string(t);

	}
	void backFromGreen() // знімаємо виділення
		
	{
		COORD co = { xStart + newGame[activeIndexMenu][0].size(), activeIndexMenu + yStart };
		SetConsoleCursorPosition(poleLink.hand, co);
		SetConsoleTextAttribute(poleLink.hand, 7 | 1 << 4);
		cout << newGame[activeIndexMenu][1];
		for (size_t b = newGame[activeIndexMenu][0].size() + newGame[activeIndexMenu][1].size(); b < menuWidth; ++b)
			cout << ' ';
	}


	void runLiderMenu()
	{
		runMenu(tableLider);
	}

	bool runStartMenu()	// 0 - exit, 1 - start
	{ 
		int res = 0; // -1 - exit, 1 - start, 0 - nothing
		while (!res && runMenu(startMenu)) // поки тру (ентер) (тобто при виході з нижнього рівня знову показувати)
		{
			switch (activeIndexMenu)
			{
			case 0:
				activeIndexMenu = 0;
				while (!res && runMenu(newGame)) // поки тру (тобто при виході з нижнього рівня знову показувати)
				{
					size_t t = 0;
					switch (activeIndexMenu)
					{
					case 0:
						makeGreen(t); // виділяємо зелененьким
						// вводим нове значення кількості нямок
						nyamLink.setCountNyam(t);
						backFromGreen(); //прибираємо зеленень, лишаємо нове значення
						
						break;
					case 1:
						makeGreen(t);
						// вводим нове значення кількості нямок
						snakeLink.setSpeed(t);
						backFromGreen(); // знімаємо виділення
						break;
					case 2:
						res = 1; // start
						break;
					}
				}
				break;
			case 1:
				// load game
				{
					loadGame.clear();
					loadGame.push_back(vector<string> {"Name - ", "Date"});
					std::ifstream in(filename, std::ios::in | std::ios::binary);
					if (!in)
						loadGame.push_back(vector<string> {"You have no saves!"});
					while (runMenu(loadGame) && !res)
					{

					}
				}
				break;
			case 2:
				res = -1; // exit
				// exit
				break;
			}
			SetConsoleTextAttribute(poleLink.hand, 7);
			
		}
		if (res == 1)
			return true;
		return false;
	}
	void runPauseMenu()	{ runMenu(pauseMenu);}
	



private:
	vector<vector<string>> startMenu; // {{ "1. New Game" }, { "2. Load game" }, { "3. Exit" } };
	vector<vector<string>> pauseMenu; // {{ "1.Restart" }, { "2.New Game" }, { "3.Save Game" }, { "4.Exit" } };
	vector<vector<string>> newGame; // {{ "Count nyam: ", std::to_string(nyamLink.getCountNyam()) }, { "Speed", std::to_string(snakeLink.getSpeed()) }, { "3.Save Game" }, { "4.Exit" } };
	vector<vector<string>> loadGame;
	vector<vector<string>> tableLider;


	Nyamka &nyamLink;
	Pole &poleLink;
	Snake &snakeLink;
	
	string filename;
	string filenameL;
	size_t activeIndexMenu;

	size_t xStart;
	size_t yStart;

	const size_t menuWidth = 20;

	void writeMenu(vector<vector<string>> &arr, size_t indexStart, size_t indexEnd)
	{
		COORD co = { xStart, yStart };
		size_t countLeters = 0;
		for (size_t a = indexStart; a <=indexEnd; ++a)
		{
			if (a == activeIndexMenu)
				SetConsoleTextAttribute(poleLink.hand, 7 | 9 << 4);
			else
				SetConsoleTextAttribute(poleLink.hand, 7 | 1 << 4);

			co.Y = yStart + a;
			SetConsoleCursorPosition(poleLink.hand, co);
			
			countLeters = 0;
			std::for_each(arr[a].begin(), arr[a].end(), [&countLeters](string &s) { countLeters += s.size(); cout << s; });
			for (size_t b = countLeters; b < menuWidth; ++b)
					cout << ' ';
		}
	}

	bool runMenu(vector<vector<string>>&arr)
	{
		SetConsoleTextAttribute(poleLink.hand, 7);
		system("cls");
		bool res = false;

		activeIndexMenu = 0;
		writeMenu(arr, 0, arr.size()-1);
		

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
					if (activeIndexMenu < arr.size()-1)
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

