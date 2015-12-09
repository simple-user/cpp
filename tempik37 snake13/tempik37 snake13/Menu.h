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
	Menu(Nyamka &n, Pole &p, Snake &s);
	bool runStartMenu();	// 0 - exit, 1 - start
	int runPauseMenu(); // -1 - continue
	void SaveScore(); // і його же ж треба вивести
	int startNewGame() 
	{
		int res = 0;
		activeIndexMenu = 0;
		while (!res && runMenu(newGame)) // поки тру (тобто при виході з нижнього рівня знову показувати)
		{
			size_t t = 0;
			switch (activeIndexMenu)
			{
			case 0:
				makeGreen(t); // виділяємо зелененьким
				// вводим нове значення кількості нямок
				nyamLink->setCountNyam(t);
				backFromGreen(); //прибираємо зеленень, лишаємо нове значення

				break;
			case 1:
				makeGreen(t);
				// вводим нове значення кількості нямок
				snakeLink->setSpeed(t);
				backFromGreen(); // знімаємо виділення
				break;
			case 2:
				res = 1; // start
				return res;
				break;
			}
		}
		return res;
	}

	void saveGame(const string & name)
	{
		size_t t = 0;
		size_t countLoads = 0;
		size_t strLen = 0;
		size_t xPole = 0;
		size_t yPole = 0;

		// якщо пусто в векторі то зчитуємо всю інфу
		if (loadGame.empty())
		{
			loadGameToVector();
		}
		
		std::fstream f(filename, std::ios::in | std::ios::out | std::ios::binary); // для початку треба зчитати кількість вже записаних ігор
		if (!f.is_open())
		{
			std::ofstream f(filename, std::ios::out | std::ios::binary);
			countLoads = 1;
			f.write((char*)&countLoads, sizeof(countLoads));
		}
		else
		{
			f.seekg(0, std::ios::beg);
			f.read((char*)&countLoads, sizeof(countLoads));
			++countLoads;
			f.seekp(0, std::ios::beg);
			f.write((char*)&countLoads, sizeof(countLoads));
		}
		
		// тепер допишемо в кінець вектора поточну зберігачку
		// а потім запишемо її у файл
		loadGame.push_back(vector<string> {name, "Date"});

		// тепер записуємо поточну зберігачку у файл
		// стурктура
		// [кількість сейвів]
		// [кількість букв назви сейву][назва сейву]
		// [Pole][кількість елементів vector<vector<point>> vecPole x][кількість елементів vector<vector<point>> vecPole y][інфа з хіп: vector<vector<point>> vecPole ]
		// [Nyamka][кількість улументів vector<Nyam> vecNyam][інфа з хіп vector<Nyam> vecNyam]
		// [Snake][кількість елементів vector<COORD> snakeArr][інфа з хіп vector<COORD> snakeArr]

		t = name.size();
		f.seekp(0, std::ios::end); // перемістились в кінець, і будем писати вже саму гру
		f.write((char*)&t, sizeof(t)); //ількість символів імя
		f.write(name.c_str(), t); //записали імя
		
		// перед тим як записати екземпляр класу поле треба забекапити і почитити вектор
		vector<vector<Pole::point>> vecPoleT;
		for (xPole = 0; xPole < poleLink->width; ++xPole)
		{
			vecPoleT.push_back(vector<Pole::point>());
			for (yPole = 0; yPole < poleLink->height; ++yPole)
			{
				vecPoleT[xPole].push_back(poleLink->getPoint(xPole, yPole));
			}
		} // записали heap vecPole
		poleLink->delvecPole(); // нам треба записати у файл пустий вектор (у нас інфа по ньому лежить)
		
		f.write((char*)poleLink, sizeof(Pole)); // записали екземпляр класу поле
		xPole = poleLink->width;
		yPole = poleLink->height;
		f.write((char*)&xPole, sizeof(xPole)); // записали кількість елементів по х
		f.write((char*)&yPole, sizeof(yPole)); // записали кількість елементів по у
		for (xPole = 0; xPole < poleLink->width; ++xPole)
		{
			for (yPole = 0; yPole < poleLink->height; ++yPole)
			{
				f.write((char*)&vecPoleT[xPole][yPole], sizeof(Pole::point));
			}
		} // записали heap vecPole
		
		// перед тим як записати екземпляр класу поле треба забекапити і почитити вектор
		vector<Nyamka::Nyam> vecNyamT;
		t = nyamLink->getCountNyam();
		for (size_t a = 0; a < t; ++a)
		{
			vecNyamT.push_back(nyamLink->getNyam(a));
		} // heap нямок
		nyamLink->clear();

		f.write((char*)nyamLink, sizeof(Nyamka)); // екземпляр класу Nyamka
		f.write((char*)&t, sizeof(t)); // кількість нямок
		for (size_t a = 0; a < t; ++a)
		{
			f.write((char*)&vecNyamT[a], sizeof(Nyamka::Nyam));
		} // heap нямок

		// перед тим як записати екземпляр класу поле треба забекапити і почитити вектор
		vector<COORD> vecSnakeT;
		t = snakeLink->getCountSnakeElements();
		for (size_t a = 0; a < t; ++a)
		{
			vecSnakeT.push_back(snakeLink->getCoordSnakeElem(a));
		}// heap snake
		snakeLink->clear();

		f.write((char*)snakeLink, sizeof(Snake)); // екземпляр Snake
		f.write((char*)&t, sizeof(t)); // кількість елементів snake
		for (size_t a = 0; a < t; ++a)
		{
			f.write((char*)&vecSnakeT[a], sizeof(COORD));
		}// heap snake

		f.close();
	}

	void loadGameToVector()
	{
		loadGame.clear(); // радше страховочка
		// пишемо заголовок
		loadGame.push_back(vector<string> {"Name - ", "Date"});

		// дивимос файл. якщо там щось є - зчитуємо
		std::ifstream f(filename, std::ios::in | std::ios::binary);
		
		if (!f.is_open()) // якщо файла не існує, то створимо і запишемо нулик
		{
			std::ofstream f(filename, std::ios::out | std::ios::binary);
			size_t t = 0;
			f.write((char*)&t, sizeof(t));
		}
		else
		{
			// стурктура
			// [кількість сейвів]
			// [кількість букв назви сейву][назва сейву]
			// [Pole][кількість елементів vector<vector<point>> vecPole x][кількість елементів vector<vector<point>> vecPole y][інфа з хіп: vector<vector<point>> vecPole ]
			// [Nyamka][кількість улументів vector<Nyam> vecNyam][інфа з хіп vector<Nyam> vecNyam]
			// [Snake][кількість елементів vector<COORD> snakeArr][інфа з хіп vector<COORD> snakeArr]
			
			size_t t = 0;
			size_t countLoads = 0;
			size_t strLen = 0;
			size_t xPole = 0;
			size_t yPole = 0;
			
			f.seekg(0, std::ios::beg);
			f.read((char*)&countLoads, sizeof(countLoads)); // зчитали кількість сейвів
			
			char str[80];
			f.seekg(sizeof(size_t), std::ios::beg); //пропускаємо перше число
			for (size_t a = 0; a<countLoads; ++a) 
			{
				f.read((char*)&t, sizeof(t)); // кількість букві імя сейва
				strLen = t > 79 ? 79 : t;
				f.read(str, strLen); // зчитали імя сейва
				str[strLen] = '\0';
				loadGame.push_back(vector<string> {str, "Date"});

				// треба перейти до наступоного size_t - кількості символів сейва
				// якщо це не остання прочитка
				// якщо остання прочитка то далі йти смислу немає (нам потрібні тільки імена)
				if (a == countLoads - 1)
					break;


				// якщо довжину зчитуємого ім"я ми таки обрізали:
				if (strLen < t)
					f.seekg(t - strLen, std::ios::cur);

				//pole
				f.seekg(sizeof(Pole), std::ios::cur);
				f.read((char*)&xPole, sizeof(xPole));
				f.read((char*)&yPole, sizeof(yPole));
				f.seekg(xPole*yPole*sizeof(Pole::point), std::ios::cur); //heap
				//end pole

				//nyamka
				f.seekg(sizeof(Nyamka), std::ios::cur);
				f.read((char*)&t, sizeof(t));
				f.seekg(t*sizeof(Nyamka::Nyam), std::ios::cur); //heap
				//end nyamka

				//snake
				f.seekg(sizeof(Snake), std::ios::cur);
				f.read((char*)&t, sizeof(t));
				f.seekg(t*sizeof(COORD), std::ios::cur);
				//end snake
			}

		}
		f.close();
	}

	void inputStr(const string &invite, string &strRes)
	{
		COORD co = { xStart, yStart };
		SetConsoleCursorPosition(poleLink->hand, co);
		SetConsoleTextAttribute(poleLink->hand, activeMenuColor);
		cout << invite;
		SetConsoleTextAttribute(poleLink->hand, activeMenuColorEdit);
		for (size_t a = 0; a < 15; ++a)
			cout << ' ';
		co.X = xStart + invite.size() + 1;
		SetConsoleCursorPosition(poleLink->hand, co);
		std::cin >> strRes;
		co.X = xStart;
		SetConsoleCursorPosition(poleLink->hand, co);
		SetConsoleTextAttribute(poleLink->hand, 0);
		for (size_t a = 0; a < 15 + invite.size() + 1; ++a)
			cout << ' ';
	}

	bool is_loadingGame() const { return loadingGame; };

	

