#include <string.h>
#include <stdlib.h>
#include "Timer.h"

using namespace std;

//	Timer(Counter hh, Counter mm, Counter ss);
Timer::Timer(int hh, int mm, int ss) : HH(23,0,hh), MM(59,0,mm), SS(59,0,ss) 
{
	
}

//	void tick();
void Timer::tick()
{
	if (SS.tick())
		if (MM.tick())
			HH.tick();
}

//	int getHH();
int Timer::getHH()
{
	return HH.getNow();
}

//	int getMM();
int Timer::getMM()
{
	return MM.getNow();
}

//	int getSS();
int Timer::getSS()
{
	return SS.getNow();
}

//bool getTime(char *dest, int len=9)
bool Timer::getTime(char *dest, int lenBuffer)
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

