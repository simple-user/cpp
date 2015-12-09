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
	void SaveScore(); // � ���� �� � ����� �������
	int startNewGame() 
	{
		int res = 0;
		activeIndexMenu = 0;
		while (!res && runMenu(newGame)) // ���� ��� (����� ��� ����� � �������� ���� ����� ����������)
		{
			size_t t = 0;
			switch (activeIndexMenu)
			{
			case 0:
				makeGreen(t); // �������� �����������
				// ������ ���� �������� ������� �����
				nyamLink->setCountNyam(t);
				backFromGreen(); //��������� ��������, ������ ���� ��������

				break;
			case 1:
				makeGreen(t);
				// ������ ���� �������� ������� �����
				snakeLink->setSpeed(t);
				backFromGreen(); // ������ ��������
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

		std::fstream f(filename, std::ios::in | std::ios::out | std::ios::binary); // ��� ������� ����� ������� ������� ��� ��������� ����
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
		
		// ���������
		// [������� �����]
		// [������� ���� ����� �����][����� �����]
		// [Pole][������� �������� vector<vector<point>> vecPole x][������� �������� vector<vector<point>> vecPole y][���� � ���: vector<vector<point>> vecPole ]
		// [Nyamka][������� �������� vector<Nyam> vecNyam][���� � ��� vector<Nyam> vecNyam]
		// [Snake][������� �������� vector<COORD> snakeArr][���� � ��� vector<COORD> snakeArr]

		// ���� ����� � ������ �� ������� ��� ����
		if (loadGame.empty())
		{
			loadGame.push_back(vector<string> {"Name - ", "Date"});
			char str[80];
			f.seekg(sizeof(size_t), std::ios::beg); //���������� ����� �����
			for (size_t a = 1; a<countLoads ; ++a) // �� �� ��� ������ +1 ��� � ���� �� ����� �� ��������
			{
				f.read((char*)&t, sizeof(t)); // ������� ���� ��� �����
				strLen = t > 79 ? 79 : t;
				f.read(str, strLen); // ������� ��� �����
				str[strLen] = '\0';
				loadGame.push_back(vector<string> {str, "Date"});
				
				// ����� ������� �� ����������� size_t - ������� ������� �����
				// ���� �� �� ������� ��������
				// ���� ������� �������� �� ��� ��� ������ ���� (��� ������ ����� �����)
				if (a == countLoads - 1)
					break;


				// ���� ������� ��������� ��"� �� ���� �������:
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

		// ����� �������� � ����� ������� ������� ���������
		// � ���� �������� �� � ����
		loadGame.push_back(vector<string> {name, "Date"});

		// ����� �������� ������� ��������� � ����
		// ���������
		// [������� �����]
		// [������� ���� ����� �����][����� �����]
		// [Pole][������� �������� vector<vector<point>> vecPole x][������� �������� vector<vector<point>> vecPole y][���� � ���: vector<vector<point>> vecPole ]
		// [Nyamka][������� �������� vector<Nyam> vecNyam][���� � ��� vector<Nyam> vecNyam]
		// [Snake][������� �������� vector<COORD> snakeArr][���� � ��� vector<COORD> snakeArr]

		t = name.size();
		f.seekp(0, std::ios::end); // ������������ � �����, � ����� ������ ��� ���� ���
		f.write((char*)&t, sizeof(t)); //������� ������� ���
		f.write(name.c_str(), t); //�������� ���
		f.write((char*)poleLink, sizeof(Pole)); // �������� ��������� ����� ����
		xPole = poleLink->xMax + 1;
		yPole = poleLink->yMax + 1;
		f.write((char*)&xPole, sizeof(xPole)); // �������� ������� �������� �� �
		f.write((char*)&yPole, sizeof(yPole)); // �������� ������� �������� �� �
		Pole::point polePoint;
		for (xPole = 0; xPole <= poleLink->xMax; ++xPole)
		{
			for (yPole = 0; yPole <= poleLink->yMax; ++xPole)
			{
				polePoint = poleLink->getPoint(xPole, yPole);
				f.write((char*)&polePoint, sizeof(polePoint));
			}
		} // �������� heap vecPole
		
		f.write((char*)nyamLink, sizeof(Nyamka)); // ��������� ����� Nyamka
		t = nyamLink->getCountNyam();
		f.write((char*)&t, sizeof(t)); // ������� �����
		Nyamka::Nyam nya;
		for (size_t a = 0; a < t; ++a)
		{
			nya = nyamLink->getNyam(a);
			f.write((char*)&nya, sizeof(nya));
		} // heap �����

		f.write((char*)snakeLink, sizeof(Snake)); // ��������� Snake
		t = snakeLink->getCountSnakeElements();
		f.write((char*)&t, sizeof(t)); // ������� �������� snake
		COORD co;
		for (size_t a = 0; a < t; ++a)
		{
			co = snakeLink->getCoordSnakeElem(a);
			f.write((char*)&co, sizeof(co));
		}// heap snake

		f.close();
	}

	void loadGameToVector()
	{
		loadGame.clear(); // ����� �����������
		// ������ ���������
		loadGame.push_back(vector<string> {"Name - ", "Date"});

		// ������� ����. ���� ��� ���� � - �������
		std::ifstream f(filename, std::ios::in | std::ios::binary);
		
		if (!f.is_open()) // ���� ����� �� ����, �� �������� � �������� �����
		{
			std::ofstream f(filename, std::ios::out | std::ios::binary);
			size_t t = 0;
			f.write((char*)&t, sizeof(t));
		}
		else
		{
			// ���������
			// [������� �����]
			// [������� ���� ����� �����][����� �����][Pole][Nyamka][Snake]
			size_t countSave = 0;
			f.seekg(0, std::ios::beg);
			f.read((char*)&countSave, sizeof(countSave)); // ������� ������� �����
			// ����� ������ � ������� ����� ��� (+ ���������� ������� ����� ����)
			size_t t = 0;
			char str[80];
			for (size_t a = 0; a<countSave; ++a)
			{
				f.read((char*)&t, sizeof(t));
				t = t > 79 ? 79 : t;
				f.read((char*)str, t);
				str[t] = '\0';
				loadGame.push_back(vector<string> {str, "Date"});
				if (a == countSave - 1)
					break;
				f.seekg(sizeof(Pole)+sizeof(Nyamka)+sizeof(Snake), std::ios::cur);
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

	void makeGreen(size_t &t); // ������� �������
	void backFromGreen(); // ������ ��������

	void readScore();

	bool runMenu(vector<vector<string>>&arr, bool clear=true, size_t width = 0);
	void writeMenu(vector<vector<string>> &arr, size_t indexStart, size_t indexEnd, size_t width = 0);


};

