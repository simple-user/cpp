#include <iostream>
using namespace std;
#include <iomanip>
#include <ctime>
#include "Drob.h"



int main()
{
	setlocale(0, "");
	
	int a, b;
	double d;
	/*
	cout << "Creating object Drob from one integer number \n";
	cout << "Imput one integer number: ";
	cin >> a;
	Drob d1(a);
	cout << "d1 = " << d1;
	cout << "\n\n";

	cout << "Creating object Drob from two integer number \n";
	cout << "Imput two integer number: ";
	cin >> a >> b;
	Drob d2(a, b);
	cout << "d2 = " << d2;
	cout << "\n\n";

	cout << "Creating object Drob from two integer number (one more for testing...) \n";
	cout << "Imput two integer number: ";
	cin >> a >> b;
	Drob d3(a, b);
	cout << "d3 = " << d3;
	cout << "\n\n";

	cout << "Creating object Drob from one double number (5 digits after coma)\n";
	cout << "Imput one double number: ";
	cin >> d;
	Drob d4(d);
	cout << "d4 = " << d4;
	cout << "\n\n";

	const int NUM = 5;
	cout << "NUM = " << NUM << endl;

	cout << "d2 + d3 = " << d2 << " + " << d3 << " = " << d2 + d3 << endl;
	cout << "d2 + NUM = " << d2 << " + " << NUM << " = " << d2 + NUM << endl;
	cout << "NUM + d3 = " << NUM << " + " << d3 << " = " << NUM + d3 << endl;
	cout << endl;

	cout << "d2 - d3 = " << d2 << " - " << d3 << " = " << d2 - d3 << endl;
	cout << "d2 - NUM = " << d2 << " - " << NUM << " = " << d2 - NUM << endl;
	cout << "NUM - d3 = " << NUM << " - " << d3 << " = " << NUM - d3 << endl;
	cout << endl;

	cout << "d2 * d3 = " << d2 << " * " << d3 << " = " << d2 * d3 << endl;
	cout << "d2 * NUM = " << d2 << " * " << NUM << " = " << d2 * NUM << endl;
	cout << "NUM * d3 = " << NUM << " * " << d3 << " = " << NUM * d3 << endl;
	cout << endl;

	cout << "d2 / d3 = " << d2 << " / " << d3 << " = " << d2 / d3 << endl;
	cout << "d2 / NUM = " << d2 << " / " << NUM << " = " << d2 / NUM << endl;
	cout << "NUM / d3 = " << NUM << " / " << d3 << " = " << NUM / d3 << endl;
	cout << endl;

	cout << "d2 = " << d2 << endl;
	cout << "d2++ = " << d2++ << endl;
	cout << "d2 = " << d2 << endl;
	cout << "++d2 = " << ++d2 << endl;
	cout << endl;
	cout << "(int)d2 = " << (int)d2 << endl;
	cout << "(double)d2 = " << (double)d2 << endl;
	*/
	cout << "comparing:" << endl;
	double asd;
	cout << "double: 10. == 20./2 : " << ((20./3)+(20./3))/2 << endl;
	cout << "drob: 20./3 = " << Drob(20) / 3 +1 << endl;
	
	cout << endl;
	
	double dnum1 = 1;
	const double dnum2 = 0.01;
	const int COUNT = 200;
	Drob drob1 = 1;
	const Drob drob2 = 0.01;

	for (int a(0); a < COUNT; a++)
	{
		//if (a % 10000000 ==0)
		//	cout << a << '\t';
		cout << "dnum1 + dnum2 = " << dnum1 << " + " << dnum2 << endl;
		cout << "drob1 + drob2 = " << drob1 << " + " << drob2 << endl;

		dnum1 = dnum1 + dnum2;
		drob1 = drob1 + drob2;

		cout << "dnum1 = " << dnum1 << endl;
		cout << "drob1 = " << drob1 << endl;
		cout << "\n";
	}
	cout << "result: " << endl;
	cout << "dnum1 = " << dnum1 << endl;
	cout << "drob1 = " << drob1 << endl;
	cout << "-----------------------------------\n";
	for (int a(0); a < COUNT; a++)
	{
		//if (a % 10000000 ==0)
		//	cout << a << '\t';
		cout << "dnum1 - dnum2 = " << dnum1 << " - " << dnum2 << endl;
		cout << "drob1 - drob2 = " << drob1 << " - " << drob2 << endl;
		
		dnum1 = dnum1 - dnum2;
		drob1 = drob1 - drob2;

		cout << "dnum1 = " << dnum1 << endl;
		cout << "drob1 = " << drob1 << endl;
		cout << "\n";
	}
	cout << "result: " << endl;
	cout << "dnum1 = " << dnum1 << endl;
	cout << "drob1 = " << drob1 << endl;



	
	return 0;
}
