#pragma once
#include "Drum.h"

class Bandit
{
public:
	Bandit(size_t dep) : deposit(dep)
	{
		Drum **pDrum = new Drum*[3];

		pDrum[0] = new Drum(5, 4, 4, 3, 5, 50, 1500);
		Sleep(500);
		pDrum[1] = new Drum(5, 6, 4, 3, 8, 50, 1500);
		Sleep(500);
		pDrum[2] = new Drum(5, 8, 4, 3, 10, 50, 1500);
	}
	~Bandit();
	void show() const
	{
		for (size_t a = 0; a < 3; ++a)
			pDrum[a]->show();
	}

private:
	Drum** pDrum;
	size_t deposit;
};

