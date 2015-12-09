#include <string>
#include <vector>
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <ctime>

#include "Header.h"
#include "Korablik.h"
#include "Pole.h"

using namespace std;

int main()
{


	gotoxy(0, 0), cout << "Pole My";
	Pole p_my(0, 2, 1);
	p_my.first_draw();

	vector<Korablik> korabli_my;

	for (int a(1); a <= 4; a++)
	{
		for (int b(1); b <= a; b++)
		{
			Korablik k(5 - a, p_my, 1);
			korabli_my.push_back(k);
		}
	}
	
	p_my.show_action(); 
	
	Sleep(1000);

	
	gotoxy(20, 0), cout << "Pole Comp";
	Pole p_comp(20, 2, 0);
	p_comp.first_draw();

	vector<Korablik> korabli_comp;
	for (int a(1); a <= 4; a++)
	{
		for (int b(1); b <= a; b++)
		{
			Korablik k(5 - a, p_comp, 1);
			korabli_comp.push_back(k);
		}
	}
	// p_comp.show_action();
	
	
	srand(unsigned(time(0)));
	int my_turn = rand() % 2;
	bool end_of_game = 0;

	/*
	for (auto &a : korabli_comp)
	{
		a.about_me();
	}
	return 0;
	*/

	while (!end_of_game)
	{
		if (my_turn)
			end_of_game = move_my(korabli_comp, p_comp, my_turn);
		else
			end_of_game = move_comp(korabli_my, p_my, my_turn);

		my_turn = my_turn*(-1) + 1;
	}

	
	
	gotoxy(0,24);
	return 0;
}

