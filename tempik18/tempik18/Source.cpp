#include <iostream>
#include <string>
#include <Windows.h>
#include "MyString.h"
#include "Container.h"
#include "MyInt.h"
#define LINE std::cout<<"-----------------------------------------------------\n";

using std::cout;
using std::cin;
using std::endl;


MyString createMyString()
{
	MyString m("in func");
	return m;
}

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

	//Container c(MyString("Перша строка."));
	
	MyInt my(5);
	cout << "my = " << my << endl;
	cout << "++my = " << ++my << endl;
	cout << "my = " << my << endl;
	LINE
	
	//MyString m("a");
	//m = createMyString();
	//cout <<"!!! змінна c: " <<  c << endl;
	
	
	return 0;
}

