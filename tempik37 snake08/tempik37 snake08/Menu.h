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
	void runPauseMenu()	{ runMenu(pauseMenu);}
	void SaveScore(); // і його же ж треба вивести

private:
	vector<vector<string>> startMenu; // {{ "1. New Game" }, { "2. Load game" }, { "3. Exit" } };
	vector<vector<string>> pauseMenu; // {{ "1.Restart" }, { "2.New Game" }, { "3.Save Game" }, { "4.Exit" } };
	vector<vector<string>> newGame; // {{ "Count nyam: ", std::to_string(nyamLink.getCountNyam()) }, { "Speed", std::to_string(snakeLink.getSpeed()) }, { "3.Save Game" }, { "4.Exit" } };
	vector<vector<string>> loadGame;
	vector<vector<string>> tableScore;

	bool ghangedScore;

	Nyamka &nyamLink;
	Pole &poleLink;
	Snake &snakeLink;
	
	string filename;
	string filenameL;
	size_t activeIndexMenu;

	size_t xStart;
	size_t yStart;

	const size_t menuWidth = 20;
	
	void makeGreen(size_t &t); // виділяєм зеленим
	void backFromGreen(); // знімаємо виділення

	void readScore();

	bool runMenu(vector<vector<string>>&arr, size_t width = 0);
	void writeMenu(vector<vector<string>> &arr, size_t indexStart, size_t indexEnd, size_t width = 0);


};

