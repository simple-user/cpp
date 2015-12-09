#include "StupidEditor.h"


StupidEditor::StupidEditor() : fileIsOnDisk(0), changedFile(0)
{
	menuCreator();
}

void StupidEditor::menuCreator()
{
	menu.addPunkt(0, "1. Робота з файлами  >>>");
	menu.addPunkt(0, "2. Робота з текстом  >>>");
	menu.addPunkt(0, "3. Робота з абзацами >>>");
	menu.addPunkt(0, "4. Пошук             >>>");

	menu.addMenu(1);
	menu.addPunkt(1, "1. Створити новий файл");
	menu.addPunkt(1, "2. Відкрити існуючий файл");
	menu.addPunkt(1, "3. Зберегти файл");
	menu.addPunkt(1, "4. Зберегти файл як..");

	menu.addMenu(2);
	menu.addPunkt(2, "1. Очистити текст");
	menu.addPunkt(2, "2. Показати текст");

	menu.addMenu(3);
	menu.addPunkt(3, "1. Редагувати абзац");
	menu.addPunkt(3, "2. Додати абзац");
	menu.addPunkt(3, "3. Видалити абзац");
	menu.addPunkt(3, "4. Переставити абзаци");

	menu.addMenu(4);
	menu.addPunkt(4, "1. Знайти");
	menu.addPunkt(4, "2. Замінити");
}
void StupidEditor::runMenu()
{
	int res = 0;
	do
	{
		menuResultCatch(res);  // буде один перший холостий проход
		system("cls");
		res = menu.runMenu();
	} while (res);
}
void StupidEditor::menuResultCatch(int resultMenu)
{
	try
	{
		switch (resultMenu)
		{
		case 11: createNewFile(); break;
		case 12: openFile(); break;
		case 13: saveFile(); break;
		case 14: saveFile(1); break;

		case 21: clearText(); break;
		
		case 22: showText(); break;

		case 31: editP(); break;
		
		case 32: addP(); break;
		case 33: deleteP(); break;
		case 34: changeP(); break;
		
		case 41: find(); break;
		case 42: change(); break;
		}
	}
	catch (std::exception &e)
	{
		cout << "We have a little truble: " << e.what() << endl;
		_getch();
	}
	catch (...)
	{
		cout << "Что-то пошло не так! Chome(c)" << endl;
		_getch();
	}
}

inline void StupidEditor::changesCheckForSave() 
{
	if (changedFile)
	{
		gotoxy(0, indexTextStartLine, 7);
		std::cout << "Do you want to save current file, before creating a new one? (y) ";
		char ch = _getch();
		gotoxy(0, indexTextStartLine, 80, 7); //затираємо після прийняття рішення
		if (std::strchr("yY", ch) != 0)
			saveFile();
	}
}

void StupidEditor::createNewFile()
{
	changesCheckForSave();

	gotoxy(0, indexTextStartLine, 7);
	std::cout << "Enter name of new file: "; std::cin >> fileName;
	fileIsOnDisk = 0; //файл не на диску
	changedFile = 1;  //при маніпуляціях з файлом потрібно запитати чи не зберегти зміни!
	P.clear();
	
}

void StupidEditor::openFile()
{
	clearText();

	gotoxy(0, indexTextStartLine, 7);
	std::cout << "Enter name of file to open: "; std::cin >> fileName;
	gotoxy(0, indexTextStartLine, 80, 7);



	std::ifstream fin(fileName);
	if (!fin.is_open())       // просто жесть яка крута оптимізація! :)
		throw std::exception((std::string("Error: File: ") + fileName + " is not opened! (in func openFile())").c_str());

	char ch = 0;
	bool endFlag=0;
	
	// заповнюємо масив векторів
	do
	{
		string sT;
		while (1)
		{
			ch = fin.get();
			if (fin.eof()) break; //якщо прочитано ознаку кінця файлу - виходимо без запису
			sT.push_back(ch);
			if (ch == '\n')	break; //якщо прочитано знак кінця абзацу - записуємо і тоді виходимо
		}
		if (sT.size())
			P.push_back(std::_Move(sT));  // супер-дюпер оптимізація :)
	} while (!fin.eof());

	fin.close();

	fileIsOnDisk = 1; //файл на диску
	changedFile = 0;  //при маніпуляціях з файлом не потрібно питати чи не зберегти зміни!
}

