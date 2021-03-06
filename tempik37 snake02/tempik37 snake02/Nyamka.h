#pragma once
#include <vector>
#include <Windows.h>
#include <ctime>
#include <exception>
#include <string>
#include "Pole.h"

using std::vector;
using std::exception;
using std::string;

class Nyamka
{
public:
	Nyamka(size_t cN, Pole &p);
	
	bool checkNyam(COORD c); // ��������� ���� ���������� ���� �����. ������� ��������� ��� Snake
	
private:
	struct Nyam
	{
		Nyam(size_t x, size_t y, WORD c, bool a)
		{
			coord.X = x;
			coord.Y = y;
			color = c;
			active = a;
		}
		Nyam(COORD cor, WORD col, bool a) : coord(cor), color(col), active(a) {}
		
		COORD coord;
		WORD color;
		bool active;
	};

	void createNewNyam(Nyam & nyam);
	void showStartNyamki() const;
	inline void showOneNyam(Nyam &n) const;
	vector<Nyam> vecNyam;
	size_t countNyam;  //��������� �������� ������� � �����������
	Pole &pole;
	static const char CharNyamka = 'Z';
		
};

