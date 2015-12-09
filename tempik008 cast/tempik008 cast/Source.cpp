#include <iostream>
#include <array>
#include <algorithm>
#include <string>
#include <functional>
#include <fstream>
#include <Windows.h>

using namespace std;


class A
{
public:
	virtual ~A() {};
};

class B : public A
{

};


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	A a;
	A *pa = &a;
	
	B b;
	B *pb = &b;

	cout << typeid(pa).name() << "pa = " << pa << endl;
	
	// вказівник на підрядник клас приводимо до вказівника базового класу
	// успєх. впринципі можна і звичайним тут скористатись (A*)bp
	pa = dynamic_cast<A*> (pb);
	cout << typeid(pa).name() << "pa = " << pa << endl;

	pa = &a;
	pb = &b;

	cout << typeid(pb).name() << "pb = " << pb << endl;
	
	// по перше якщо приводимо базовий к підрядному - базовий має бути поліморфним
	// по друге:
	// якщо pa (базовий) вже ссилається на підрядний - то успєх
	// якщо pa (базовий) ссилається на базовий- то у вказівник підрядного не приведе. 
	   // тут для вказівника - nullptr
	   // для ссилки виключена ситуація (bad_cast)

	pb = dynamic_cast<B*> (pa);
	cout << typeid(pb).name() << "pb = " << pb << endl;

	cout << "\n\n--------------const_cast--------------------------\n";
	

	{
		const int a = 4;
		const int *pa = &a;
		cout << "*pa до const_cast:" << *pa << endl;
		cout << "pa до const_cast:" << pa << endl;
		
		int * pb = const_cast<int*>(pa);
		*pb = 40;
		
		*const_cast<int*>(pa) = 50;

		cout << "*pa після const_cast:" << *pa << endl;
		cout << "pa після const_cast:" << pa << endl;
		cout << "a після const_cast:" << a << endl;

	}
	{
		int a = 20;
		cout << "a до const_cast:" << a << endl;
		[](const int &i) {const_cast<int&>(i) = 10; cout << "temp a= " << i << endl; }(a);
		cout << "a після const_cast:" << a << endl;

	}

	cout << "\n\n--------------reinterpret_cast- хз для чго він :)-------------------------\n";
	{
		int a = 10;
		char *str = "Hrlllo";
		a = reinterpret_cast<int>(str);
		cout << "a= " << a << endl;
		a = 10;
		str = reinterpret_cast<char*>(a);
		cout << "str = " << str << endl;
	}



	return 0;
}