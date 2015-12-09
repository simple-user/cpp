#pragma once
#include "Counter.h"
class Clock
{
private:
	Counter HH;
	Counter MM;
	Counter SS;
public:
Clock(int hh, int mm, int ss);
//	Clock(Counter hh, Counter mm, Counter ss);
	void tick();
	int getHH();
	int getMM();
	int getSS();
	bool getTime(char *dest, int lenBuffer);
	~Clock(void);
};

