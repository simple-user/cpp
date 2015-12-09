#include <iostream>
#include <Windows.h>
#include "Counter.h"
#include "Clock.h"
#include "Timer.h"
#include <iomanip>

#define L cout<<"_______________________________________________\n";

using namespace std;

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Clock c1(0,0,0);
	Timer t1(0,2,0);

	char myTime[9];
	myTime[8]=0;

	while(1)
	{
		c1.getTime(myTime,9);
		cout << myTime << endl;
		t1.getTime(myTime,9);
		cout << myTime;
		
		c1.tick();
		t1.tick();
		Sleep(100);
		system("cls");
	}

	return 0;

	

}