void StupidEditor::saveFile(bool as)
{
	if (as)
	{
		gotoxy(0, indexTextStartLine, 7);
		std::cout << "Enter new name of file: "; std::cin >> fileName;
	}

	std::ofstream fout(fileName);

	if (!fout.is_open())
		throw std::exception((std::string("Error: File: ") + fileName + " is not opened! (in func saveFile())").c_str());

	for (auto a : P) 
	{
		fout << a;
	}
	fout.close();

	fileIsOnDisk = 1; //файл на диску
	changedFile = 0;  //при маніпуляціях з файлом не потрібно питати чи не зберегти зміни!

}

void StupidEditor::clearText()
{
	changesCheckForSave();
	P.clear();

}

inline void StupidEditor::ramkaForShowText(size_t posX)
{
	gotoxy(0, indexTextStartLine - 1, 7);
	for (int a(0); a < 80; a++) cout << '-';
	gotoxy(0, indexTextLastLine - 2, 7);
	for (int a(0); a < 80; a++) cout << '-';
	
	for (int a(indexTextStartLine); a < indexTextLastLine-2; a++)
	{
		gotoxy(posX, a, 7);
		cout << '|';
	}

}
void StupidEditor::showText()
{
	if (P.empty())
	{
		gotoxy(0, indexTextStartLine, 7);
		cout << "There is no text!" << endl;
		system("pause");
		gotoxy(0, indexTextLastLine, 80, 7);
		gotoxy(0, indexTextLastLine+1, 80, 7);
		return;
	}

	size_t textSize = 0;
	int indexLine = indexTextStartLine;
	bool flagExit = 0;
	size_t numP = 1;
	size_t widthText = 70;
	ramkaForShowText(80 - widthText-1);
	for (vector<string>::const_iterator cit(P.cbegin()); cit != P.cend() && !flagExit; cit++)
	{
		for (size_t pos = 0; pos < cit->size(); pos += widthText)
		{
			if (indexLine == indexTextLastLine - 2)
			{
				gotoxy(0, indexTextLastLine, 7);
				cout << "Do you want to continue? (y)";
				char ch = _getch();
				gotoxy(0, indexTextLastLine, 80, 7); //затираємо після прийняття рішення
				if (std::strchr("yY", ch) != 0)
				{
					indexLine = indexTextStartLine;
					gotoxy(0, indexTextStartLine, 80, indexTextLastLine - indexTextStartLine, 7);
					ramkaForShowText(80 - widthText - 1);
				}
				else
				{
					flagExit = 1;
					break;
				}

			}

			if (pos==0)
			{
				gotoxy(0, indexLine, 7);
				cout << "P=[" << numP << "]";
			}


			gotoxy(80-widthText, indexLine, 7);
			cout << cit->substr(pos, widthText);
			indexLine++;

		}

		numP++;

	}
	gotoxy(0, indexTextLastLine, 7);
	cout << "That's all!";
	_getch();
	gotoxy(0, indexTextLastLine, 80, 7); //затираємо після прийняття рішення

}

void StupidEditor::editP()
{
	int index = 0;
	int ch = 0;
	gotoxy(0, indexTextStartLine, 7);
	cout << "Enter number of Paragraph (min=1, max=" << P.size() << "): ";
	cin >> index;
	index--;
	gotoxy(0, indexTextStartLine, 80, 7);

	if (index <0 || index > P.size() - 1)
		throw std::exception("Incorect Paragraph number!");

	P[index].clear();

	gotoxy(0, indexTextStartLine, 7);
	cout << "Input new text for paragraph " << index << " here:\n";

	while (cin.get() != '\n');
	while ((ch = cin.get()) != '\n')
	{
		P[index].push_back(ch);
	}

	P[index].push_back('\n');  // в кінець додаємо перевод рядка + треба для size()==0

	changedFile = 1;  //
}

void StupidEditor::addP()
{
	P.emplace_back();
	gotoxy(0, indexTextStartLine, 7);
	cout << "Input new text for added paragraph here:\n";
	char ch = 0;
	while ((ch = _getch()) != '\r')
	{
		cout << ch;
		P[P.size()-1].push_back(ch);
	}
	P[P.size() - 1].push_back('\n');  // в кінець додаємо перевод рядка + треба для size()==0

	changedFile = 1;  //

}

