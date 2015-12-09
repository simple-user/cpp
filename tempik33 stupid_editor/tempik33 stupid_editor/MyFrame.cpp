#include "MyFrame.h"

HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);

inline void gotoxy(int x, int y, WORD color)
{
	COORD coord = { x, y };
	SetConsoleCursorPosition(hand, coord);
	SetConsoleTextAttribute(hand, color);
}
inline void gotoxy(int x, int y, int count, WORD color)
{
	gotoxy(x, y, color);
	for (int a(0); a < count; a++)
		std::cout << ' ';
}
inline void resetColor()
{
	SetConsoleTextAttribute(hand, 7);
}

MyFrame::MyFrame(int h)
: height(h), width(w), xMax(w - 1), yMax(h - 1), posInText(0), posInTextStart(0), yService(h + 1), xMin(1), yMin(1)
{
	xPos = xMin, yPos = yMin;
	
	if (h<10 || h>20)
		throw std::invalid_argument("Error: litle height of frame");

	clear();

	gotoxy(xMin, yService +2, 15 | 3 << 4);
	std::cout << "CTRL+O - open";
	gotoxy(xMin + 16, yService + 2, 15 | 3 << 4);
	std::cout << "CTRL+S - save";
	gotoxy(xMin + 32, yService + 2, 15 | 3 << 4);
	std::cout << "ESC - exit";
	gotoxy(xPos, yPos, 7);
}

void MyFrame::clear(bool New)
{
	for (int x(0); x <= width; x++)
		for (int y(0); y <= height; y++)
		{
			gotoxy(x, y, 4 | 4 << 4);
			if (x == 0 || x == width || y == 0 || y == height)
				gotoxy(x, y, 4 | 4 << 4) , std::cout << '#';
			else
				gotoxy(x, y, 4 | 7) , std::cout << ' ';
		}

		xPos = xMin;
	yPos = yMin;
	posInText = 0;
	posInTextStart = 0;
	
	
	gotoxy(3, 0, 7);
	if (New)
		std::cout << "new.txt";
	else
		std::cout << fileName;

	resetColor();
	gotoxy(xPos, yPos, 7);
}

void MyFrame::openFile()
{
	std::ifstream fin;
	gotoxy(0, yService, 7);
	std::cout << "Enter fileName: ";
	std::cin >> fileName;
	gotoxy(0, yService, 70, 7);
	fin.open(fileName, std::ifstream::in);
	
	if (!fin.is_open())
		throw std::runtime_error("Error: file is not open in func openFile");
	
	text.clear();
	clear(0);

	while (!fin.eof())
	{
		text.push_back(fin.get());
	}
	fin.close();

	text.at(text.size()-1)='\n';

	readToFrame();
}

void MyFrame::saveToFile()
{
	std::ofstream fout;
	
	if (fileName.empty())
	{
		gotoxy(0, yService, 7);
		std::cout << "Enter fileName: ";
		std::cin >> fileName;
		gotoxy(0, yService, 70, 7);
	}

	fout.open(fileName);

	if (!fout.is_open())
		throw std::runtime_error("Error: file is not open in func saveToFile");

	for (std::string::const_iterator ci(text.cbegin()); ci < text.cend(); ci++)
	{
		if (*ci == ZN)
			continue;

		fout << *ci;
	}

	fout.close();
	gotoxy(xPos, yPos, 7);
}

void MyFrame::readToFrame(bool start)
{
	int xT = xPos;
	int yT = yPos;
	size_t posT = posInText;

	if (start)
	{
		xT = xMin;
		yT = yMin;
		posT = posInTextStart;
	}
	
	while (posT < text.size())
	{
		gotoxy(xT, yT, 7);
		std::cout << text.at(posT);
	
		if (text.at(posT) == '\n')
		{
			gotoxy(xT, yT, 7);
			std::cout << ' ';

			if (posT == text.size() - 1) //останній ентер просто чистимо екран
			{
				clearLineFromPos(xT, yT);
				break;
			}

			posT++;
			xT++;
			while (text.at(posT) == ZN) // якщо ентер видаляємо всі пробіли після нього 
				text.erase(text.cbegin() + posT);
			
			while (xT <= xMax) // тепер доставляємо свої пробіли
			{
				text.insert(text.cbegin() + posT, ZN);
				gotoxy(xT, yT, 7);
				std::cout << ' ';
				xT++;
				posT++;
			}
			xT--;
			posT--;
		}
		
		if (xT == xMax && yT == yMax)
		{
			break;
		}
		else if (xT == xMax)
		{
			xT = xMin;
			yT++;
			posT++;
		}
		else
		{
			xT++;
			posT++;
		}
	}

	if (yT != yMax)
		clearLine(yT + 1);
	
	gotoxy(xPos, yPos, 7);
}

void MyFrame::clearLine(int y)
{
	for (int a(xMin); a <= xMax; a++)
	{
		gotoxy(a, y, 7);
		std::cout << ' ';
	}
}

void MyFrame::clearLineFromPos(int x, int y)
{
	for (int a(x); a <= xMax; a++)
	{
		gotoxy(a, y, 7);
		std::cout << ' ';
	}
}

void MyFrame::addSpaces()
{
	size_t t = posInText - text.size();
	for (size_t a(0); a<t; a++)
		text.push_back(SP);
}

