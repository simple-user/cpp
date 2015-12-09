#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <vector>
#include <iterator>
#include <vector>
#include <algorithm>



int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	std::vector<int> vec(10); // count - 10, val - 5
	int counter = 0;
	std::generate(vec.begin(), vec.end(), [&counter](){return ++counter; });
	std::for_each(vec.cbegin(), vec.cend(), [](int a){std::cout << a << ' '; });
	std::cout << std::endl;
	//--------------------------------class insert_iterator--------------------------------
	// використовується для вставки нових значень а не зміни!
	// вставляє в те місце, куди вказує ітератор where (другий параметр конструктора)

	// template<typename Cont> class insert_iterator : public iterator<output_iterator_tag, void,void, void, void>

	// constructor
	// std::insert_iterator< typename container > iitVec(container & cont, container::iterator where);
	std::insert_iterator<std::vector<int>> iitVec(vec, vec.begin());
	*iitVec = 200;  // відбувається вставка а не заміна! 
	std::for_each(vec.cbegin(), vec.cend(), [](int a){std::cout << a << ' '; });
	std::cout << std::endl;

	// функція inserter для створення об"єкта insert_iterator
	//template <typename Container>
	//std::insert_iterator<Container> inserter(Container &cont, Container::iterator where);

	//--------------------------------class back_insert_iterator--------------------------------
	// аналогічно з попереднім, тільки вконструкторі не передається ітератор
	// тут же визначена функція back_inserter()  для ствонення об"єкта

	//--------------------------------class front_insert_iterator--------------------------------
	// аналогічно з попереднім...

	
	//--------------------------------class reverse_iterator--------------------------------

	std::reverse_iterator<std::vector<int>::iterator> ritVec(vec.rbegin());
	std::cout << "reverse iterator: " << *ritVec << std::endl;
	std::cout << "reverse iterator: " << *ritVec << std::endl;
	ritVec++;
	std::cout << "reverse iterator: " << *ritVec << std::endl;
	// 
	// ritVec.base();  вертає ітератор на основі якого був створений даний

	//--------------------------------class istream_iterator--------------------------------

	std::istream_iterator<char> istrIt(std::cin);
	size_t t = 0;
	do
	{
		std::cout << "chars in istrIt: " << *(istrIt++) << std::endl;
	} while (*istrIt != '.');



	return 0;
}