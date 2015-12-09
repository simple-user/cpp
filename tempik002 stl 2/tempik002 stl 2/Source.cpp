#include <iostream>
#include <string>
#include <algorithm>
#include <typeinfo>
#include <functional>
#include <utility>
#include <vector>
#include <iomanip>

using namespace std;



void printVec(vector<int> & v, string name)
{
	cout << setw(5) << name << " : ";
	for_each(v.cbegin(), v.cend(), [](int i){cout << i << ' '; });
	cout << endl;
}

void main()
{
	// функтори
	// унарні
	// negate
	// logical_not

	// times<T>   - множення
	// divides<T> - ділення
	// modulus<T> - остача від ділення
	// plus
	// minus
	
	// при створенні свого функтора потрібно чомусь наслідувати базові класи:
	// template<typename Argument, typemane Result> struct unary_function {}
	// template<typename Argument1, typename Argument2, typemane Result> struct binary_function {}
	// наприклад class someFunctor : public unary_function<int,int> {...}
	
	// редактор з"язків:
	// робить з бінарного функтора - унарний, підставляючи значення в:
	// перший аргумент - bind1st(бінакринй_функтор, значення) пр: bind1st(plus<int>(), 4);
	// другий аргумент - bind2nd(бінакринй_функтор, значення) пр: bind1nd(plus<int>(), 4);

	// інвентор (возвращает отрицание)
	// not1(unary_predicat)
	// not2(binary_predicat)

	

	vector<int> v(10);
	//fill_n(v.begin(), v.end(), 4);
	generate(v.begin(), v.end(), [](){ return rand() % 10; });
	printVec(v, "v");

	cout << "\n--------count------------------------------\n";
	cout << "count of 5 in v: " << count(v.cbegin(), v.cend(), 5) << endl;
	cout << "count of % 4 in v: " << count_if(v.cbegin(), v.cend(), [](int i) {if (i % 4) return false; return true; }) << endl;

	cout << "\n--------remove_copy------------------------------\n";

	vector<int> v2(10);
	printVec(v, "v");
	printVec(v2, "v2");
	remove_copy(v.cbegin(), v.cend(), v2.begin(), 8);
	printVec(v, "v");
	printVec(v2, "v2");

	cout << "\n--------replace_copy------------------------------\n";
	fill(v2.begin(), v2.end(), 0);
	printVec(v, "v");
	printVec(v2, "v2");
	replace_copy(v.cbegin(), v.cend(), v2.begin(), 8, 1);
	printVec(v, "v");
	printVec(v2, "v2");

	cout << "\n--------reverse------------------------------\n";
	printVec(v, "v");
	reverse(v.begin() + 2, v.end() - 2);
	printVec(v, "v");

}