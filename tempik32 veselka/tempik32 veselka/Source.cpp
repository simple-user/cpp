#include <Windows.h>
#include <iostream>
#include <stdexcept>
#include "Shelf.h"
#include "Book.h"
#include "Magazine.h"
#include "Audio.h"
#define br cout << endl
#define _TRY_BEGIN try {
#define _TRY_END } \
	catch (std::exception & e) \
	{	\
		cout << "Error: " << e.what() << endl; \
	} \
	catch (...) \
	{	\
	cout << "���-�� ����� �� ���!  Chrom (c)" << endl; \
	} \


using std::cout;
using std::cin;
using std::endl;


int main()
{
	_TRY_BEGIN
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	Shelf<Book> b(10);
	Shelf<Magazine> m(10);
	Shelf<Audio> s(10);

	b.push_back(Book("���� �������� �������", "������ ʳ����", "������ � ����", 6000, 1));
	b.push_back(Book("���", "�.�. �������", "�������������� �������", 4000, 1));
	m.push_back(Magazine("Play Boy", 12000, 1));
	s.push_back(Audio("Գ��� ʳ������", 32, "� ���� ������� �� �������", 50, 0));

	cout << "Books:\n";
	cout << b;
	br;
	cout << "Magazines:\n";
	cout << m;
	br;
	cout << "CD:\n";
	cout << s;
	br;
	cout << "Min price Book index: " << b.findFirstMinIndex() << endl;
	cout << b[b.findFirstMinIndex()] << endl;
	br;
	br;
	br;
	cout << "Sort by price (up):\n";
	b.sortByPrice();
	cout << "Books:\n";
	cout << b;
	br;
	br;
	cout << "Sort by price (down):\n";
	b.sortByPrice(0);
	cout << "Books:\n";
	cout << b;
	br;
	br;
	cout << "Averange books price: ";
	int av = b.averangePrice();
	cout << (av / 100) << '.' << (av % 100) << endl;

	br;
	br;
	cout << "New books:\n";
	b.showNewItems();
	_TRY_END
	return 0;

}

