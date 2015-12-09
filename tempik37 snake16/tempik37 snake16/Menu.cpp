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
	while (!res && runMenu(startMenu)) // поки тру (ентер) (тобто при виході з нижнього рівня знову показувати)
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

				  // якщо пусто то дописуємо заголовок і будемо зчитувати з файлу
				  // якщо не пусто, значить там вже вся інфа залита під час сейва
				  if (loadGame.empty())
					  loadGameToVector();

				  
				  if (runMenu(loadGame))
				  {
					 
					  if (activeIndexMenu == 0)
						  break;
					  //якщо сюди зайшли значить зайшли по ентер
					  //но в векторах в оперативці тільки назви тому читаємо інфу з файлу
					  std::ifstream f(filename, std::ios::in | std::ios::binary);
					  if (!f.is_open())
						  throw exception(string("Error: can't open file for loading the game").c_str());

					  // activeindex і буде індексом вибору тут!
					  size_t t = 0;
					  size_t xPole = 0;
					  size_t yPole = 0;

					  f.seekg(sizeof(size_t), std::ios::beg); //пропускаємо перше число

					  // спочатку потрібно пройтись по файлу і проскіпувати ті індекси які нам не пторібно
					  for (size_t a = 0; a<activeIndexMenu - 1; ++a) // бо ми вже додали +1 але в файл ще нічого не записали
					  {
						  f.read((char*)&t, sizeof(t)); // кількість букві імя сейва
						  f.seekg(t, std::ios::cur); // проскіпували саме імя

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

					  // дійшли до поточного activeindex
					  f.read((char*)&t, sizeof(t)); //ількість символів імя
					  //f.seekg(t, std::ios::cur); //імя
					  char str[80];
					  f.read(str, t);
					  str[t] = 0;
					  poleLink->delvecPole(); // перед тим як перепишемо вказівник почистим heap
					  //f.read((char*)poleLink, sizeof(Pole)); // записали екземпляр класу поле
					  poleLink->readFromFile(f);
					  f.read((char*)&xPole, sizeof(xPole)); // записали кількість елементів по х
					  f.read((char*)&yPole, sizeof(yPole)); // записали кількість елементів по у
					  Pole::point polePoint;
					  for (xPole = 0; xPole < poleLink->width; ++xPole)
					  {
						  for (yPole = 0; yPole < poleLink->height; ++yPole)
						  {
							  f.read((char*)&polePoint, sizeof(polePoint));
							  poleLink->setPoint(xPole, polePoint);
						  }
					  } // зчитали heap vecPole

					  nyamLink->clear(); //  перед тим як перепишемо вказівник почистим heap
					  // f.read((char*)nyamLink, sizeof(Nyamka)); // екземпляр класу Nyamka
					  nyamLink->readFromFile(f);
					  f.read((char*)&t, sizeof(t)); // кількість нямок
					  Nyamka::Nyam nya;
					  for (size_t a = 0; a < t; ++a)
					  {
						  f.read((char*)&nya, sizeof(nya));
						  nyamLink->setNyam(nya);
					  } // heap нямок

					  snakeLink->clear(); //  перед тим як перепишемо вказівник почистим heap
					  //f.read((char*)snakeLink, sizeof(Snake)); // екземпляр Snake
					  snakeLink->readFromFile(f);
					  f.read((char*)&t, sizeof(t)); // кількість елементів snake
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
					  res = 1; // для виходу з менюшок

					  //size_t t = 0;
					  //for (size_t a = 0; a < activeIndexMenu; ++a)
					  //{
					  //	f.read((char*)&t, sizeof(t));
					  //	// тут число кількості букв вже зчитане і його не потрібно пропускати
					  //	// тому починаємо з імя (тобто з пропуску t char-ів)
					  //	f.seekg(t + sizeof(Pole)+sizeof(Nyamka)+sizeof(Snake), std::ios::cur);
					  //}
					  //// підійшли до поточного запису (а саме до числа кількості симвролів імені)
					  //// число кількосі символів і міе ім"я і треба пропустити
					  //f.read((char*)&t, sizeof(t));
					  //f.seekg(t, std::ios::cur);
					  //f.read((char*)poleLink, sizeof(Pole));
					  //f.read((char*)nyamLink, sizeof(Nyamka));
					  //f.read((char*)snakeLink, sizeof(Snake));
					  ////поновимо вказівники у інших класах
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
				// якщо тільки зчитали - треба сортонути	
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
	while (!res && runMenu(newGame)) // поки тру (тобто при виході з нижнього рівня знову показувати)
	{
		size_t t = 0;
		switch (activeIndexMenu)
		{
		case 0:
			makeGreen(t); // виділяємо зелененьким
			// вводим нове значення кількості нямок
			nyamLink->setCountNyam(t);
			backFromGreen(); //прибираємо зеленень, лишаємо нове значення

			break;
		case 1:
			makeGreen(t);
			// вводим нове значення кількості нямок
			snakeLink->setSpeed(t);
			backFromGreen(); // знімаємо виділення
			break;
		case 2:
			res = 1; // start
			return res;
			break;
		}
	}
	return res;
}

void Menu::makeGreen(size_t &t) // виділяєм зеленим
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

void Menu::backFromGreen() // знімаємо виділення

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

	// якщо пусто в векторі то зчитуємо всю інфу
	if (loadGame.empty())
	{
		loadGameToVector();
	}

	std::fstream f(filename, std::ios::in | std::ios::out | std::ios::binary); // для початку треба зчитати кількість вже записаних ігор
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

	// тепер допишемо в кінець вектора поточну зберігачку
	// а потім запишемо її у файл
	loadGame.push_back(vector<string> {name, "Date"});

	// тепер записуємо поточну зберігачку у файл
	// стурктура
	// [кількість сейвів]
	// [кількість букв назви сейву][назва сейву]
	// [Pole][кількість елементів vector<vector<point>> vecPole x][кількість елементів vector<vector<point>> vecPole y][інфа з хіп: vector<vector<point>> vecPole ]
	// [Nyamka][кількість улументів vector<Nyam> vecNyam][інфа з хіп vector<Nyam> vecNyam]
	// [Snake][кількість елементів vector<COORD> snakeArr][інфа з хіп vector<COORD> snakeArr]

	t = name.size();
	f.seekp(0, std::ios::end); // перемістились в кінець, і будем писати вже саму гру
	f.write((char*)&t, sizeof(t)); //ількість символів імя
	f.write(name.c_str(), t); //записали імя

	poleLink->writeToFile(f); // записали усі поля класу поле  (без вектора!)
	xPole = poleLink->width;
	yPole = poleLink->height;
	f.write((char*)&xPole, sizeof(xPole)); // записали кількість елементів по х
	f.write((char*)&yPole, sizeof(yPole)); // записали кількість елементів по у
	Pole::point polePointT;
	for (xPole = 0; xPole < poleLink->width; ++xPole)
	{
		for (yPole = 0; yPole < poleLink->height; ++yPole)
		{
			polePointT = poleLink->getPoint(xPole, yPole);
			f.write((char*)&polePointT, sizeof(Pole::point));
		}
	} // записали heap vecPole

	nyamLink->writeToFile(f); // записали усі поля Nyamka без вектора
	t = nyamLink->getCountNyam();
	f.write((char*)&t, sizeof(t)); // кількість нямок
	Nyamka::Nyam nyamkaNyamT;
	for (size_t a = 0; a < t; ++a)
	{
		nyamkaNyamT = nyamLink->getNyam(a);
		f.write((char*)&nyamkaNyamT, sizeof(Nyamka::Nyam));
	} // heap нямок


	snakeLink->writeToFile(f); // записали всі поля Snake без вектора
	t = snakeLink->getCountSnakeElements();
	f.write((char*)&t, sizeof(t)); // кількість елементів snake
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
	loadGame.clear(); // радше страховочка
	// пишемо заголовок
	loadGame.push_back(vector<string> {"Name - ", "Date"});

	// дивимос файл. якщо там щось є - зчитуємо
	std::ifstream f(filename, std::ios::in | std::ios::binary);

	if (!f.is_open()) // якщо файла не існує, то створимо і запишемо нулик
	{
		std::ofstream f(filename, std::ios::out | std::ios::binary);
		size_t t = 0;
		f.write((char*)&t, sizeof(t));
	}
	else
	{
		// стурктура
		// [кількість сейвів]
		// [кількість букв назви сейву][назва сейву]
		// [Pole][кількість елементів vector<vector<point>> vecPole x][кількість елементів vector<vector<point>> vecPole y][інфа з хіп: vector<vector<point>> vecPole ]
		// [Nyamka][кількість улументів vector<Nyam> vecNyam][інфа з хіп vector<Nyam> vecNyam]
		// [Snake][кількість елементів vector<COORD> snakeArr][інфа з хіп vector<COORD> snakeArr]

		size_t t = 0;
		size_t countLoads = 0;
		size_t strLen = 0;
		size_t xPole = 0;
		size_t yPole = 0;

		f.seekg(0, std::ios::beg);
		f.read((char*)&countLoads, sizeof(countLoads)); // зчитали кількість сейвів

		char str[80];
		// f.seekg(sizeof(size_t), std::ios::beg); //пропускаємо перше число
		for (size_t a = 0; a<countLoads; ++a)
		{
			f.read((char*)&t, sizeof(t)); // кількість букві імя сейва
			strLen = t > 79 ? 79 : t;
			f.read(str, strLen); // зчитали імя сейва
			str[strLen] = '\0';
			loadGame.push_back(vector<string> {str, "Date"});

			// треба перейти до наступоного size_t - кількості символів сейва
			// якщо це не остання прочитка
			// якщо остання прочитка то далі йти смислу немає (нам потрібні тільки імена)
			if (a == countLoads - 1)
				break;


			// якщо довжину зчитуємого ім"я ми таки обрізали:
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
			if (countChar>79) countChar = 79; // якщо вдруг хтось розкашелився зі своїм ім"ям
			f.read(str, countChar);
			str[countChar] = '\0';
			f.read((char*)&score, sizeof(size_t));
			tableScore.push_back(vector<string> {string(str), std::to_string(score)});
		}

		f.close();
	}

}

