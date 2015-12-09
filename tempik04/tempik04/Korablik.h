#ifndef __KORABLIK__
#define __KORABLIK__

#include <vector>
#include "Pole.h"
using namespace std;

class Korablik
{
private:
	void manual_create();
	void auto_create();
	bool is_good_place(int x, int y);
public:
	void about_me();
	Pole &pole;
	int count_pal;
	bool killed;
	struct Paluba
	{
		int x_pal;
		int y_pal;
		bool isPal;
	};
	vector<Paluba> palubi;
	Korablik(int p, Pole& pole, bool auto_creation);
	~Korablik();
};

#endif // !__KORABLIK__
