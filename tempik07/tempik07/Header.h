#ifndef __HEADER__
#define __HEADER__

#include <string>

#include "Pole.h"
#include "Korablik.h"

using namespace std;

enum Buttons { UP=72, DOWN=80,LEFT=75,RIGHT=77,ESC=27,SPACE=32,ENTER=13};

void operator>>(istream &is, Buttons &b);

void gotoxy(int x, int y);
void gotoxy(int x, int y, int color);
void gotoxy(int x, int y, int color, char ch);
void gotoxy(int x, int y, int colortext, int colorbackground, char ch);
void gotoxy(int x1, int y1, int x2, int y2, int color, char ch);
void gotoxy(int x, int y, int color, string str);

bool move_my(vector<Korablik> &korabli, Pole & pole, int &turn);
bool move_my2(vector<Korablik> &korabli, Pole & pole, int &turn);
bool move_comp(vector<Korablik> &korabli, Pole &pole, int &turn);
bool move_maker(vector<Korablik> &korabli, Pole &pole, int &turn);
void killed_ship(Korablik & korablik, Pole &pole);
bool find_free_around_happy(Pole &p);

 #endif // !__HEADER__








