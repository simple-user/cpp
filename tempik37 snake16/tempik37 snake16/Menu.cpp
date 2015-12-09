#include "Menu.h"

Menu::Menu(Nyamka &n, Pole &p, Snake &s) : nyamLink(&n), poleLink(&p), snakeLink(&s), filename("save.dat"), filenameL("l.dat"), xStart(30), yStart(6), ghangedScore(true), loadingGame(false)
{
	startMenu = { { "1. New Game" }, { "2. Load game" }, {"3. View score"}, { "4. Exit" } };
	pauseMenu = { { "1.Restart" }, { "2.New Game" }, { "3.Save Game" }, { "4.Main Menu" } };
	newGame = { { "Count nyam: ", std::to_string(nyamLink->getCountNyam()) }, { "Speed: ", std::to_string(snakeLink->getSpeed()) }, { "GO!" } };


}


bool Menu::runStartMenu()	// 0 - exit, 1 - start
{
	int res = 0; // -1 - exit, 1 - start, 0 - nothing
	while (!res && runMenu(startMenu)) // ���� ��� (�����) (����� ��� ����� � �������� ���� ����� ����������)
	{
		switch (activeIndexMenu)
		{
		case 0: // new game
			loadingGame = false;
			res = startNewGame();
			break;
		case 1:
			// load game
		{

				  // ���� ����� �� �������� ��������� � ������ ��������� � �����
				  // ���� �� �����, ������� ��� ��� ��� ���� ������ �� ��� �����
				  if (loadGame.empty())
					  loadGameToVector();

				  
				  if (runMenu(loadGame))
				  {
					 
					  if (activeIndexMenu == 0)
						  break;
					  //���� ���� ������ ������� ������ �� �����
					  //�� � �������� � ���������� ����� ����� ���� ������ ���� � �����
					  std::ifstream f(filename, std::ios::in | std::ios::binary);
					  if (!f.is_open())
						  throw exception(string("Error: can't open file for loading the game").c_str());

					  // activeindex � ���� �������� ������ ���!
					  size_t t = 0;
					  size_t xPole = 0;
					  size_t yPole = 0;

					  f.seekg(sizeof(size_t), std::ios::beg); //���������� ����� �����

					  // �������� ������� �������� �� ����� � ����������� � ������� �� ��� �� �������
					  for (size_t a = 0; a<activeIndexMenu - 1; ++a) // �� �� ��� ������ +1 ��� � ���� �� ����� �� ��������
					  {
						  f.read((char*)&t, sizeof(t)); // ������� ���� ��� �����
						  f.seekg(t, std::ios::cur); // ����������� ���� ���

						  //pole
						  f.seekg(poleLink->getSizeSkip(), std::ios::cur);
						  f.read((char*)&xPole, sizeof(xPole));
						  f.read((char*)&yPole, sizeof(yPole));
						  f.seekg(xPole*yPole*sizeof(Pole::point), std::ios::cur); //heap
						  //end pole

						  //nyamka
						  f.seekg(nyamLink->getSizeSkip(), std::ios::cur);
						  f.read((char*)&t, sizeof(t));
						  f.seekg(t*sizeof(Nyamka::Nyam), std::ios::cur); //heap
						  //end nyamka

						  //snake
						  f.seekg(snakeLink->getSizeSkip(), std::ios::cur);
						  f.read((char*)&t, sizeof(t));
						  f.seekg(t*sizeof(COORD), std::ios::cur);
						  //end snake
					  }

					  // ����� �� ��������� activeindex
					  f.read((char*)&t, sizeof(t)); //������� ������� ���
					  //f.seekg(t, std::ios::cur); //���
					  char str[80];
					  f.read(str, t);
					  str[t] = 0;
					  poleLink->delvecPole(); // ����� ��� �� ���������� �������� �������� heap
					  //f.read((char*)poleLink, sizeof(Pole)); // �������� ��������� ����� ����
					  poleLink->readFromFile(f);
					  f.read((char*)&xPole, sizeof(xPole)); // �������� ������� �������� �� �
					  f.read((char*)&yPole, sizeof(yPole)); // �������� ������� �������� �� �
					  Pole::point polePoint;
					  for (xPole = 0; xPole < poleLink->width; ++xPole)
					  {
						  for (yPole = 0; yPole < poleLink->height; ++yPole)
						  {
							  f.read((char*)&polePoint, sizeof(polePoint));
							  poleLink->setPoint(xPole, polePoint);
						  }
					  } // ������� heap vecPole

					  nyamLink->clear(); //  ����� ��� �� ���������� �������� �������� heap
					  // f.read((char*)nyamLink, sizeof(Nyamka)); // ��������� ����� Nyamka
					  nyamLink->readFromFile(f);
					  f.read((char*)&t, sizeof(t)); // ������� �����
					  Nyamka::Nyam nya;
					  for (size_t a = 0; a < t; ++a)
					  {
						  f.read((char*)&nya, sizeof(nya));
						  nyamLink->setNyam(nya);
					  } // heap �����

					  snakeLink->clear(); //  ����� ��� �� ���������� �������� �������� heap
					  //f.read((char*)snakeLink, sizeof(Snake)); // ��������� Snake
					  snakeLink->readFromFile(f);
					  f.read((char*)&t, sizeof(t)); // ������� �������� snake
					  COORD co;
					  for (size_t a = 0; a < t; ++a)
					  {
						  f.read((char*)&co, sizeof(co));
						  snakeLink->setCoordSnakeElem(co);
					  }// heap snake


					  nyamLink->setPoleLink(poleLink);
					  snakeLink->setNyamLink(nyamLink);
					  snakeLink->setPoleLink(poleLink);

					  f.close();

					  loadingGame = true;
					  res = 1; // ��� ������ � �������

					  //size_t t = 0;
					  //for (size_t a = 0; a < activeIndexMenu; ++a)
					  //{
					  //	f.read((char*)&t, sizeof(t));
					  //	// ��� ����� ������� ���� ��� ������� � ���� �� ������� ����������
					  //	// ���� �������� � ��� (����� � �������� t char-��)
					  //	f.seekg(t + sizeof(Pole)+sizeof(Nyamka)+sizeof(Snake), std::ios::cur);
					  //}
					  //// ������ �� ��������� ������ (� ���� �� ����� ������� �������� ����)
					  //// ����� ������ ������� � �� ��"� � ����� ����������
					  //f.read((char*)&t, sizeof(t));
					  //f.seekg(t, std::ios::cur);
					  //f.read((char*)poleLink, sizeof(Pole));
					  //f.read((char*)nyamLink, sizeof(Nyamka));
					  //f.read((char*)snakeLink, sizeof(Snake));
					  ////�������� ��������� � ����� ������
					  //nyamLink->setPoleLink(poleLink);
					  //snakeLink->setPoleLink(poleLink);
					  //snakeLink->setNyamLink(nyamLink);
					  //f.close();


				  }

		}
			break;
		case 2: //view score
			if (tableScore.empty())
			{
				readScore();
				// ���� ����� ������� - ����� ���������	
				if (tableScore.size() > 2)
					std::sort(tableScore.begin() + 1, tableScore.end(), [](const vector<string> &vec1, const vector<string> &vec2) { return std::stoi(vec2[1]) < std::stoi(vec1[1]); });
			}
			runMenu(tableScore, true, 13);
			break;
		case 3: //exit
			res = -1; // exit
			// exit
			break;
		}
		SetConsoleTextAttribute(poleLink->hand, 7);

	}
	if (res == 1)
		return true;
	return false;
}

