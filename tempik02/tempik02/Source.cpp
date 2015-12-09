#include <iostream>

using std::cout;

struct A
{
	int *i;
};

void main()
{
	int *i = nullptr;

	cout << "size = " << sizeof(i) << std::endl;
	cout << "size struct = " << sizeof(A) << std::endl;
}