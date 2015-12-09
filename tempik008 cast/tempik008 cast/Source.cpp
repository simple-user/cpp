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
	
	// �������� �� �������� ���� ��������� �� ��������� �������� �����
	// ����. �������� ����� � ��������� ��� ������������ (A*)bp
	pa = dynamic_cast<A*> (pb);
	cout << typeid(pa).name() << "pa = " << pa << endl;

	pa = &a;
	pb = &b;

	cout << typeid(pb).name() << "pb = " << pb << endl;
	
	// �� ����� ���� ��������� ������� � ��������� - ������� �� ���� ����������
	// �� �����:
	// ���� pa (�������) ��� ��������� �� �������� - �� ����
	// ���� pa (�������) ��������� �� �������- �� � �������� ��������� �� �������. 
	   // ��� ��� ��������� - nullptr
	   // ��� ������ ��������� �������� (bad_cast)

	pb = dynamic_cast<B*> (pa);
	cout << typeid(pb).name() << "pb = " << pb << endl;

	cout << "\n\n--------------const_cast--------------------------\n";
	

	{
		const int a = 4;
		const int *pa = &a;
		cout << "*pa �� const_cast:" << *pa << endl;
		cout << "pa �� const_cast:" << pa << endl;
		
		int * pb = const_cast<int*>(pa);
		*pb = 40;
		
		*const_cast<int*>(pa) = 50;

		cout << "*pa ���� const_cast:" << *pa << endl;
		cout << "pa ���� const_cast:" << pa << endl;
		cout << "a ���� const_cast:" << a << endl;

	}
	{
		int a = 20;
		cout << "a �� const_cast:" << a << endl;
		[](const int &i) {const_cast<int&>(i) = 10; cout << "temp a= " << i << endl; }(a);
		cout << "a ���� const_cast:" << a << endl;

	}

	cout << "\n\n--------------reinterpret_cast- �� ��� ��� �� :)-------------------------\n";
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