void Menu::SaveScore() // і його же ж треба вивести
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

	// спочатку внесемо значення в вектор
	// а потім запишемо все у файл
	
	if (tableScore.empty())
		readScore();
	tableScore.push_back(vector<string> {tempName, std::to_string(nyamLink->getScore())});

	// стркуктура:
	//[кількість рядків]
	//[кількість букв імені][імя][кількість очок]
	size_t t = 0;
	std::fstream f(filenameL, std::ios::in | std::ios::out | std::ios::binary);
	if (!f.is_open())
	{
		f.open(filenameL, std::ios::out | std::ios::binary);
		t = 1;
		f.write((char*)&t, sizeof(size_t)); // якщо файл пустий - вписуєм спочатку 1 (кількість рядків) (тобто цей один рядок зараз додамо)
	}
	else
	{
		f.seekg(0, std::ios::beg);
		f.read((char*)&t, sizeof(size_t)); //зчитали поточну кількість рядків
		++t;
		f.seekp(0, std::ios::beg);
		f.write((char*)&t, sizeof(size_t)); //записали кількість +1
		f.seekp(0, std::ios::end); //перейшли в кінеці файлу, щоб дописати поточну
	}

	t = tempName.size();
	f.write((char*)&t, sizeof(size_t)); // кількість букв імені
	f.write(tempName.c_str(), tempName.size()); //саме ім"я
	t = nyamLink->getScore();
	f.write((char*)&t, sizeof(size_t)); //кількість очок
	f.close();

	//тепер треба сортонути без першого запису
	//але у тому випадку коли взагалі є що сортувати :)
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
	if (runMenu(pauseMenu, false)) // клікнути ентєр по якомусь пункту
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
	// якщо не зайли в if значить ESC - і рубимось далі

}
