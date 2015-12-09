#include "Odometr.h"

void Odometr::tickC(Counter **c, int index)
{
	if (c[index]->tick() && index > 0)
		tickC(c, index - 1);
}


Odometr::Odometr(int wayStart, int kmPL, int capFG, int volFG) : way(nullptr), kmPerLiter(kmPL), fg(capFG, volFG), wayLeftToLiter(0)
{
	way = new Counter*[6];

	//999999
	int k = 100000;
	for (int a(0); a < 6; a++)
	{
		way[a] = new Counter(0, 9, wayStart / k);
		k /= 10;
	}
}

void Odometr::getKiloMetrage(char *c) const
{
	for (int a(0); a < 6; a++)
		c[a] = way[a]->getNow() + 48;
	c[6] = 0;
}

bool Odometr::goOneKm()
{
	if (wayLeftToLiter)
	{
		wayLeftToLiter--;
		tickC(way);
		return 1;
	}

	if (fg.burnFuel())
	{
		wayLeftToLiter = kmPerLiter;
		wayLeftToLiter--;
		tickC(way);
		return 1;
	}

	return 0;
}

Odometr::~Odometr()
{
	for (int a(0); a < 6; a++)
		delete way[a];
	delete[] way;
}

FuelGauge * Odometr::fgPtr()
{
	return &fg;
}

int Odometr::leftKilometers() const
{
	return wayLeftToLiter;
}