void StupidEditor::deleteP()
{
	int index = 0;
	gotoxy(0, indexTextStartLine, 7);
	cout << "Enter number of Paragraph you want to delete: (min=1, max=" << P.size() << "): ";
	cin >> index;
	index--;
	gotoxy(0, indexTextStartLine, 80, 7);

	if (index <0 || index > P.size() - 1)
		throw std::exception("Incorect Paragraph number!");

	P.erase(P.cbegin() + index);

	gotoxy(0, indexTextStartLine, 7);
	cout << "Done!";
	_getch();
	gotoxy(0, indexTextStartLine, 80, 7);

	changedFile = 1;  //

}

void StupidEditor::changeP()
{
	int index1 = 0;
	int index2 = 0;
	int indexPut = 0;
	gotoxy(0, indexTextStartLine, 7);
	cout << "Enter range of paragraphs to move: (min=1, max=" << P.size() << "):\n";

	cout << "First paragraph (of range): ";	
	cin >> index1;
	index1--;
	if (index1 <0 || index1 > P.size() - 1)
		throw std::exception("Incorect firts Paragraph number!");

	cout << "Last paragraph (of range): ";	
	cin >> index2;
	index2--;
	if (index2 <0 || index2 > P.size() - 1 || index2 < index1)
		throw std::exception("Incorect last Paragraph number!");

	cout << "Enter number of paragraph to insert range (before):"
		" (min=1, max=" << P.size() << ") but not in range: (" << index1+2 << "-" << index2+1 << "): ";
	cin >> indexPut;
	indexPut--;
	if (indexPut < 0 || indexPut > P.size() || indexPut > index1 && indexPut <= index2)
		throw std::exception("Incorect number of paragraph to insert range!");

	gotoxy(0, indexTextStartLine, 80, 4, 7);

	// відчайдушна спроба провалилась! :(
	// P.insert(P.cbegin() + indexPut, vector<string>(P.cbegin() + index1, P.cbegin() + index2 + 1));
	
	for (int a(index1); a <= index2; a++)
	{
		string s(std::move(P.at(a)));
		P.insert(P.cbegin() + indexPut, std::move(s));
		
		//P.insert(P.cbegin() + indexPut, std::move(P.at(a)));
		
		if (indexPut <= index1) // вставляємо наперед - іддекси з"жджають вниз (плюсуються)
		{
			a++;
			index2++;
			index1++;
		}
		indexPut++;
	}

	P.erase(P.cbegin() + index1, P.cbegin() + index2 + 1);

	changedFile = 1;  //
}

void StupidEditor::find()
{
	gotoxy(0, indexTextStartLine, 7);
	cout << "Enter text to find (99 symbols max): ";
	while (cin.get() != '\n');

	char buffer[100];
	cin.getline(buffer, 100, '\n');

	cout << "Your text was found in such paragraphs:\n";

	for (size_t a(0); a < P.size(); a++)
	{
		if (P[a].find(buffer) != string::npos)
			cout << "Paragraph " << a + 1 << " (in position: " << P[a].find(buffer) << ")\n";
	}
	cout << endl;

	_getch();
}

void StupidEditor::change()
{
	gotoxy(0, indexTextStartLine, 7);
	cout << "Enter text to find (99 symbols max): ";
	// while (cin.get() != '\n');
	char bufferFind[100];
	cin.getline(bufferFind, 100, '\n');
	size_t findLen = strlen(bufferFind);

	cout << "Enter text to replace (99 symbols max): ";
	// while (cin.get() != '\n');
	char bufferReplace[100];
	cin.getline(bufferReplace, 100, '\n');

	cout << "Your text was replaced in such paragraphs:\n";

	size_t findedPos = 0;
	for (size_t a(0); a < P.size(); a++)
	{
		if ((findedPos = P[a].find(bufferFind)) != string::npos)
		{
			cout << "Paragraph " << a + 1 << " (in position: " << findedPos << ")\n";
			P[a].erase(findedPos, findLen);
			P[a].insert(findedPos, bufferReplace);
		}
			
	}
	cout << endl;

	changedFile = 1;

	_getch();
}