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

	//������ � ������
	int GetReaminingFuel() const; 
	
	// �� ������
	bool isFull() const;
	
	//������ ����
	bool toFuel(); 
	
	//������� ����
	bool burnFuel();
private:
	int capaticy;
	int volume;
};

