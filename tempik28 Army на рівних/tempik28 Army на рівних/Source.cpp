#include <iostream>
#include <Windows.h>
#include "Army.h"
#include <typeinfo>
#include <typeinfo.h>
using namespace std;

int main()
{
	
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(unsigned(time(0)));

	// �������� ���� � ��쳿
	Army ar1(5);
	std::cout << "Wait please a secont. It's all for dear srand()! :)\n";
	Sleep(1000);
	Army ar2(5);
	bool win = 0;
	bool firstAttak = rand() % 2;

	// ������� ������
	std::cout << "The First Army:\n";
	ar1.printArmy();
	std::cout << "The Second Army:\n";
	ar2.printArmy();
	
	std::cout << "We are ready! This is gonna be really great figth!!!\n";
	system("pause");

	do
	{
		system("cls");
		// ���� ��������� ������ ����� �������� ������
		std::cout << "The First Army:\n";
		ar1.printArmy();
		std::cout << "The Second Army:\n";
		ar2.printArmy();

		// ��������� �������
		if (firstAttak)
		{
			std::cout << "The First Army attaks!\n";
			win = ar1.attack(ar2);
			firstAttak = 0;
		}
		else
		{
			std::cout << "The Second Army attaks!\n";
			win = ar2.attack(ar1);
			firstAttak = 1;
		}
		
		// Sleep(50);
		system("pause");

	} while (!win);
	
	system("cls");
	// � ���� ��� ������� ������� ������ (� ������ ������� ���� ������)
	std::cout << "The First Army:\n";
	ar1.printArmy();
	std::cout << "The Second Army:\n";
	ar2.printArmy();

	// � ������� ���������.
	std::cout << "The Winer is: " << int(firstAttak) + 1 << " Army!\n";

	return 0;

}

