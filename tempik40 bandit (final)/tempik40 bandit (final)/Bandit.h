#pragma once
#include <conio.h>
#include "Drum.h"

class Bandit
{
public:
	Bandit(size_t x, size_t y, size_t dep, clock_t stop);
	~Bandit();
	
	void show() const;
	void hryas();

	size_t countPoints();

	void pointsAnim(size_t start, size_t fin, clock_t span = 100);

	bool game();

private:
	clock_t stopSpan;
	size_t xMin;
	size_t yMin;
	Drum** pDrum;
	size_t deposit;
};

