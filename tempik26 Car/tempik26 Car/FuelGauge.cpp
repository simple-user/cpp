#include "FuelGauge.h"


int FuelGauge::GetReaminingFuel() const //скільки є палива
{
	return volume;
}

bool FuelGauge::isFull() const
{
	return volume == capaticy;
}
bool FuelGauge::toFuel()
{
	if (capaticy - volume >= 1)
	{
		volume++;
		return 1;
	}
	
	return 0;
}
bool FuelGauge::burnFuel()
{
	if (volume > 0)
	{
		volume--;
		return 1;
	}

	return 0;
}
