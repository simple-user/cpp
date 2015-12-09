#ifndef __POLE__
#define __POLE__

#include <array>
#include "Kletka.h"
using namespace std;

class Pole
{
private:
	void show_my();

public:
	const int COUNT_K;
	int count_k_op; // кількість відкритих клітинок
	const int COUNT_K_PAL; // 1*4 + 3*2 + 2*3 + 4*1 =20
	int count_k_pal_op; // кількість відкритих клітинок з палубами
	// якщо count_k_pal_op== count_k_pal =>win
	int x_move; //зміщення поля (на екрані)
	int y_move;
	bool isMy;
	array<array<Kletka, 10>, 10> arr_k;

	Pole(int x, int y, bool my);

	void first_draw();
	void show_action();

};

#endif // __POLE__