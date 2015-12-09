#include <Windows.h>
#include <string>
#include <vector>
#include <iostream>
#include <exception>
#include <conio.h>
#include <algorithm>
#include "Ammo.h"
#include "Magazine.h"
#include "AK.h"


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

	

	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	

	
	Ammo::numberStar = 1001;

	
	Magazine mag1;
	cout << "Споряджаємо патронами магазин 1 (30 штук):" << endl;
	for (size_t a = 0; a < 30; ++a)
	{
		mag1.push(new Ammo());
		cout << "засандалив патрон: " << mag1.top()->getNumber() << endl;
	}
	br;


	Magazine mag2;
	cout << "Споряджаємо патронами магазин 2 (15 штук):" << endl;
	for (size_t a = 0; a < 15; ++a)
	{
		mag2.push(new Ammo());
		cout << "засандалив патрон: " << mag2.top()->getNumber() << endl;
	}
	br;


	AK ak(&mag1);

	AK::Res res;

	cout << "Вистріл одиночним: " << endl;
	if (ak.pif(res))
		cout << "Вистрілив одиночним. Патрон №" << res.num << " результат: " << (res.res ? "влучив" : "промазав") << endl;
	else
		cout << "Осічка!";
	br;

	cout << "Вистріл чергою 10 патронів: " << endl;
	
	std::vector<AK::Res> vecRes;
	if (ak.tratata(10, vecRes))
	{
		cout << "Вистрілив чергою. Результати:\n";
		std::for_each(vecRes.cbegin(), vecRes.cend(), [](const AK::Res &r) {cout << "Патрон №" << r.num << " результат: " << (r.res ? "влучив" : "промазав") << endl; });
	}
	else
		cout << "Осічка!";
	vecRes.clear();
	br;

	cout << "Недозяряджаючи. Вистріл чергою 100 патронів: " << endl;

	if (ak.tratata(100, vecRes))
	{
		cout << "Вистрілив чергою. Результати:\n";
		std::for_each(vecRes.cbegin(), vecRes.cend(), [](const AK::Res &r) {cout << "Патрон №" << r.num << " результат: " << (r.res ? "влучив" : "промазав") << endl; });
	}
	else
		cout << "Осічка!";
	vecRes.clear();
	br;

	cout << "Вистріл одиночним: " << endl;
	if (ak.pif(res))
		cout << "Вистрілив одиночним. Патрон №" << res.num << " результат: " << (res.res ? "влучив" : "промазав") << endl;
	else
		cout << "Осічка!";
	br;

	if (ak.ejectMag())
		cout << "Вийняли магазин 1" << endl;
	else
		cout << "Магазин заклинило 1" << endl;
	br;

	if (ak.insertMag(&mag2))
		cout << "Вставили магазин 2" << endl;
	else
		cout << "Магазин 2 не вставляється :(" << endl;
	br;

	vecRes.clear();
	cout << "Вистріл чергою всі патрони (100): " << endl;
	if (ak.tratata(100, vecRes))
	{
		cout << "Вистрілив чергою. Результати:\n";
		std::for_each(vecRes.cbegin(), vecRes.cend(), [](const AK::Res &r) {cout << "Патрон №" << r.num << " результат: " << (r.res ? "влучив" : "промазав") << endl; });
	}
	else
		cout << "Осічка!";
	vecRes.clear();
	cout << endl;


	_EXEPT_END
	return 0;
}



