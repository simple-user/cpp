#pragma once
#include <conio.h>
#include <direct.h>
#include "side.h"

#define DEBUG_FILEMAN_COPY
#define DEBUG_FILEMAN_COPY_FILE
#define DEBUG_FILEMAN_COPY_DIR

enum Buttons { UP = 72, DOWN = 80, ESC = 27, ENTER = 13, SKIP = 224, TAB = 9, FSCIP = 0, F5 = 63, F6=64 };
class fileMan
{
public:
	fileMan(string l, string r, size_t x, size_t y);
	~fileMan();

	void keyLisener();
private:
	side *left;
	side *right;
	side *active;
	bool activeLeft;
	bool copy();
	bool copyFile(string pathSrc,
		          string pathDst,
				  string fileName);
	bool copyDir(string pathSrc,
				string pathDst,
				string dirName);

	inline side* getInactive() const
	{
		if (activeLeft)
			return right;
		else
			return left;
	}

	inline void clearStatus() const
	{
		SetConsoleCursorPosition(side::hand, { posX, posY + side::countFiles });
		SetConsoleTextAttribute(side::hand, 7);
		for (size_t a = 80; a; --a) cout << ' ';
	}
	size_t posX;
	size_t posY;
};

