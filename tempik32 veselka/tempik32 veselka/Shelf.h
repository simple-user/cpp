#pragma once
#include <iostream>
#include <string>
template <typename T>
class Shelf
{
public:
	Shelf(); //+
	explicit Shelf(size_t capacitySize); //+
	Shelf(size_t countElements, T element); //+

	Shelf(const Shelf &sh); //+
	Shelf(Shelf &&sh); //+

	~Shelf(); //+

	Shelf & operator=(Shelf sh); //+
	T & operator[](size_t index); //+

	void push_back(T t); //+
	void clear(); //+
	void erase(size_t index); //+
	void sortByPrice(bool up = 1); //+

	bool empty() const; //+
	int size() const; //+
	int capacity() const; //+
	int findFirstMinIndex() const; //+
	int findFirstMaxIndex() const; //+
	int averangePrice() const; //+
	void showNewItems() const; //+

	template <typename U>
	friend std::ostream & operator<<(std::ostream & os, const Shelf<U> & sh); //+

	template <typename U>
	friend void swap(Shelf<U> &sh1, Shelf<U> &sh2); //+

private:
	T * arr;
	size_t countElem;
	size_t capacitySize;
	void addMemory(); //+
	void swapElements(T &t1, T &t2);
};


template <typename T>
Shelf<T>::Shelf() : capacitySize(10), countElem(0), arr(nullptr){ arr = new T[capacitySize]; }

template <typename T>
Shelf<T>::Shelf(size_t capacitySize) : capacitySize(capacitySize + 5), countElem(0), arr(new T[capacitySize + 5]){}

template <typename T>
Shelf<T>::Shelf(size_t countElements, T element) : capacitySize(countElements + 5), countElem(countElements), arr(new T[countElements + 5])
{
	for (size_t a(0); a < countElements; a++)
		arr[a] = element;
}

template <typename T>
Shelf<T>::Shelf(const Shelf<T> &sh) : capacitySize(sh.capacitySize), countElem(sh.countElem), arr(new T[sh.capacitySize])
{
	std::memcpy(arr, sh.arr, countElem*sizeof(T));
}

template <typename T>
Shelf<T>::Shelf(Shelf<T> &&sh) : capacitySize(sh.capacity), countElem(sh.countElem), arr(sh.arr)
{
	sh.arr = nullptr;
}

template <typename T>
Shelf<T>::~Shelf()
{
	delete[] arr;
}

template <typename T>
void swap(Shelf<T> &sh1, Shelf<T> &sh2)
{
	std::swap(sh1.arr, sh2.arr);
	std::swap(sh1.countElem, sh2.countElem);
	std::swap(sh1.capacitySize, sh2.capacitySize);
}

template <typename T>
std::ostream & operator<<(std::ostream & os, const Shelf<T> & sh)
{
	for (size_t a(0); a < sh.countElem; a++)
		os << a	+ 1 << ". " << sh.arr[a] << endl;
	return os;
}

template <typename T>
Shelf<T> & Shelf<T>::operator=(Shelf<T> sh)
{
	swap<T>(*this, sh);
	return *this;
}

template <typename T>
T & Shelf<T>::operator[](size_t index)
{
	if (index >= countElem)
		throw std::out_of_range("Index " + std::to_string(index) + " out of range");

	return arr[index];
}

template <typename T>
void Shelf<T>::addMemory()
{
	size_t k = 0;

	if (capacitySize < 20)
		k = 5;
	else
		k = capacitySize / 4;
	
	T *t = new T[capacitySize + k];
	std::memcpy(t, arr, capacitySize);
	delete[] arr;
	arr = t;
	capacitySize += k;
}

template <typename T>
void Shelf<T>::push_back(T t)
{
	if (countElem == capacitySize)
		addMemory();

	arr[countElem] = std::move(t);
	countElem++;
}

template <typename T>
bool Shelf<T>::empty() const
{
	return countElem == 0;
}

template <typename T>
int Shelf<T>::size() const
{
	return countElem;
}

template <typename T>
int Shelf<T>::capacity() const
{
	return capacitySize;
}

template<typename T>
int Shelf<T>::findFirstMinIndex() const //+
{
	if (countElem == 0)
		throw std::range_error("You try to find min in zero count array!");

	int min = 0;

	for (size_t a(1); a < countElem; a++)
	{
		if (arr[min].getPrice()>arr[a].getPrice())
			min = a;
	}

	return min;
}

template<typename T>
int Shelf<T>::findFirstMaxIndex() const //+
{
	if (countElem == 0)
		throw std::range_error("You try to find min in zero count array!");

	int max = 0;

	for (size_t a(1); a < countElem; a++)
	{
		if (arr[max].getPrice()<arr[a].getPrice())
			max = a;
	}

	return max;
}

template <typename T>
int Shelf<T>::averangePrice() const
{
	if (countElem == 0)
		throw std::range_error("Can't find averange price in zero count array.");

	int averange = 0;
	for (size_t a(0); a < countElem; a++)
	{
		averange += arr[a].getPrice();
	}
	
	return averange / countElem;
}

template <typename T>
void Shelf<T>::showNewItems() const
{
	for (size_t a(0); a < countElem; a++)
	{
		if (arr[a].isItNew())
			cout << a+1 << ". " <<  arr[a].getName() << endl;
	}
}

template <typename T>
void Shelf<T>::clear()
{
	capacitySize = 10;
	countElem = 0;
	delete[] arr;
	arr = new T[capacitySize];
}

template <typename T>
void Shelf<T>::erase(size_t index)
{
	if (index >= countElem)
		throw std::out_of_range("Index " + std::to_string(index) + " out of range");

	for (size_t a(0); a < countElem-1; a++)
		if (a >= index)
			arr[a] = arr[a + 1];

	countElem--;
}

template <typename T>
void Shelf<T>::swapElements(T &t1, T &t2)
{
	T t = std::move(t1);
	t1 = std::move(t2);
	t2 = std::move(t);

}

template <typename T>
void Shelf<T>::sortByPrice(bool up = 1)
{
	if (countElem < 2)
		return;
	
	bool change = 1;

	for (size_t a(0); a < countElem-1 && change; a++)
	{
		change = 0;
		for (size_t b(0); b <= a; b++)
		{
			if ((arr[b].getPrice() < arr[b + 1].getPrice() && !up) || (arr[b].getPrice() > arr[b + 1].getPrice() && up))
			{
				swapElements(arr[b], arr[b + 1]);
				change = 1;
			}
			
		}
	}
}
