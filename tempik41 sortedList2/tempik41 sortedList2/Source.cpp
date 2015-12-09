#include <iostream>
#include <ctime>
#include <Windows.h>
#include <conio.h>
#include "sortedList.h"
#include <string>


using std::cout;
using std::endl;
using std::string;

#define br cout << endl

#define _EXEPT_START try {
#define _EXEPT_END } \
	catch (std::exception &e) { \
	std::cout << "Error: " << e.what(); \
} \
catch (...) { \
	std::cout << "„то-то пошло не так... Chrome.(c) "; \
}


struct myPair
{
	int n;
	string s;
	myPair(int n, const string &s) : n(n), s(s){};
};

bool operator==(const myPair &m1, const myPair &m2)
{
	return m1.n == m2.n;
}

bool operator<=(const myPair &m1, const myPair &m2)
{
	return m1.n <= m2.n;
}

std::ostream & operator<<(std::ostream &o, const myPair &m)
{
	o << m.s << " = " << m.n << endl;
	return o;
}


int main() 
{
	_EXEPT_START

	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	
	cout << "\n______create s1<int>, s2<int>______________\n";
	sortedList<int> s1;
	cout << "s1: ", s1.show();
	
	cout << "\n______insert to s1______________\n";
	s1.insert(22);
	s1.insert(212);
	s1.insert(242);
	s1.insert(122);
	cout << "s1: ", s1.show();
	
	cout << "\n______s1.remove(3)______________\n";
	s1.remove(3);
	cout << "s1: ", s1.show();
	
	cout << "\n______s1.remove(122)______________\n";
	s1.remove(122);
	cout << "s1: ", s1.show();
	
	cout << "\n______get_size______________\n";
	cout << "s1: " << s1.getSize() << endl;
	
	cout << "\n______s2(s1)______________\n";
	sortedList<int>s2(s1);
	cout << "s1: ", s1.show();
	cout << "s2: ", s2.show();

	cout << "\n______s1 insert 3______________\n";
	s1.insert(3);
	cout << "s1: ", s1.show();
	cout << "s2: ", s2.show();

	cout << "\n______s2=s1______________\n";
	s2=s1;
	cout << "s1: ", s1.show();
	cout << "s2: ", s2.show();

	cout << "\n______s2 removeAt 2______________\n";
	s2.removeAt(2);
	cout << "s1: ", s1.show();
	cout << "s2: ", s2.show();

	cout << "\n______s2 first last []______________\n";
	cout << "s2 first: " << s2.first() << endl;
	cout << "s2 last: " << s2.last() << endl;
	cout << "s2 [0]: " << s2[0] << endl;
	cout << "s2 [1]: " << s2[1] << endl;
	cout << "s2 [2]: " << s2[2] << endl;
	

	cout << "\n______s2 removeFirst removeLast ______________\n";
	s2.removeFirst();
	s2.removeLast();
	cout << "s2 first: " << s2.first() << endl;
	cout << "s2 last: " << s2.last() << endl;
	try
	{
		cout << "s2 [0]: " << s2[0] << endl;
		cout << "s2 [1]: " << s2[1] << endl;
		cout << "s2 [2]: " << s2[2] << endl;
	}
	catch (std::exception &e)
	{
		cout << e.what() << endl;
	}

	cout << "\n______s1 []______________\n";
	cout << "s1: ", s1.show();
	
	cout << "\ns1[1]=10: ", s1[1] = 10; 
	cout << "\ns1: ", s1.show();
	
	cout << "\ns1[1]=s1[0]=500: ", s1[1] = s1[0] = 500; 
	cout << "\ns1: ", s1.show();
	
	cout << "\n(s1[1]=999) = s1[2]: ", (s1[1] = 999) = s1[2]; 
	cout << "\ns1: ", s1.show();

	
	cout << "\n______mp1<myPair>______________\n";
	sortedList<myPair> mp1;
	cout << "mp1: ", mp1.show();

	cout << "\n______mp1.insert(myPair(10, \"це дес€ть\"));______________\n";
	mp1.insert(myPair(10, "це дес€ть"));
	cout << "mp1:\n ", mp1.show();
	
	cout << "\n______mp1.insert(myPair(20, \"це двадц€ть!\"));______________\n";
	mp1.insert(myPair(20, "це двадц€ть!"));
	cout << "mp1:\n ", mp1.show();

	cout << "\n______mp1.emplace(15, \"а це п\'€тнадц€ть!\");______________\n";
	mp1.emplace(15, "а це п\'€тнадц€ть!");  // ≥-хо-хо ≥ бутилка рому! :)
	cout << "mp1:\n ", mp1.show();

	_EXEPT_END
	return 0;
}
