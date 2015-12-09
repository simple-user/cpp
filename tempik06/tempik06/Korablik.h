#ifndef __KORABLIK__
#define __KORABLIK__

#include <vector>
#include "Pole.h"
using namespace std;

class Korablik
{
private:
	void manual_create();
	void manual_create2();
	void auto_create();
	bool is_good_place(int x, int y);
	void max_min_paluba(int &xmin, int &ymin, int &xmax, int &ymax);
public:
	void about_me();
	Pole &pole;
	int count_pal;
	int count_pal_alive;
	bool killed;
	struct Paluba
	{
		int x_pal;
		int y_pal;
		bool killed_paluba;
	};
	vector<Paluba> palubi;
	Korablik(int p, Pole& pole, bool auto_creation);
	~Korablik();
};

#endif // !__KORABLIK__
