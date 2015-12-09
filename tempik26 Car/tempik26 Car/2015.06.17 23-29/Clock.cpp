#include <string.h>
#include <stdlib.h>
#include "Clock.h"

using namespace std;

//	Clock(Counter hh, Counter mm, Counter ss);
Clock::Clock(int hh, int mm, int ss) : HH(0,23,hh), MM(0,59,mm), SS(0,59,ss) 
{
	
}

//	void tick();
void Clock::tick()
{
	if (SS.tick())
		if (MM.tick())
			HH.tick();
}

//	int getHH();
int Clock::getHH()
{
	return HH.getNow();
}

//	int getMM();
int Clock::getMM()
{
	return MM.getNow();
}

//	int getSS();
int Clock::getSS()
{
	return SS.getNow();
}

//bool getTime(char *dest, int len=9)
bool Clock::getTime(char *dest, int lenBuffer)
{
	const int NORMLEN = 9;
	int indexStr=0;
	if (lenBuffer>NORMLEN)
		return 0;
	else
	{
		if (HH.getNow()<10)
		{
			*dest='0';
			indexStr++;
		}
		_itoa_s(HH.getNow(),dest+indexStr,lenBuffer-indexStr,10);
		indexStr=2;
		*(dest+indexStr++) = ':';

		if (MM.getNow()<10)
		{
			*(dest+indexStr++)='0';
		}
		_itoa_s(MM.getNow(),dest+indexStr,lenBuffer-indexStr,10);
		indexStr=5;
		*(dest+indexStr++) = ':';
		
		if (SS.getNow()<10)
		{
			*(dest+indexStr++)='0';
			
		}
		_itoa_s(SS.getNow(),dest+indexStr,lenBuffer-indexStr,10);
		return 1;
	}
}

Clock::~Clock(void)
{
}
