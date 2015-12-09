#include "Snake.h"

Snake::Snake(size_t size, time_t speed, Pole &p, Nyamka &n)
: snakeSpeed(speed), snakeDir(LEFT), indexHead(0), pole(p), nyamLink(n), dirUp(true)
{
	for (size_t a = 0; a<size; ++a)
	{
		COORD co = { pole.width / 2 + a, pole.height / 2 };
		snakeArr.push_back(co);
		showOne(co);
		pole.setCoord(co.X, co.Y, 1);
	}
}


int Snake::step()
{
	COORD co;
	co = snakeArr[indexHead];

	switch (snakeDir)
	{
	case LEFT:
		co.X = (co.X - 1 + pole.width) % pole.width;
		break;
	case UP:
		co.Y = (co.Y - 1 + pole.height) % pole.height;
		break;
	case RIGHT:
		co.X = (co.X + 1) % pole.width;
		break;
	case DOWN:
		co.Y = (co.Y + 1) % pole.height;
		break;
	}
	if (std::find(snakeArr.cbegin(), snakeArr.cend(), co) != snakeArr.cend()) // значить клацнув сам себе гейм овер! :)
		return -1;
	else if (nyamLink.checkNyam(co)) // якщо попали на нямку
	{
		snakeArr.emplace_back();
		// зміщуємо значення координат
		//std::copy(snakeArr.rbegin()+1, snakeArr.rend()+1+indexHead, snakeArr.rbegin() ); //я надіюсь що він по одному копіює :)
		for (size_t a = snakeArr.size() - 1;   a>indexHead; --a)
			snakeArr[a] = snakeArr[a - 1];
		
		snakeArr[indexHead] = co;
		showOne(co);
		pole.setCoord(co.X, co.Y, true);
		return 1;
	}

	replaceIndex(co);
	return 0;
}

int Snake::move()
{
	int mask[] = { 75, 72, 77, 80 }; //маска відповідностей в одну сторону

	map<int, int> mask2;           // маска відповідностей в зворотню сторону
	for (int a = 0; a < 4; ++a)
	{
		mask2.insert(std::make_pair(mask[a], a)); 
	}
	
	int key[2] = {};
	time_t waitStep = clock();

	do
	{
		while (!_kbhit())
		{
			if (clock() - waitStep >= snakeSpeed)  //треба зробити крок
			{
				step();
				waitStep = clock();
			}
		}

		key[0] = _getch();
		if (_kbhit()) key[1] = _getch();
		if (key[0] == 224)
		{
			if (key[1] != mask[snakeDir] && key[1] != mask[snakeDir + 2 % 4])  // тобто не в ту саму сторону і не в протилежну
			{
				snakeDir = static_cast<Dir>(mask2.at(key[1]));
			}
		}
	} while (true);

	return 0;


}