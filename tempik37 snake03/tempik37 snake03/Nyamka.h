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
	
	bool checkNyam(COORD c); // �������� ���� ���������� ���� �����. ������� ��������� ��� Snake
	
private:
	struct Nyam
	{
		Nyam(size_t x, size_t y, WORD c)
		{
			coord.X = x;
			coord.Y = y;
			color = c;
		}
		Nyam(COORD cor, WORD col) : coord(cor), color(col){}
		
		COORD coord;
		WORD color;
	};

	void createNewNyam(vector<Nyam>::iterator &itNyam);
	void showStartNyamki() const;
	inline void showOneNyam(Nyam n) const;
	vector<Nyam> vecNyam;
	size_t countNyam;  //��������� �������� ������� � �����������
	Pole &pole;
	static const char CharNyamka = 'Z';
		
};

