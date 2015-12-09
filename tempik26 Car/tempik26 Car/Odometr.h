#pragma once
#include "Counter.h"
#include "FuelGauge.h"
class Odometr
{
public:
	Odometr(int wayStart, int kmPL, int capFG, int volFG);
	void getKiloMetrage(char *c) const;
	bool goOneKm();
	FuelGauge * fgPtr();
	int leftKilometers() const;

	~Odometr();
private:
	Counter **way;
	int kmPerLiter;
	int wayLeftToLiter;
	FuelGauge fg;
	Odometr(const Odometr&);
	Odometr& operator=(const Odometr&);
	void tickC(Counter **c, int index = 5);
};