int Menu::startNewGame()
{
	int res = 0;
	activeIndexMenu = 0;
	nyamLink->setCountNyam(std::stoi(newGame[0][1]));
	snakeLink->setSpeed(std::stoi(newGame[1][1]));
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

void Menu::makeGreen(size_t &t) // ������� �������
{
	COORD co = { xStart + newGame[activeIndexMenu][0].size(), activeIndexMenu + yStart };
	SetConsoleCursorPosition(poleLink->hand, co);
	SetConsoleTextAttribute(poleLink->hand, activeMenuColorEdit);
	for (size_t b = newGame[activeIndexMenu][0].size(); b < menuWidth; ++b)
		cout << ' ';
	SetConsoleCursorPosition(poleLink->hand, co);
	std::cin >> t;
	newGame[activeIndexMenu][1] = std::to_string(t);

}

void Menu::backFromGreen() // ������ ��������

{
	COORD co = { xStart + newGame[activeIndexMenu][0].size(), activeIndexMenu + yStart };
	SetConsoleCursorPosition(poleLink->hand, co);
	SetConsoleTextAttribute(poleLink->hand, inactiveMenuColor);
	cout << newGame[activeIndexMenu][1];
	for (size_t b = newGame[activeIndexMenu][0].size() + newGame[activeIndexMenu][1].size(); b < menuWidth; ++b)
		cout << ' ';
}

void Menu::saveGame(const string & name)
{
	size_t t = 0;
	size_t countLoads = 0;
	size_t strLen = 0;
	size_t xPole = 0;
	size_t yPole = 0;

	// ���� ����� � ������ �� ������� ��� ����
	if (loadGame.empty())
	{
		loadGameToVector();
	}

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

	poleLink->writeToFile(f); // �������� �� ���� ����� ����  (��� �������!)
	xPole = poleLink->width;
	yPole = poleLink->height;
	f.write((char*)&xPole, sizeof(xPole)); // �������� ������� �������� �� �
	f.write((char*)&yPole, sizeof(yPole)); // �������� ������� �������� �� �
	Pole::point polePointT;
	for (xPole = 0; xPole < poleLink->width; ++xPole)
	{
		for (yPole = 0; yPole < poleLink->height; ++yPole)
		{
			polePointT = poleLink->getPoint(xPole, yPole);
			f.write((char*)&polePointT, sizeof(Pole::point));
		}
	} // �������� heap vecPole

	nyamLink->writeToFile(f); // �������� �� ���� Nyamka ��� �������
	t = nyamLink->getCountNyam();
	f.write((char*)&t, sizeof(t)); // ������� �����
	Nyamka::Nyam nyamkaNyamT;
	for (size_t a = 0; a < t; ++a)
	{
		nyamkaNyamT = nyamLink->getNyam(a);
		f.write((char*)&nyamkaNyamT, sizeof(Nyamka::Nyam));
	} // heap �����


	snakeLink->writeToFile(f); // �������� �� ���� Snake ��� �������
	t = snakeLink->getCountSnakeElements();
	f.write((char*)&t, sizeof(t)); // ������� �������� snake
	COORD coordT;
	for (size_t a = 0; a < t; ++a)
	{
		coordT = snakeLink->getCoordSnakeElem(a);
		f.write((char*)&coordT, sizeof(COORD));
	}// heap snake

	f.close();
}

void Menu::loadGameToVector()
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
		// [������� ���� ����� �����][����� �����]
		// [Pole][������� �������� vector<vector<point>> vecPole x][������� �������� vector<vector<point>> vecPole y][���� � ���: vector<vector<point>> vecPole ]
		// [Nyamka][������� �������� vector<Nyam> vecNyam][���� � ��� vector<Nyam> vecNyam]
		// [Snake][������� �������� vector<COORD> snakeArr][���� � ��� vector<COORD> snakeArr]

		size_t t = 0;
		size_t countLoads = 0;
		size_t strLen = 0;
		size_t xPole = 0;
		size_t yPole = 0;

		f.seekg(0, std::ios::beg);
		f.read((char*)&countLoads, sizeof(countLoads)); // ������� ������� �����

		char str[80];
		// f.seekg(sizeof(size_t), std::ios::beg); //���������� ����� �����
		for (size_t a = 0; a<countLoads; ++a)
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
			f.seekg(poleLink->getSizeSkip(), std::ios::cur);
			f.read((char*)&xPole, sizeof(xPole));
			f.read((char*)&yPole, sizeof(yPole));
			f.seekg(xPole*yPole*sizeof(Pole::point), std::ios::cur); //heap
			//end pole

			//nyamka
			f.seekg(nyamLink->getSizeSkip(), std::ios::cur);
			f.read((char*)&t, sizeof(t));
			f.seekg(t*sizeof(Nyamka::Nyam), std::ios::cur); //heap
			//end nyamka

			//snake
			f.seekg(snakeLink->getSizeSkip(), std::ios::cur);
			f.read((char*)&t, sizeof(t));
			f.seekg(t*sizeof(COORD), std::ios::cur);
			//end snake
		}

	}
	f.close();
}