private:
	vector<vector<string>> startMenu; // {{ "1. New Game" }, { "2. Load game" }, { "3. Exit" } };
	vector<vector<string>> pauseMenu; // {{ "1.Restart" }, { "2.New Game" }, { "3.Save Game" }, { "4.Main Menu" } };
	vector<vector<string>> newGame; // {{ "Count nyam: ", std::to_string(nyamLink.getCountNyam()) }, { "Speed", std::to_string(snakeLink.getSpeed()) }, { "3.Save Game" }, { "4.Exit" } };
	vector<vector<string>> loadGame;
	vector<vector<string>> tableScore;

	bool ghangedScore;
	bool loadingGame;

	Nyamka *nyamLink;
	Pole *poleLink;
	Snake *snakeLink;
	
	string filename;
	string filenameL;
	size_t activeIndexMenu;

	size_t xStart;
	size_t yStart;

	const static size_t menuWidth = 20;
	const static WORD activeMenuColor = 7 | 9 << 4;
	const static WORD activeMenuColorEdit = 7 | 2 << 4;
	const static WORD inactiveMenuColor = 7 | 1 << 4;

	void makeGreen(size_t &t); // виділяєм зеленим
	void backFromGreen(); // знімаємо виділення

	void readScore();

	bool runMenu(vector<vector<string>>&arr, bool clear=true, size_t width = 0);
	void writeMenu(vector<vector<string>> &arr, size_t indexStart, size_t indexEnd, size_t width = 0);


};

