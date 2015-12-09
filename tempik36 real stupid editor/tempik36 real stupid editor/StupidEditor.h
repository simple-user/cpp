#pragma once
#include <exception>
#include <string>
#include <conio.h>
#include <vector>
#include <fstream>
#include "Menu.h"

class StupidEditor
{
public:
	StupidEditor();
	void runMenu();
private:
	static const int indexTextStartLine = 7;
	static const int indexTextLastLine = 23;
	Menu menu;
	vector<string> P;
	string fileName;
	bool fileIsOnDisk;
	bool changedFile;

	inline void changesCheckForSave();

	void menuCreator();
	void menuResultCatch(int resultMenu);

	void createNewFile();
	void openFile();
	void saveFile(bool as=0);
	
	void clearText();
	void showText();
	inline void ramkaForShowText(size_t posX);


	void editP();
	void addP();
	void deleteP();
	void changeP();

	void find();
	void change();
};

