#pragma once
#include <exception>

template <typename T>
class MyPriorityQueue
{
private:
	struct Element;
public:
	class ConstIterator; 
	MyPriorityQueue();
	~MyPriorityQueue();

	MyPriorityQueue(const MyPriorityQueue & m) = delete;
	MyPriorityQueue & operator=(const MyPriorityQueue &m) = delete;

	size_t getSize() const;
	void push(T val);
	T pop();
	ConstIterator cibegin() const;
	ConstIterator ciend() const;
	void printMe() const;

	class ConstIterator
	{
	public:
		ConstIterator(Element *p) : pointer(p){}
		ConstIterator & operator++()
		{
			pointer = pointer->next;
			return *this;
		}
		ConstIterator & operator++(int a)
		{
			Iterator t(*this);
			pointer = pointer->next;
			return t;
		}
		const T & operator*() const
		{
			return pointer->value;
		}

		const T* operator->() const
		{
			return (T*)pointer;  // ����� ��� :)
		}

	private:
		const Element * pointer;
	};

private:
	struct Element
	{
		Element() : next(nullptr){}
		Element(T val) : value(val), next(nullptr){}

		T value;
		Element *next;
	};
	Element *begin;
	Element *end;
	size_t size;
};

template <typename T>
MyPriorityQueue<T>::MyPriorityQueue() : size(0), begin(nullptr), end(nullptr) { }

template <typename T>
MyPriorityQueue<T>::~MyPriorityQueue()
{
	Element *temp=nullptr;
	while (begin)
	{
		temp = begin->next;
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
		end = newElem;
	}
	else
	{
		Element * counterElem = begin;
		Element * previousElem = nullptr;
		while (counterElem)
		{
			if (newElem->value > counterElem->value) //������ ������ ������� �� ���� ��� ������� ������
				break;                               //�������� �� ����� �������� �������� � ����� �������� �� �� ������
			else
			{
				previousElem = counterElem;         //�������� ������� ������ (� �������� �������� ���� ����� ��������� ���������)
				counterElem = counterElem->next;    //����� ��� �� ����������
			}
		}

		// ��� ��� �� ������� (�� �� end->next)
		// ��� �� ������� ������� �������
		newElem->next = counterElem;               // ������� ���������� �� ���� ��������� �� �������� ����� ��������� ��� ������
		if (previousElem)						   // ���� �� �� ������� ������� (���� ���������)
		{
			previousElem->next = newElem;          //����� ��������� ����� �� ��� ����� (� ����� ��� ������������� ����)
			if (!counterElem)					   //���� ����� ���� ���������� (����� ����� ��� ����� �������) �������� � END
				end = newElem;
		}
		else
			begin = newElem;                      //���� �� ������� ������� (������������ �� ����) �������� � BEGIN
	}
}

template <typename T>
T MyPriorityQueue<T>::pop()
{
	if (!begin)
		throw std::range_error("Range error in func pop: there is no elements!");

	T tempValue = std::move(begin->value);
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
typename MyPriorityQueue<T>::ConstIterator MyPriorityQueue<T>::cibegin() const
{
	ConstIterator ci (begin);
	return ci;
}

template <typename T>
typename MyPriorityQueue<T>::ConstIterator MyPriorityQueue<T>::ciend() const
{
	//if (end)
	//	ConstIterator ci(end->next); // �������� �� �������� STL. ������ ��� nullptr!!! :)))) ��� �����. ��� ��������.
	//else
		ConstIterator ci(nullptr);
	return ci;
}