void Menu::readScore()
{
	tableScore.clear();
	tableScore.push_back(vector<string> {"Name", "Score"});
	std::ifstream f(filenameL, std::ios::in | std::ios::binary);
	if (!f.is_open())
	{
		std::ofstream of(filenameL, std::ios::out);
		size_t t = 0;
		of.write((char*)&t, sizeof(t));
		of.close();
	}
	else
	{
		size_t t = 0;
		f.seekg(0, std::ios::beg);
		f.read((char*)&t, sizeof(t));
		size_t countChar;
		char str[80];
		size_t score;

		for (size_t a = 0; a < t; ++a)
		{
			f.read((char*)&countChar, sizeof(size_t));
			if (countChar>79) countChar = 79; // ���� ����� ����� ������������ � ���� ��"��
			f.read(str, countChar);
			str[countChar] = '\0';
			f.read((char*)&score, sizeof(size_t));
			tableScore.push_back(vector<string> {string(str), std::to_string(score)});
		}

		f.close();
	}

}

void Menu::SaveScore() // � ���� �� � ����� �������
{
	COORD co = { xStart, yStart };
	SetConsoleCursorPosition(poleLink->hand, co);
	SetConsoleTextAttribute(poleLink->hand, activeMenuColor);
	const size_t strLen = 16;
	cout << "Enter you name: ";
	SetConsoleTextAttribute(poleLink->hand, 7 | 2 << 4);
	for (size_t a = 0; a < menuWidth - strLen; ++a)
		cout << ' ';
	co.X += strLen;
	SetConsoleCursorPosition(poleLink->hand, co);
	string tempName;
	std::cin >> tempName;

	// �������� ������� �������� � ������
	// � ���� �������� ��� � ����
	
	if (tableScore.empty())
		readScore();
	tableScore.push_back(vector<string> {tempName, std::to_string(nyamLink->getScore())});

	// ����������:
	//[������� �����]
	//[������� ���� ����][���][������� ����]
	size_t t = 0;
	std::fstream f(filenameL, std::ios::in | std::ios::out | std::ios::binary);
	if (!f.is_open())
	{
		f.open(filenameL, std::ios::out | std::ios::binary);
		t = 1;
		f.write((char*)&t, sizeof(size_t)); // ���� ���� ������ - ������ �������� 1 (������� �����) (����� ��� ���� ����� ����� ������)
	}
	else
	{
		f.seekg(0, std::ios::beg);
		f.read((char*)&t, sizeof(size_t)); //������� ������� ������� �����
		++t;
		f.seekp(0, std::ios::beg);
		f.write((char*)&t, sizeof(size_t)); //�������� ������� +1
		f.seekp(0, std::ios::end); //�������� � ����� �����, ��� �������� �������
	}

	t = tempName.size();
	f.write((char*)&t, sizeof(size_t)); // ������� ���� ����
	f.write(tempName.c_str(), tempName.size()); //���� ��"�
	t = nyamLink->getScore();
	f.write((char*)&t, sizeof(size_t)); //������� ����
	f.close();

	//����� ����� ��������� ��� ������� ������
	//��� � ���� ������� ���� ������ � �� ��������� :)
	if (tableScore.size()>2)
		std::sort(tableScore.begin() + 1, tableScore.end(), [](const vector<string> &vec1, const vector<string> &vec2) { return std::stoi(vec2[1]) < std::stoi(vec1[1]); });

	runMenu(tableScore, true, 13);
}

