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
	
	setlocale(0, "");
	Pole p_my(0, 2, 1);
	gotoxy(p_my.x_move, 0), cout << "Pole My";
	p_my.first_draw();

	vector<Korablik> korabli_my;

	for (int a(1); a <= 4; a++)
	{
		for (int b(1); b <= a; b++)
		{
			Korablik k(5 - a, p_my, 0);
			korabli_my.push_back(k);
		}
	}
	gotoxy(0, 15, 79, 16, 7, ' ');
	//p_my.show_action(); 
	
	Sleep(1000);

	
	Pole p_comp(25, 2, 0);
	gotoxy(p_comp.x_move, 0), cout << "Pole Comp";
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

	gotoxy(0, 15, 79, 15, 7, ' ');
	gotoxy(p_my.x_move - 3, 15), cout << "Залишилось палуб: " << p_my.count_closed_pal << "  ";
	gotoxy(p_comp.x_move - 3, 15), cout << "Залишилось палуб: " << p_comp.count_closed_pal << "  ";

	while (!end_of_game)
	{
		if (my_turn)
			end_of_game = move_my2(korabli_comp, p_comp, my_turn);
		else
			end_of_game = move_comp(korabli_my, p_my, my_turn);

		my_turn = my_turn*(-1) + 1;
	}

	gotoxy(0, 21, 7, "Для виходу: ESC");
	while (_getch() != ESC);

	
	gotoxy(0,24);
	return 0;
}

