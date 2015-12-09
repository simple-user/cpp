#include <iostream>
#include <array>
#include <algorithm>
#include <string>
#include <functional>
#include <fstream>
#include <Windows.h>
#include <ctime>
#include <iomanip>
#include <cstdio>
#include <cassert>

using namespace std;


void exitFunc()
{
	cout << "This is exit!" << endl;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	time_t curT = time(nullptr); 

	cout << "curT: " << curT << endl;

	tm tmTime1;
	tm tmTime2;
	gmtime_s(&tmTime1, &curT); //  робить з time_t -> структуру tm (в даному випадку результат запишеться в  tmTime)
	localtime_s(&tmTime2, &curT); // схожа тєма з попередньою, треба протестити на вивод
	
	cout << setw(18) << "tm_hour: " << setw(5) << tmTime1.tm_hour << setw(5) << tmTime2.tm_hour << endl;
	cout << setw(18) << "tm_isdst: " << setw(5) << tmTime1.tm_isdst << setw(5) << tmTime2.tm_isdst << endl;
	cout << setw(18) << "tm_mday: " << setw(5) << tmTime1.tm_mday << setw(5) << tmTime2.tm_mday << endl;
	cout << setw(18) << "tm_min: " << setw(5) << tmTime1.tm_min << setw(5) << tmTime2.tm_min << endl;
	cout << setw(18) << "tm_mon: " << setw(5) << tmTime1.tm_mon << setw(5) << tmTime2.tm_mon << endl;
	cout << setw(18) << "tm_sec: " << setw(5) << tmTime1.tm_sec << setw(5) << tmTime2.tm_sec << endl;
	cout << setw(18) << "tm_wday: " << setw(5) << tmTime1.tm_wday << setw(5) << tmTime2.tm_wday << endl;
	cout << setw(18) << "tm_yday: " << setw(5) << tmTime1.tm_yday << setw(5) << tmTime2.tm_yday << endl;
	cout << setw(18) << "tm_year: " << setw(5) << tmTime1.tm_year << setw(5) << tmTime2.tm_year << endl;
	
	
	char str0[80];
	char str1[80];
	char str2[80];

	ctime_s(str0, 80, &curT);  // запоанює str0 текстом про дату (з time_t)
	asctime_s(str1, &tmTime1);  // все те саме (той самий текст), тільки з сткуктури tm
	asctime_s(str2, &tmTime2);  // тестим localtime
	cout << "ctime_s: " << str0 << endl;
	cout << "gmtime_s:" << str1 << endl;
	cout << "localtime_s:" << str1 << endl;

	time_t curT2 = mktime(&tmTime1);
	cout << "curt2 (tmTime1): " << curT2 << endl;
	curT2 = mktime(&tmTime2);
	cout << "curt2 (tmTime2): " << curT2 << endl;

	lconv *localeConv;  // структура про всяку геополітичну інфу
	localeConv = localeconv();  // фенкція яка вертає дану структуру :)
	cout << "localeConv->decimal_point - \"" << localeConv->decimal_point << "\""<< endl;

	char *str3 = new char[800];
	strcpy_s(str3,800,setlocale(LC_ALL, nullptr));
	cout << "setlocale: " << str3 << endl;
	
	strftime(str3, 79, "%d.%m.%y всього пройшло днів з початку року - %j", &tmTime2);
	cout << "strftime: " <<  str3 <<endl;
	
	
	int a = 4;
	// assert(a!=5 ? false : true);
	// _ASSERTE(5);
	// _ASSERT(5);
	
	atexit(exitFunc); // реєстрація функції яка виконуєтсья при виході
	size_t t = 0;
	getenv_s(&t, str3, 800, "str3");
	cout << "getenv: " << str3 << endl;

	wchar_t wch = 'an';

	cout << "wch: " << wch << endl;

	cout << "-----------------------------------\n\n";

	ios::app;
	ios_base::app;

	

	return 0;
}