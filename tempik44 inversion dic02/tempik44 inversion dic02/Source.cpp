#include <iostream>
#include <ctime>
#include <Windows.h>
#include <conio.h>
#include <string>
#include "Inversion.h"
#include "myString.h"
#include "vec.h"
#include <vector>
#include <algorithm>
#include <functional>
#include <fstream>


//using std::cout;
//using std::endl;
//using std::string;
//using std::vector;

using namespace std;

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

	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	/*string str1("aa");
	string str2("aabb");

	bool res = std::lexicographical_compare(str1.cbegin(), str1.cend(), str2.cbegin(), str2.cend());
	cout << res << endl;

	res = std::lexicographical_compare(str2.cbegin(), str2.cend(), str1.cbegin(), str1.cend());
	cout << res << endl; 
	
	str1 = "aa";
	str2 = "bbaa";

	bool res = std::lexicographical_compare(str1.cbegin(), str1.cend(), str2.cbegin(), str2.cend());
	cout << res << endl;

	res = std::lexicographical_compare(str2.cbegin(), str2.cend(), str1.cbegin(), str1.cend());
	cout << res << endl;

	return 0;*/
	
	Inversion in("invertDic.txt");
	
	vec<my> myVec;
	size_t countLet = 0;
	
	cout << "Do you want to find some words? (ESC - escape)\n";
	
	while (_getch()!=27)
	{
		
		my wordToFind;
		cout << "Input word to find: "; cin >> wordToFind;
		cout << "Input count leters: "; cin >> countLet;

		wordToFind.setCountCharsComp(countLet);

		
		if (in.find(wordToFind, myVec))
		{
			cout << "Finded words:\n";
			for (const auto &a : myVec)
				cout << a << endl;
		}
		else
		{
			cout << "no matches!" << endl;
		}
	
		myVec.clear();
		cout << "Do you want to continue? (ESC - escape)\n";
	}
	
	_EXEPT_END
	return 0;
}