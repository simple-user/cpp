#include "Snake.h"

Snake::Snake(size_t size, time_t speed, Pole &p)
: snakeSpeed(speed), snakeDir(LEFT), indexHead(0), pole(p), dirUp(true)
{
	for (size_t a = 0; a<size; ++a)
	{
		COORD co = { pole.width / 2 + a, pole.height / 2 };
		snakeArr.push_back(co);
		showOne(co);
	}
}


void Snake::step()
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
	replaceIndex(co);

}