bool Menu::runMenu(vector<vector<string>>&arr, bool clear, size_t width)
{
	SetConsoleTextAttribute(poleLink->hand, 7);
	if (clear)
		system("cls");

	bool res = false;

	activeIndexMenu = 0;
	writeMenu(arr, 0, arr.size() - 1, width);


	int key[2] = {};
	do
	{
		key[0] = _getch();
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
				if (activeIndexMenu < arr.size() - 1)
				{
					++activeIndexMenu;
					writeMenu(arr, activeIndexMenu - 1, activeIndexMenu);
				}
				break;
			case UPm:
				if (activeIndexMenu >0)
				{
					--activeIndexMenu;
					writeMenu(arr, activeIndexMenu, activeIndexMenu + 1);
				}
				break;
			}
		}

	} while (key[0] != ESCm && key[0] != ENTERm);

	return res;
}

void Menu::writeMenu(vector<vector<string>> &arr, size_t indexStart, size_t indexEnd, size_t width)
{
	COORD co = { xStart, yStart };
	size_t countLeters = 0;
	for (size_t a = indexStart; a <= indexEnd; ++a)
	{
		if (a == activeIndexMenu)
			SetConsoleTextAttribute(poleLink->hand, activeMenuColor);
		else
			SetConsoleTextAttribute(poleLink->hand, inactiveMenuColor);

		co.Y = yStart + a;
		SetConsoleCursorPosition(poleLink->hand, co);

		countLeters = 0;
		//std::for_each(arr[a].begin(), arr[a].end(), [&countLeters](string &s) { countLeters += s.size(); cout << s; });

		for (size_t c = 0; c < arr[a].size(); ++c)
		{
			if (!c && width)
				arr[a][c].resize(width, ' ');
			countLeters += arr[a][c].size();
			cout << arr[a][c];
		}

		for (size_t b = countLeters; b < menuWidth; ++b)
			cout << ' ';
	}
}

int Menu::runPauseMenu()
{ 
	if (runMenu(pauseMenu, false)) // ������� ���� �� ������� ������
	{
		switch (activeIndexMenu)
		{
		case 0: //restart
			return 0;
			break;
		case 1: //new game
			return 1;
			break;
		case 2: // save game
			return 2;
			break;
		case 3: // main menu
			return 3;
			break;
		}
	}
	return -1;
	// ���� �� ����� � if ������� ESC - � �������� ���

}
