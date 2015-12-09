#pragma once
#include<iostream>
class FuelGauge
{
public:
	FuelGauge(int cap, int vol) : capaticy(cap), volume(vol)
	{
		if (cap < 0 || vol < 0 || cap < vol)
			exit(1);
	}

	//скільки є палива
	int GetReaminingFuel() const; 
	
	// чи повний
	bool isFull() const;
	
	//залити літру
	bool toFuel(); 
	
	//спалити літру
	bool burnFuel();
private:
	int capaticy;
	int volume;
};

