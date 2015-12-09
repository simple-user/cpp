#ifndef __HEADER__
#define __HEADER__

#include <string>

#include "Pole.h"
#include "Korablik.h"

using namespace std;

void gotoxy(int x, int y);
void gotoxy(int x, int y, int color);
void gotoxy(int x, int y, int color, char ch);
void gotoxy(int x1, int y1, int x2, int y2, int color, char ch);
void gotoxy(int x, int y, int color, string str);

bool move_my(vector<Korablik> &korabli, Pole & pole, int &turn);
bool move_comp(vector<Korablik> &korabli, Pole &pole, int &turn);
bool move_maker(vector<Korablik> &korabli, Pole &pole, int &turn, int x, int y);
void killed_ship(Korablik & korablik, Pole &pole);

 #endif // !__HEADER__








