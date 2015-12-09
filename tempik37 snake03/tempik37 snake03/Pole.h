#pragma once
#include <exception>
#include <string>
#include <Windows.h>
#include <iostream>
#include <array>
#include <vector>

using std::string;
using std::exception;
using std::cout;
using std::array;
using std::vector;

bool operator==(COORD a, COORD b);


class Pole
{
public:
	Pole(size_t x, size_t y, size_t w, size_t h);

	const size_t xPos;
	const size_t yPos;
	const size_t width;
	const size_t height;
	const size_t xMin;
	const size_t xMax;
	const size_t yMin;
	const size_t yMax;
	
	void drawPole() const;

	bool chekCoord(size_t x, size_t y) const;  // ������� - 1, ����� - 0
	bool setCoord(size_t x, size_t y, bool b);  // 1 - ������ ��, 0 - � �� ����
	void setTwoCoords( /* size_t x, size_t y, bool b*/);  // ��� �����. 1 -��������, ���� ���������
	bool isFree() const;                        // 1 - � �� ����, 0 - ������ �� 
	const HANDLE hand; // ��� � ��� ��������!
private:
	vector<vector<bool>> vecPole; // ��� ���� - ������� ������� �� �����. 

	//struct point
	//{
	//	size_t x;
	//	size_t y;
	//	bool zan;
	//};
	//vector<point> vecPoints; // ������������.  - � ������ ������� ��� ������������ 

	static const size_t XMAX = 78;
	static const size_t YMAX = 23;
	static const char borderChar = '#';
	
	mutable COORD coord;
	size_t leftFree;
};

