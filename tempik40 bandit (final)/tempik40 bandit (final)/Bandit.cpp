#include "Bandit.h"

Bandit::Bandit(size_t x, size_t y, size_t dep, clock_t stop) : deposit(dep), xMin(x), yMin(y), stopSpan(stop)
{
	pDrum = new Drum*[3];

	pDrum[0] = new Drum(5, xMin + 1, yMin + 1, 0, 5, 50);
	Sleep(500);
	pDrum[1] = new Drum(5, xMin + 3, yMin + 1, 0, 8, 50);
	Sleep(500);
	pDrum[2] = new Drum(5, xMin + 5, yMin + 1, 0, 10, 50);
}
Bandit::~Bandit()
{
	delete pDrum[0];
	delete pDrum[1];
	delete pDrum[2];
	delete[] pDrum;
}

void Bandit::show() const
{
	SetConsoleCursorPosition(Drum::hand, COORD{ xMin, yMin });
	printf_s("%c%c%c%c%c%c%c", 201, 205, 203, 205, 203, 205, 187);

	SetConsoleCursorPosition(Drum::hand, COORD{ xMin, yMin + 1 });
	printf_s("%c%c%c%c%c%c%c", 186, ' ', 186, ' ', 186, ' ', 186);

	SetConsoleCursorPosition(Drum::hand, COORD{ xMin, yMin + 2 });
	printf_s("%c%c%c%c%c%c%c", 204, 205, 206, 205, 206, 205, 185);

	SetConsoleCursorPosition(Drum::hand, COORD{ xMin, yMin + 3 });
	printf_s("%c%c%c%c%c%c%c", 186, ' ', 186, ' ', 186, ' ', 186);

	SetConsoleCursorPosition(Drum::hand, COORD{ xMin, yMin + 4 });
	printf_s("%c%c%c%c%c%c%c", 204, 205, 206, 205, 206, 205, 185);

	SetConsoleCursorPosition(Drum::hand, COORD{ xMin, yMin + 5 });
	printf_s("%c%c%c%c%c%c%c", 186, ' ', 186, ' ', 186, ' ', 186);

	SetConsoleCursorPosition(Drum::hand, COORD{ xMin, yMin + 6 });
	printf_s("%c%c%c%c%c%c%c", 200, 205, 202, 205, 202, 205, 188);

	for (size_t a = 0; a < 3; ++a)
		pDrum[a]->show();

	SetConsoleCursorPosition(Drum::hand, COORD{ xMin, yMin + 10 });
	cout << "Deposit: " << deposit << "          ";

}

void Bandit::hryas()
{

	SetConsoleCursorPosition(Drum::hand, COORD{ xMin, yMin + 8 });
	cout << "                                                        ";

	pointsAnim(deposit, deposit - 100);
	deposit -= 100;
	clock_t defPeriod[3] = { pDrum[0]->getPeriod(), pDrum[1]->getPeriod(), pDrum[2]->getPeriod() };
	do
	{
		for (size_t a = 0; a < 3; ++a)
		if (pDrum[a]->getPeriod()<stopSpan)
			pDrum[a]->update();
	} while (pDrum[0]->getPeriod() < 1500 || pDrum[1]->getPeriod() < 1500 || pDrum[2]->getPeriod() < 1500);

	for (size_t a = 0; a < 3; ++a)
	{
		pDrum[a]->resetCounterUpdate();
		pDrum[a]->setPeriod(defPeriod[a]);
	}
}

size_t Bandit::countPoints()
{
	char res1 = pDrum[0]->getRes();
	char res2 = pDrum[1]->getRes();
	char res3 = pDrum[2]->getRes();

	if (res1 == res2 && res2 == res3)
		return 3;
	else if (res1 == res2 || res2 == res3)
		return 2;

	return 0;
}

void Bandit::pointsAnim(size_t start, size_t fin, clock_t span)
{
	if (start == fin)
		return;

	int k = (start < fin) ? 1 : -1;
	for (; start != fin; start += k)
	{
		SetConsoleCursorPosition(Drum::hand, COORD{ xMin + 9, yMin + 10 });
		cout << start << "          ";
		if (_kbhit() && span>10)
		{
			_getch();
			span -= 30;
		}
		Sleep(span);
	}
	SetConsoleCursorPosition(Drum::hand, COORD{ xMin + 9, yMin + 10 });
	cout << fin << "          ";

}

bool Bandit::game()
{
	char ch = 0;

	while (deposit >= 100)
	{
		SetConsoleCursorPosition(Drum::hand, COORD{ xMin, yMin + 8 });
		cout << "Press enter to start... esc - exit                 ";
		ch = _getch();
		if (ch == 27)
			break;

		hryas();

		switch (countPoints())
		{
		case 3:
			SetConsoleCursorPosition(Drum::hand, COORD{ xMin, yMin + 8 });
			cout << "You win, take 1000 points...                      ";
			while (_kbhit()) _getch(); _getch();
			pointsAnim(deposit, deposit + 1000);
			deposit += 1000;
			break;
		case 2:
			SetConsoleCursorPosition(Drum::hand, COORD{ xMin, yMin + 8 });
			cout << "You win, take 200 points...                         ";
			while (_kbhit()) _getch(); _getch();
			pointsAnim(deposit, deposit + 200);
			deposit += 200;
			break;
		case 0:
			SetConsoleCursorPosition(Drum::hand, COORD{ xMin, yMin + 8 });
			cout << "You loose...                                     ";
			while (_kbhit()) _getch(); _getch();
			break;
		}
		while (_kbhit()) _getch();


	}
	if (deposit >= 100)
		return 1;
	return 0;
}