void MyFrame::incXPos()
{
	if (xPos == xMax && yPos == yMax)
		return;
	else if (xPos == xMax)
	{
		xPos = xMin;
		yPos++;
	}
	else
		xPos++;
}

int MyFrame::findPosEBack() const
{
	size_t t = posInText-1;
	while (text.at(t) == ZN)
		t--;
	if (text.at(t) == '\n')
		return t;
	return -1;
}

void MyFrame::moveEnter()
{
	
}

void MyFrame::keyPress()
{
	char ch = 0;
	bool ex = 0;
	do
	{
		ch = _getch();

		if (ch >= 33 && ch <= 191 || ch==ENTER ) // letters
		{
			
			// спочатку вписуємо в позицію  поля
			gotoxy(xPos, yPos, 7);
			std::cout << (ch == ENTER ? ' ' : ch);

			if (posInText >= text.size()) // варіант, коли дописуємо в кінець string-a
			{
				if (posInText > text.size())
				{
					// якщо в кінець і ще після ентера
					if (text.at(text.size()-1)=='\n')
						text.at(text.size() - 1) = SP;
					addSpaces();
				}
				
				if (ch == ENTER)
				{
					text.push_back('\n');
				}
				else
					text.push_back(ch);
			}
			else
			{
				if (text.at(posInText) == ZN) //вставляємо в середину тексту пісял ентера
				{
					int posE = findPosEBack();
					if (posE != -1)
					{
						// text.at(posE) = ' ';  // якщо знайшовся ентер  від posE до posInText - пробіли
						for (size_t a(posE); a < posInText; a++)
							text.at(a) = SP;
						text.insert(text.cbegin() + posInText, '\n');
					}
				}

				if (ch == ENTER)
					text.insert(text.cbegin() + posInText, '\n');
				else
					text.insert(text.cbegin() + posInText, ch);

				readToFrame();

			}
			
			
			if (ch == ENTER)
			{
				moveDown();
				while (xPos != xMin)
					moveLeft();
			}
			else
			{
				incXPos();
				posInText++;
			}
		}
		else if (ch == -32) //moves
		{
			ch = _getch();
			switch (ch)
			{
			case UP: moveUp(); break;
			case DOWN: moveDown(); break;
			case LEFT: moveLeft(); break;
			case RIGHT: moveRight(); break;
			}
		}
		else if (ch == SPACE)
			moveRight();
		else if (ch == 27)
		{
			ex = exit();
		}
		else if (ch == SAVE)
		{
			try
			{
				saveToFile();
			}
			catch (std::exception &e)
			{
				gotoxy(0, yService, 7);
				std::cout << e.what() << "(press any key)";
				_getch();
				gotoxy(0, yService, 70, 7);
			}
		}
		else if (ch == OPEN)
		{
			try
			{
				openFile();
			}
			catch (std::exception &e)
			{
				gotoxy(0, yService, 7);
				std::cout << e.what() << "(press any key)";
				_getch();
				gotoxy(0, yService, 70, 7);
				gotoxy(xPos, yPos, 7);
			}
		}

	} while (!ex);
}

bool MyFrame::exit() const
{
	bool ex = 0;
	char ch = 0;
	gotoxy(0, yService, 7);
	std::cout << "Do you want to exit ? (y)";
	
	ch = _getch();
	if (ch == 'y' || ch == 'Y')
	{
		gotoxy(0, yService, 70, 7);
		return 1;
	}
	
	gotoxy(0, yService, 70, 7);
	return 0;
	
}

void MyFrame::moveUp()
{
	if (yPos > yMin)
	{
		yPos--;
		posInText -= (xMax - xMin + 1);
		gotoxy(xPos, yPos, 7);
	}
	else if (yPos == yMin && posInTextStart != 0)
	{
		posInTextStart -= (xMax - xMin + 1);
		posInText -= (xMax - xMin + 1);
		readToFrame(1);
	}
}

void MyFrame::moveDown()
{
	if (yPos < yMax)
		yPos++;
	else
	{
		posInTextStart += (xMax - xMin + 1);
		readToFrame(1);
	}
	posInText += (xMax - xMin + 1);
	gotoxy(xPos, yPos, 7);

}

void MyFrame::moveLeft()
{
	if (xPos > xMin)
	{
		xPos--;
		posInText--;
		gotoxy(xPos, yPos, 7);
	}
	else if (xPos == xMin && yPos != yMin)
	{
		xPos = xMax;
		yPos--;
		posInText--;
		gotoxy(xPos, yPos, 7);
	}
	else if (xPos == xMin && yPos == yMin && posInText != 0)
	{
		posInTextStart -= (xMax - xMin + 1);
		xPos = xMax;
		posInText--;
		gotoxy(xPos, yPos, 7);
		readToFrame(1);
	}
}

void MyFrame::moveRight()
{
	if (xPos < xMax)
	{
		xPos++;
		posInText++;
		gotoxy(xPos, yPos, 7);
	}
	else if (xPos == xMax && yPos != yMax)
	{
		xPos = xMin;
		yPos++;
		posInText++;
		gotoxy(xPos, yPos, 7);
	}
	else if (xPos == xMax && yPos == yMax)
	{
		xPos = xMin;
		posInText++;
		posInTextStart += (xMax - xMin + 1);
		gotoxy(xPos, yPos, 7);
		readToFrame(1);
	}
}