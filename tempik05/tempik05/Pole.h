#ifndef __POLE__
#define __POLE__

#include <array>
#include <vector>
#include "Kletka.h"


using namespace std;

class Pole
{
private:

public:
	// const int COUNT_K;
	int count_�losed; // ������� �������� ������� =100
	//const int COUNT_K_PAL; // 1*4 + 3*2 + 2*3 + 4*1 =20
	int count_closed_pal; // ������� �������� ������� � �������� =20
	// ���� count_k_pal_op== count_k_pal =>win
	int x_move; //������� ���� (�� �����)
	int y_move;
	int x_at;
	int y_at;
	bool isMy;
	array<array<Kletka, 10>, 10> arr_k;

	Pole(int x, int y, bool my);

	void first_draw();
	void show_action();
	

};

#endif // __POLE__