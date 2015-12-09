#include <iostream>
#include <string>
#include <Windows.h>
#include "MyString.h"
#include "Container.h"
#define LINE std::cout<<"-----------------------------------------------------\n";

using std::cout;
using std::cin;
using std::endl;


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	//MyString s1("Перша строка.");
	//cout << s1 << endl;
	//MyString s3("Друга строка.");
	//MyString s4;
	//s4 = s1 + s3;
	//cout << s4 << endl;
	//cin >> s1;
	//cout << s1 << endl;

	MyString s; s = "asd";

	LINE
	
	
	return 0;
}

