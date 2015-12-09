#pragma once
#include <iostream>


template <typename T>
class B
{
public:
	T f();
};

template <typename T>
T B<T>::f()
{
	std::cout << "B<T>::f()" << std::endl;
	return 0;
}