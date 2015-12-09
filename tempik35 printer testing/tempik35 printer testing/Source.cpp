#include <Windows.h>
#include <string>
#include <iostream>
#include <exception>
#include <conio.h>
#include <queue>
#include <thread>
#include <mutex>
#include "Menu.h"
#include "Document.h"
#include "Printer.h"
#include "Tr.h"

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

int main()
{

	_EXEPT_START
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	std::mutex mut;
	std::priority_queue<Document> spooler;
	Printer pr(spooler, mut);
	Menu m(mut);
	int nomDoc = 0;

	for (int a(10); a < 25; a++)
	{
		gtoxy(39, a, 7);
		cout << '|';
	}

	// std::thread thr1(tr2_add_queue, std::ref(spooler));
	std::thread thr2(tr1_printer, std::ref(pr));
	std::thread thr3(tr2_add_queue_menu, std::ref(m), std::ref(spooler), std::ref(nomDoc), std::ref(mut));

	// thr1.join();
	thr2.join();
	thr3.join();



	system("cls");
	_EXEPT_END
	return 0;
}



