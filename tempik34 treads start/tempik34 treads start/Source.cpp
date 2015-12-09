#include <Windows.h>
#include <string>
#include <iostream>
#include <exception>
#include <conio.h>
#include <thread>



#define br cout << endl
#define _EXEPT_START try { 
#define _EXEPT_END } \
	catch (std::exception &e) { \
	std::cout << "Error: " << e.what(); \
	} \
	catch (...) { \
	std::cout << "Что-то пошло не так... Chrome.(c) "; \
	} 

using std::cout;
using std::endl;
using std::string;


void f1()
{
	for (int a(0); a < 10; a++)
	{
		std::cout << "f1 - " << a << std::endl;
		Sleep(100);
	}
}
void f2()
{
	for (int a(0); a < 10; a++)
	{
		std::cout << "\t\tf2 - " << a << std::endl;
		Sleep(200);
	}
}


int main()
{

	_EXEPT_START
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	try
	{

		std::thread thr1(f1);
		std::thread thr2(f2);
		thr1.join();
		thr1.detach();

		

		// thr2.detach();
	}
	catch (...)
	{
		std::cout << "opa!" << endl;
	}
	

	_EXEPT_END
	return 0;
}







