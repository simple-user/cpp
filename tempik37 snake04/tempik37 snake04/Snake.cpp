#include "Snake.h"

Snake::Snake(size_t size, time_t speed, Pole &p, Nyamka &n)
: snakeSpeed(speed), snakeDir(LEFT), indexHead(0), pole(p), nyamLink(n), dirUp(true), colorSnake(7)
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
	else if (nyamLink.checkNyam(co, colorSnake)) // якщо попали на нямку
	{
		snakeArr.emplace_back();
		// зміщуємо значення координат
		//std::copy(snakeArr.rbegin()+1, snakeArr.rend()+1+indexHead, snakeArr.rbegin() ); //я надіюсь що він по одному копіює :)
		
		if (dirUp)
		{
			for (size_t a = snakeArr.size() - 1; a > indexHead; --a)
				snakeArr[a] = snakeArr[a - 1];
		}
		else
		{
			snakeArr[snakeArr.size() - 1] = snakeArr[0];
			for (size_t a = 0; a <indexHead; ++a)
				snakeArr[a] = snakeArr[a + 1];
		}

		snakeArr[indexHead] = co;
		showOne(co, colorSnake);
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

	int res = 0; // -1 - клацнув сам себе, 0 - все норм, 1 - з"їв нямку(ще не знаю де це використати)
	do
	{
		while (!_kbhit() && res!=-1)
		{
			if (clock() - waitStep >= snakeSpeed)  //треба зробити крок
			{
				res=step();
				waitStep = clock();
			}
		}
		
		if (res == -1 || (res == 1 && snakeArr.size() == pole.height * pole.width)) 
			break; // щоб ще не чекав натискання клавіатури

		key[0] = _getch();
		if (_kbhit()) key[1] = _getch();
		if (key[0] == 224)
		{
			if (key[1] != mask[snakeDir] && key[1] != mask[(snakeDir + 2) % 4])  // тобто не в ту саму сторону і не в протилежну
			{
				snakeDir = static_cast<Dir>(mask2.at(key[1]));
			}
			else if (key[1] == mask[(snakeDir + 2) % 4]) // в протилежну сторону
			{
				changeDir();				
			}
		}
	} while (true);

	return res;


}

void Snake::changeDir()
{
	size_t previous = 0;
	if (dirUp)
	{
		dirUp = false;
		indexHead = (indexHead - 1 + snakeArr.size()) % snakeArr.size();  // змінили хвіст голову
		previous = (indexHead - 1 + snakeArr.size()) % snakeArr.size();  //  попередній перед новою головою
	}
	else
	{
		dirUp = true;
		indexHead = (indexHead + 1) % snakeArr.size();
		previous = (indexHead + 1) % snakeArr.size();
	}

	if (snakeArr[previous].X == snakeArr[indexHead].X) // на одній вертикалі
	{
		if (snakeArr[previous].Y == snakeArr[indexHead].Y - 1) // x==x y==x-1
			snakeDir = DOWN;
		else
			snakeDir = UP;
	}
	else //на одній горизонталі
	{
		if (snakeArr[previous].X == snakeArr[indexHead].X - 1) // x==x y==x-1
			snakeDir = RIGHT;
		else
			snakeDir = LEFT;

	}

}