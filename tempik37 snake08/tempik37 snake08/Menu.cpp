#include "Menu.h"

Menu::Menu(Nyamka &n, Pole &p, Snake &s) : nyamLink(n), poleLink(p), snakeLink(s), filename("save.dat"), filenameL("l.dat"), xStart(30), yStart(6), ghangedScore(true)
{
	startMenu = { { "1. New Game" }, { "2. Load game" }, {"3. View score"}, { "4. Exit" } };
	pauseMenu = { { "1.Restart" }, { "2.New Game" }, { "3.Save Game" }, { "4.Exit" } };
	newGame = { { "Count nyam: ", std::to_string(nyamLink.getCountNyam()) }, { "Speed: ", std::to_string(snakeLink.getSpeed()) }, { "GO!" } };


}

void Menu::makeGreen(size_t &t) // ������� �������
{
	COORD co = { xStart + newGame[activeIndexMenu][0].size(), activeIndexMenu + yStart };
	SetConsoleCursorPosition(poleLink.hand, co);
	SetConsoleTextAttribute(poleLink.hand, 7 | 2 << 4);
	for (size_t b = newGame[activeIndexMenu][0].size(); b < menuWidth; ++b)
		cout << ' ';
	SetConsoleCursorPosition(poleLink.hand, co);
	std::cin >> t;
	newGame[activeIndexMenu][1] = std::to_string(t);

}

void Menu::backFromGreen() // ������ ��������

{
	COORD co = { xStart + newGame[activeIndexMenu][0].size(), activeIndexMenu + yStart };
	SetConsoleCursorPosition(poleLink.hand, co);
	SetConsoleTextAttribute(poleLink.hand, 7 | 1 << 4);
	cout << newGame[activeIndexMenu][1];
	for (size_t b = newGame[activeIndexMenu][0].size() + newGame[activeIndexMenu][1].size(); b < menuWidth; ++b)
		cout << ' ';
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
	SetConsoleCursorPosition(poleLink.hand, co);
	SetConsoleTextAttribute(poleLink.hand, 7 | 9 << 4);
	const size_t strLen = 16;
	cout << "Enter you name: ";
	SetConsoleTextAttribute(poleLink.hand, 7 | 2 << 4);
	for (size_t a = 0; a < menuWidth - strLen; ++a)
		cout << ' ';
	co.X += strLen;
	SetConsoleCursorPosition(poleLink.hand, co);
	string tempName;
	std::cin >> tempName;

	// �������� ������� �������� � ������
	// � ���� �������� ��� � ����
	
	if (tableScore.empty())
		readScore();
	tableScore.push_back(vector<string> {tempName, std::to_string(nyamLink.getScore())});

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
	t = nyamLink.getScore();
	f.write((char*)&t, sizeof(size_t)); //������� ����
	f.close();

	//����� ����� ��������� ��� ������� ������
	//��� � ���� ������� ���� ������ � �� ��������� :)
	if (tableScore.size()>2)
		std::sort(tableScore.begin() + 1, tableScore.end(), [](const vector<string> &vec1, const vector<string> &vec2) { return std::stoi(vec2[1]) < std::stoi(vec1[1]); });

	runMenu(tableScore, 13);
}

bool Menu::runStartMenu()	// 0 - exit, 1 - start
{
	int res = 0; // -1 - exit, 1 - start, 0 - nothing
	while (!res && runMenu(startMenu)) // ���� ��� (�����) (����� ��� ����� � �������� ���� ����� ����������)
	{
		switch (activeIndexMenu)
		{
		case 0: // new game
			activeIndexMenu = 0;
			while (!res && runMenu(newGame)) // ���� ��� (����� ��� ����� � �������� ���� ����� ����������)
			{
				size_t t = 0;
				switch (activeIndexMenu)
				{
				case 0:
					makeGreen(t); // �������� �����������
					// ������ ���� �������� ������� �����
					nyamLink.setCountNyam(t);
					backFromGreen(); //��������� ��������, ������ ���� ��������

					break;
				case 1:
					makeGreen(t);
					// ������ ���� �������� ������� �����
					snakeLink.setSpeed(t);
					backFromGreen(); // ������ ��������
					break;
				case 2:
					res = 1; // start
					break;
				}
			}
			break;
		case 1:
			// load game
		{
				  loadGame.clear(); // �������, ���� �������� ���������, � ���� ������� ���� � �����
				  loadGame.push_back(vector<string> {"Name - ", "Date"});
				  std::ifstream in(filename, std::ios::in | std::ios::binary);
				  if (!in)
					  loadGame.push_back(vector<string> {"You have no saves!"});
				  while (runMenu(loadGame) && !res)
				  {

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
			runMenu(tableScore, 13);
			break;
		case 3: //exit
			res = -1; // exit
			// exit
			break;
		}
		SetConsoleTextAttribute(poleLink.hand, 7);

	}
	if (res == 1)
		return true;
	return false;
}

bool Menu::runMenu(vector<vector<string>>&arr, size_t width)
{
	SetConsoleTextAttribute(poleLink.hand, 7);
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
			SetConsoleTextAttribute(poleLink.hand, 7 | 9 << 4);
		else
			SetConsoleTextAttribute(poleLink.hand, 7 | 1 << 4);

		co.Y = yStart + a;
		SetConsoleCursorPosition(poleLink.hand, co);

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