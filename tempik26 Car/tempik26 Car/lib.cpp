#include <iostream>
#include "Menu.h"
#include "lib.h"



bool odInit(Odometr *&od)
{
	if (od)
	{
		gotoxy(0, 9, 7);
		cout << "Parameters are cleared!" << endl;
		delete od;
	}

	int kmpl = 0;
	int cap = 0;
	int vol = 0;

	gotoxy(0, 10, 7);
	cout << "Input km per liter: "; cin >> kmpl;
	cout << "Input capacity of fuel gauge: "; cin >> cap;
	cout << "Input volume of fuel gauge: "; cin >> vol;

	od = new Odometr(0, kmpl, cap, vol);

	cout << "OK!" << endl;
	system("pause");
	system("cls");

	return 1;
}

void goOneKm(Odometr *od)
{
	gotoxy(0, 10, 7);
	if (!od)
		cout << "Parameters are not initialized!" << endl;
	else
	{
		goKM(od, 1);
	}
	system("pause");
	system("cls");

}
void goXKm(Odometr *od)
{
	gotoxy(0, 10, 7);
	if (!od)
		cout << "Parameters are not initialized!" << endl;
	else
	{
		int t = 0;
		gotoxy(0, 10, 7);
		cout << "Input count kilometers to move: "; cin >> t;
		goKM(od, t);
	}
	system("pause");
	system("cls");

}

void putOneLiter(Odometr *od)
{
	gotoxy(0, 10, 7);
	if (!od)
		cout << "Parameters are not initialized!" << endl;
	else
		putLiter(od, 1);

	system("pause");
	system("cls");
}

void putXLiters(Odometr *od)
{
	gotoxy(0, 10, 7);
	if (!od)
		cout << "Parameters are not initialized!" << endl;
	else
	{
		int t = 0;
		cout << "input count of liters to fuel: "; cin >> t;
		putLiter(od, t);
	}
	system("pause");
	system("cls");
}
void printInfa(Odometr *od)
{
	gotoxy(0, 10, 7);
	if (!od)
		cout << "Parameters are not initialized!" << endl;
	else
	{
		char odometrText[7] = {};
		od->getKiloMetrage(odometrText);
		cout << odometrText << " kilometers" << "                                    " << endl;
		cout << od->fgPtr()->GetReaminingFuel() << " liters left" << "                                    " << endl;
		cout << od->leftKilometers() << " kilometrs left by liter" << "                                    " << endl;
	}

}

void goKM(Odometr *od, int km)
{
	printInfa(od);
	Sleep(500);
	for (int a(0); a < km; a++)
	{
		if (od->goOneKm())
		{
			printInfa(od);
			Sleep(500);
		}
		else
		{
			gotoxy(0, 14, 15);
			cout << "we can't go any more!" << endl;
			break;
		}
	}

}
void putLiter(Odometr *od, int l)
{
	for (int a(0); a < l; a++)
	if (od->fgPtr()->toFuel())
	{
		gotoxy(0, 10, 7);
		cout << a + 1 << " liter of fuel got to the fuel gauge                " << endl;
		Sleep(500);
	}
	else
	{
		gotoxy(0, 11, 7);
		cout << "fuel gauge is full!" << endl;
		break;
	}

}