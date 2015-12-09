#pragma once
#include <string>
#include <Windows.h>
#include <fstream>
#include <iostream>
#include <exception>
#include <conio.h>

using std::string;
enum Buttons { UP = 72, DOWN = 80, LEFT = 75, RIGHT = 77, 
	           ESC = 27, SPACE = 32, ENTER = 13, SKIP = 224,
               OPEN =15, SAVE=19, EXIT=24};

inline void gotoxy(int x, int y, WORD color);
inline void gotoxy(int x, int y, int count, WORD color);
inline void resetColor();

class MyFrame
{
public:
	MyFrame(int h = 20);
	void keyPress(); //+


private:
	static const int w = 75;
	static const char ZN = 1;
	static const char SP = ' ';
	int height;
	int width;
	int xPos;
	int yPos;
	int xMin;
	int yMin;
	int xMax;
	int yMax;
	int yService;
	string text;
	string fileName;
	size_t posInText;
	size_t posInTextStart;
	
	void openFile(); //+
	void saveToFile();
	void readToFrame(bool start = 0); //+
	bool exit() const; //+
	void moveUp(); //+
	void moveDown(); //+
	void moveLeft(); //
	void moveRight(); //
	void moveEnter();
	void addSpaces(); //
	void incXPos(); //
	void clear(bool New = 1);//
	void clearLine(int y); //
	void clearLineFromPos(int x, int y); //
	int findPosEBack() const;//

};

