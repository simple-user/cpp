#pragma once
#include <exception>

template <typename T>
class MyPriorityQueue
{
private:
	struct Element
	{
		Element() : next(nullptr){}
		Element(T val) : value(val), next(nullptr){}

		T value;
		Element *next;
	};
	Element *begin;
	// Element *end;
	size_t size;
public:
	class Iterator;
	MyPriorityQueue();
	~MyPriorityQueue();

	MyPriorityQueue(const MyPriorityQueue & m) = delete;
	MyPriorityQueue & operator=(const MyPriorityQueue &m) = delete;

	size_t getSize() const;
	void push(T val);
	T pop();
	Iterator ibegin();
	void printMe() const;

	class Iterator
	{
	public:
		Iterator(Element *p) : pointer(p){}
		Iterator & operator++()
		{
			pointer = pointer->next;
			return *this;
		}
		Iterator & operator++(int a)
		{
			Iterator t(*this);
			pointer = pointer->next;
			return t;
		}
		T & operator*()
		{
			return pointer->value;
		}
	private:
		Element * pointer;
	};

};

template <typename T>
MyPriorityQueue<T>::MyPriorityQueue() : size(0), begin(nullptr) { }

template <typename T>
MyPriorityQueue<T>::~MyPriorityQueue()
{
	while (begin)
	{
		Element *temp = begin->next;
		delete begin;
		begin = temp;
	}
}

template <typename T>
size_t MyPriorityQueue<T>::getSize() const
{
	return size;
}

template <typename T>
void MyPriorityQueue<T>::push(T val)
{
	Element *newElem = new Element(val);
	++size;
	if (!begin)
	{
		begin = newElem;
	}
	else
	{
		Element * counterElem = begin;
		Element * previousElem = nullptr;
		while (counterElem)
		{
			if (newElem->value > counterElem->value)
				break;
			else
			{
				previousElem = counterElem;
				counterElem = counterElem->next;
			}
		}

		// тут або за останнім (він же end->next)
		// або на позиції першого меншого
		newElem->next = counterElem;
		if (previousElem)
			previousElem->next = newElem;
		else
			begin = newElem;
	}
}

template <typename T>
T MyPriorityQueue<T>::pop()
{
	if (!begin)
		throw std::range_error("Range error in func pop: there is no elements!");

	T tempValue = begin->value;
	Element *tempEl = begin->next;
	delete begin;
	begin = tempEl;
	--size;
	return tempValue;
}

template <typename T>
void MyPriorityQueue<T>::printMe() const
{
	Element *temp = begin;
	while (temp)
	{
		cout << temp->value << endl;
		temp = temp->next;
	}
}

template <typename T>
typename MyPriorityQueue<T>::Iterator MyPriorityQueue<T>::ibegin()
{
	Iterator i (begin);
	return i;
}