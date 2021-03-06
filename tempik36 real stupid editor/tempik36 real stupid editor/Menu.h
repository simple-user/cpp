#pragma once
#include <vector>
#include <string>
#include <Windows.h>
#include <iostream>
#include <conio.h>

using std::vector;
using std::string;
using std::cout;
using std::cin;
using std::endl;

const int SCREENWIDTH = 80;
enum Buttons { UP = 72, DOWN = 80, LEFT = 75, RIGHT = 77, ESC = 27, SPACE = 32, ENTER = 13, SKIP = 224 };
void gotoxy(int x, int y, WORD color);
void gotoxy(int x, int y, int count, WORD color);
void gotoxy(int x, int y, int countX, int countY,  WORD color);


class Menu
{
private:
	struct PunktMenushka
	{
		string strPunkt; // ����� ������ ����
		int addrPunktN; // ������ ������
		int indexChildMenu; // ������ �������� ������� � �����
		// �����������:
		// int nomMenu; // ����� ������ ����
	};
	struct  Menushka
	{
		int xPos;
		int yPos;
		int addrMenuN; //������ �������
		int indexParentMenu; // ������ ���������� ������� � ����� 
		size_t maxLenPunkt; //������� ������� ���������� ������
		size_t activePunktIndex; // ������ ��������� ������
		vector<PunktMenushka> arrPunkt; // ����� ������
		// �����������:
		// int indexMenu; //������ ������� � �����
		// int levelMenu; // ����� ����
		// int nomParrentMenu; //����� ������ ��������� ������
	};
	
	vector<Menushka> menu; // ����� �������
	int activeMenushkaIndex;
	WORD activeMenuColor;
	WORD activePunctColor;
	WORD inactiveMenuColor;
	WORD inactivePunctColor;

	void printMenushka(bool gray = 0, int indMenu = -1) const;
	void printMenushkaBlack(int indMenu = -1) const;
	void goUp();
	void goDown();
	int goEnter(bool Enter=1);
	void goEsc(bool Ecs=1);
public:
	Menu(WORD actMCol = 7 | 4 << 4, WORD actPCol = 15 | 12 << 4, WORD inactMCol = 7 | 0 << 4, WORD inactPCol = 7 | 1 << 4);
	bool addMenu(int addr);
	bool addPunkt(int addrMenuNum, string name);
	int runMenu(int addr=0);

};

