#include <string>
#include <vector>
#include <iostream>
#include <conio.h>

#include "Header.h"
#include "Korablik.h"
#include "Pole.h"

using namespace std;

int main()
{

	Pole p_comp(40, 0, 0);
	p_comp.first_draw();

	Korablik *k1;
	gotoxy(0, 0);
	{
		Korablik k(4, p_comp, 1);
		k1 = new Korablik(k);
		cout << "K ";
		k.about_me();
		cout << "k1 ";
		k1->about_me();
	}
	cout << "k1(after) ";
	k1->about_me();
	return 0;

	vector<Korablik> korabli_comp;
	for (int a(1); a <= 4; a++)
	{
		for (int b(1); b <= a; b++)
		{
			Korablik k(5 - a, p_comp, 1);
			korabli_comp.push_back(k);
		}
	}
	p_comp.show_action();
	
	gotoxy(0, 0);

	
	/*
	int t = 1;
	for (auto a : korabli_comp)
	{
		cout << t << ") ";
		a.about_me();
		t++;
	}
	*/
	/* Pole p_my(0, 0, 1);
	p_my.first_draw();

	vector<Korablik> korabli_my;
	
	for (int a(1); a <= 4; a++)
	{
		for (int b(1); b <= a; b++)
		{
			Korablik k(5-a, p_my, 0);
			korabli_my.push_back(k);
		}
	}
	
	*/
	


}

