#include <iostream>
#include <string>
#include <algorithm>
#include <typeinfo>
#include <functional>


using namespace std;

class A
{
public:
	// A(int a) : i(a) {}
	void operator() (int a)
	{
		cout << "a in A = " << a << endl;
		// cout << "i from main = " << i << endl;
	}

private:
	int i;

};


void f(int z)
{
	cout << " in function f = " << z << endl;
}

void main()
{
	string str = "asd";
	int i = 4;
	int arr[1] = { 10 };

	
	cout << "for_each with functor_________\n";
	std::for_each(std::begin(arr), std::end(arr), A());
	cout << "\n\n";
	
	cout << "for_each with unction____\n";
	std::for_each(std::begin(arr), std::end(arr), f);
	cout << "\n\n";


	cout << "for_each _________\n";
	std::for_each(std::begin(arr), std::end(arr), [](int i) { std::cout << "in []"; });
	cout << "\n\n";

	cout << "prosto _________\n";
	[]() { std::cout << "in []"; }();
	cout << "\n\n";

	cout << "return 4_________\n";
	cout << [](int a) -> decltype(a, double(a))
	{ 
		if (a == 4)
			return (int)a;
		else
			return (double)a+0.5;	
	}(4) << endl;
	cout << "\n\n";

	cout << "return 5_________\n";
	cout << [](int a) -> decltype(a, double(a))
	{
		if (a == 4)
			return (int)a;
		else
			return (double)a + 0.5;
	}(5) << endl;
	cout << "\n\n";

	cout << "catch [] _________\n";
	
	function<double()> f =  []() -> double {
		if (1) return 5.5;
		return 1;
	};

	 cout << "f() ->" << f() << endl;


	
	
	cout << "\n\n";
}