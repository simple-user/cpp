#include "fileMan.h"


fileMan::fileMan(string l, string r, size_t x, size_t y) 
: activeLeft(true), posX(x), posY(y), 
left(new side(l, x, y)), right(new side(r, x+40, y )), active(nullptr)
{
	active = left;
	left->show();
	right->show();
	right->inactive();
}

void fileMan::keyLisener()
{
	int key[2] = {0};
	do
	{
		key[0] = _getch();
		clearStatus();
		if (_kbhit())
			key[1] = _getch();
		switch (key[0])
		{
		case ENTER:
			active->enter();
			break;
		case TAB:
			active->inactive();
			active = activeLeft ? right : left;
			activeLeft = activeLeft ? false : true;
			active->active();
			break;
		case SKIP:
			switch (key[1])
			{
			case UP:
				active->mooveUp();
				break;
			case DOWN:
				active->mooveDown();
				break;
			}
			break;
		case FSCIP:
			switch (key[1])
			{
			case F5:
				copy();
				break;
			}
			break;
		}

	} while (key[0]!=ESC);
}

bool fileMan::copyFile(string pathSrc,	string pathDst, string fileName)
{
	SetConsoleCursorPosition(side::hand, { posX, posY + side::countFiles });
	for (size_t a = 80; a; --a) cout << ' ';
	SetConsoleCursorPosition(side::hand, { posX, posY + side::countFiles });
	cout << "Copying: " << fileName;

#ifdef DEBUG_FILEMAN_COPY_FILE
	string s1(pathSrc + fileName);
	string s2(pathDst + fileName);
#endif

	//bool res = CopyFileA((active->getPath() + active->getActiveFInfo().name).c_str(),
	//	(getInactive()->getPath() + active->getActiveFInfo().name).c_str(), 0);
	bool res = CopyFileA((pathSrc+fileName).c_str(), (pathDst+fileName).c_str(), 0);

	return res;
}

bool fileMan::copyDir(string pathSrc, string pathDst, string dirName)
{
	bool res = 0;
	SetConsoleCursorPosition(side::hand, { posX, posY + side::countFiles });
	for (size_t a = 80; a; --a) cout << ' ';
	SetConsoleCursorPosition(side::hand, { posX, posY + side::countFiles });
	cout << "Copying: " << dirName;

#ifdef DEBUG_FILEMAN_COPY_DIR
	string newdir(pathDst + dirName);
#endif
	_mkdir((pathDst + dirName).c_str());
	
	_finddata_t finfo;
	intptr_t done = _findfirst((pathSrc + dirName + '\\' + "*.*").c_str(), &finfo);
	if (done == -1)
		return false;

#ifdef DEBUG_FILEMAN_COPY_DIR
	bool isDir = finfo.attrib & _A_SUBDIR;
	string src(pathSrc + dirName + '\\');
	string dst(pathDst + dirName + '\\');
	string name(finfo.name);
#endif

	if (_stricmp(finfo.name, ".") && _stricmp(finfo.name, ".."))
	{
		if (finfo.attrib & _A_SUBDIR) // якщо папка - рекурсія
			copyDir(pathSrc + dirName + '\\', pathDst + dirName + '\\', finfo.name);
		else  // копіюємо файл
			copyFile(pathSrc + dirName + '\\', pathDst + dirName + '\\', finfo.name);
	}

	while (_findnext(done, &finfo) != -1) // те ж саме тільки в циклі
	{
#ifdef DEBUG_FILEMAN_COPY_DIR
		bool isDir = finfo.attrib & _A_SUBDIR;
		string src(pathSrc + dirName + '\\');
		string dst(pathDst + dirName + '\\');
		string name(finfo.name);
#endif

		if (_stricmp(finfo.name, ".") && _stricmp(finfo.name, ".."))
		{
			if (finfo.attrib & _A_SUBDIR) // якщо папка - рекурсія
				copyDir(pathSrc + dirName + '\\', pathDst + dirName + '\\', finfo.name);
			else  // копіюємо файл
				copyFile(pathSrc + dirName + '\\', pathDst + dirName + '\\', finfo.name);
		}
	}

	_findclose(done);
	return true;
}


bool fileMan::copy()
{
	SetConsoleCursorPosition(side::hand, { posX, posY + side::countFiles });
	SetConsoleTextAttribute(side::hand, 7);
	cout << "Do you want to copy: " << active->getActiveFInfo().name << "(enter/esc)";
	int key = 0;
	do
	{
		key = _getch();
	} while (key != ENTER && key != ESC);
	if (key == ESC)
		return false;
	
	bool res = 0;

#ifdef DEBUG_FILEMAN_COPY
	string src(active->getPath());	
	string dst(getInactive()->getPath());
	string name(active->getActiveFInfo().name);
	bool isDir = active->getActiveFInfo().attrib & _A_SUBDIR;
#endif

	if (active->getActiveFInfo().attrib & _A_SUBDIR) // якщо папка - рекурсія
		res = copyDir(active->getPath(), getInactive()->getPath(), active->getActiveFInfo().name);
	else  // копіюємо файл
		res = copyFile(active->getPath(), getInactive()->getPath(), active->getActiveFInfo().name);


	if (!res)
	{
		SetConsoleCursorPosition(side::hand, { posX, posY + side::countFiles });
		for (size_t a = 80; a; --a) cout << ' ';
		SetConsoleCursorPosition(side::hand, { posX, posY + side::countFiles });
		cout << "Copy fail!";
		return false;
	}

	getInactive()->fillFiles();
	getInactive()->clearIndex();
	getInactive()->show();

	SetConsoleCursorPosition(side::hand, { posX, posY + side::countFiles });
	for (size_t a = 80; a; --a) cout << ' ';
	SetConsoleCursorPosition(side::hand, { posX, posY + side::countFiles });
	cout << "Copy complete.";
	return true;
}

fileMan::~fileMan()
{
	delete left;
	delete right;
}
