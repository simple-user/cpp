#include <iostream>
#include <iomanip>
#include <ctime>
#include "Date.h"

using namespace std;


class A
{
public:
	A(int i) : I(i) { cout << "c-tor A: " << I << endl; }
	void f() const
	{
		cout << "i= " << I << endl;
	}

	A & operator=(const A& a)
	{
		cout << "operator = (" << I << " = " << a.I << ")" << endl;
		I = a.I;
		return *this;
	}

	~A(){ cout << "d-tor A: " << I << endl; }

private:
	int I;
};

int main()
{
	setlocale(0, "");
	
	A a1(5); 
	a1.f();

	a1 = 10;
	a1.f();


	/*Date *d1 = date_init("10", "08", "2003");
	Date *d2 = date_init2("10", "08", "2003");
	

	cout << "d1: ", print_date(d1); cout << endl;
	cout << "d1: ", print_date(d1, 1); cout << endl;
	cout << "d2: ", print_date(d2); cout << endl;
	cout << "d2: ", print_date(d2, 1); cout << endl;
	*/




	return 0;
}
