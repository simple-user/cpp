#include <iostream>
#include <numeric>

using namespace std;

template<typename T>
void f1(T&& arg)
{
	cout << "without forward: "; 
	n(arg);
}

/*
template<class T>
T&& forward(typename std::remove_reference<T>::type& t) noexcept{
	return static_cast<T&&>(t);
}

*/

template<typename T>
void f2(T&& arg)
{
	cout << "without forward: ";
	n(std::forward<T>(arg));
}


inline void n(int &a)
{
	std::cout << "int &a" << endl;
}
inline void n(const int &a)
{
	std::cout << "const int &a" << endl;
}
inline void n(int &&a)
{
	std::cout << "int &&a" << endl;
}
inline void n(int *a)
{
	std::cout << "int *a" << endl;
}
inline void n(const int *a)
{
	std::cout << "const int *a" << endl;
}
//inline void n(const int *const a)
//{
//	std::cout << "int &&a" << endl;
//}



int main()
{
	std::count
	
	
	int a = 20;
	const int b = 30;
	int *pa = &a;
	const int *pb = &b;
	const int *const pc = &b;

	cout << "----------10---------------\n";
	f1(10);
	f2(10);
	cout << "-----------a (int)--------------\n";
	f1(a);
	f2(a);
	cout << "----------b (const int)---------------\n";
	f1(b);
	f2(b);
	cout << "----------pa (int*)---------------\n";
	f1(pa);
	f2(pa);
	cout << "----------pb (const int*)---------------\n";
	f1(pb);
	f2(pb);
	cout << "----------pc (const int * const)---------------\n";
	f1(pc);
	f2(pc);
}