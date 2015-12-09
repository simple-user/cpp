#include <iostream>
//#include <string>
#include <algorithm>
//#include <typeinfo>
#include <functional>
#include <utility>
#include <vector>

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

void vecPrint(vector<int> &vec, const char* str)
{
	cout << "vector: " << str << " - ";
	for (size_t a(0); a < vec.size(); ++a)
		cout << vec[a] << ' ';
	cout << "\n";
}

void main()
{
	{
		pair<int, double> p;
		p = std::make_pair<int, double>(4, 4);
	}

	{
	vector<int> vec = { 1, 2, 3, 4, 5 };

	vecPrint(vec, "vec");
	cout << "Reverse...\n";
	reverse(vec.begin(), vec.end());
	vecPrint(vec, "vec");

	cout << "Distance...\n";
	cout << distance(vec.begin(), vec.end()) << endl;

	cout << "*vec.begin() = " << *vec.begin() << endl;
	advance(vec.begin(), 3);
	cout << "*vec.begin() = " << *vec.begin() << endl << endl;

	vector<int>::iterator it = vec.begin();
	cout << "*it = " << *it << endl;
	advance(it, 3);
	cout << "it = " << *it << endl;

	cout << "transform1--------------------------\n";
	vector<int> vec2 = { 6, 7, 8, 9, 0 };
	vecPrint(vec, "vec");
	vecPrint(vec2, "vec2");
	cout << "transform(vec.cbegin(), vec.cend(), vec2.begin(), negate<int>()) \n";
	transform(vec.cbegin(), vec.cend(), vec2.begin(), negate<int>());
	vecPrint(vec, "vec");
	vecPrint(vec2, "vec2");
	cout << "transform1-end-------------------------\n";

	cout << "transform2--------------------------\n";
	vecPrint(vec, "vec");
	vecPrint(vec2, "vec2");
	cout << "transform(vec.cbegin(), vec.cend(), vec2.begin(), negate<int>()) \n";
	transform(vec.cbegin(), vec.cend(), vec2.cbegin(), vec2.begin(), plus<int>());
	
	//
	vecPrint(vec, "vec");
	vecPrint(vec2, "vec2");
	cout << "transform2-end-------------------------\n";

	cout << "transform3-[]-------------------------\n";
	vecPrint(vec, "vec");
	vecPrint(vec2, "vec2");
	cout << "transform(vec.cbegin(), vec.cend(), vec2.begin(), negate<int>()) \n";
	transform(vec.cbegin(), vec.cend(), vec2.begin(), [](int i) {return i * 2; });
	// transform(vec.cbegin(), vec.cend(), vec2.cbegin(), vec2.begin(), [](int a, int b){return a + b; });
	vecPrint(vec, "vec");
	vecPrint(vec2, "vec2");
	cout << "transform3-end-------------------------\n";

}

	{
		int a = 1, b = 2;
		cout << "int a = " << a << endl;
		cout << "int b = " << b << endl;
		plus<int> p;
		cout << "plus<int> p(a, b) = " << p(a, b) << endl;

		cout << "int a = " << a << endl;
		cout << "int b = " << b << endl;
		negate<int> n;
		cout << "negate<int> n(a) = " << n(a) << endl;
		
		// times<T>   - множення
		// divides<T> - ділення
		// modulus<T> - остача від ділення
		// plus
		// minus
		// negate

	}

	char str[200];
	str[199] = '\0';

	fgets(str, 199, stdin);
	fputs(str, stdout);

	cout << "\n\n";
}