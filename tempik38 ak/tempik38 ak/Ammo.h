#pragma once
//#include <random>
#include <ctime>
#include <cstdlib>

class Ammo
{
public:
	Ammo() : number(numberStar++)	{};
	Ammo(size_t num) : number(num) {} // ��� ��������� �������� ��� �� �� ���� �������� �� ������� :)))
	
	bool pif() // ������� ����� � ���� �� �
	{
		return rand() % 99 < 70;
	}

	size_t getNumber() const
	{
		return number;
	}

	static size_t numberStar;
private:
	size_t number;
};

