#include <iostream>
#include <ctime>
#include <Windows.h>
#include <conio.h>
#include "sortedList.h"

using std::cout;
using std::endl;

#define br cout << endl

#define _EXEPT_START try {
#define _EXEPT_END } \
	catch (std::exception &e) { \
	std::cout << "Error: " << e.what(); \
} \
catch (...) { \
	std::cout << "Что-то пошло не так... Chrome.(c) "; \
}



int main() 
{
	_EXEPT_START


	sortedList<int> s1;
	
	cout << "Blank sList: "; 
	s1.show();
	cout << "\n\n";

	s1.insert(40);
	s1.insert(33);
	s1.insert(100);

	cout << "s1 after insert: ";
	s1.show();
	cout << "\n\n";

	s1.remove(3);
	cout << "s1 after del 3: ";
	s1.show();
	cout << "\n\n";

	s1.remove(40);
	cout << "s1 after del 40: ";
	s1.show();
	cout << "\n\n";

	sortedList<int> s2(s1);
	cout << "s2(s1): ";	s2.show();
	cout << "s2 size: " << s2.getSize() << endl;
	cout << "\n\n";

	s1.insert(3);
	cout << "s1 after insert 3: ";
	s1.show();

	cout << "s2(s1): "; s2.show();
	cout << "s2 size: " << s2.getSize() << endl;
	cout << "\n\n";

	cout << "before s2 = s1:\n";
	cout << "s2: ";	s2.show();
	cout << "s1: ";	s1.show();

	cout << "after s2 = s1:\n";	s2 = s1;
	cout << "s2: ";	s2.show();
	cout << "s1: ";	s1.show();
	
	cout << "s1 del 100:\n";	s2 = s1;
	s1.remove(100);
	cout << "s2: ";	s2.show();
	cout << "s1: ";	s1.show();
	cout << "\n\n";
	
	cout << "s2 remove at 0:\n";
	s2.removeAt(0);
	cout << "s2: ";	s2.show();
	cout << "s1: ";	s1.show();
	cout << "\n\n";

	cout << "s2 remove at 1:\n";
	s2.removeAt(1);
	cout << "s2: ";	s2.show();
	cout << "s1: ";	s1.show();
	cout << "\n\n";

	//cout << "s2 remove at 1:\n";
	//s2.removeAt(1);
	//cout << "s2: ";	s2.show();
	//cout << "s1: ";	s1.show();
	//cout << "\n\n";

	s2.insert(10);
	cout << "s2: ";	s2.show();
	cout << "s2 first element: " << s2.first() << endl;
	cout << "s2 [0]: " << s2[0] << endl;

	
	cout << "s1: ";	s1.show();
	cout << "s2: ";	s2.show();

	(s2[0] = 999 )= s1[0];
	cout << "s1: ";	s1.show();
	cout << "s2: ";	s2.show();


	_EXEPT_END
	return 0;
}
