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
			return (T*)pointer;  // якось так :)
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
			if (newElem->value > counterElem->value) //шукаємо перший елемент за який наш елемент більший
				break;                               //відповідно як тільки знаходим виходимо з циклу вказуючи на цю адресу
			else
			{
				previousElem = counterElem;         //зберігаємо поточну адресу (у наступній ітерації вона стане попередній елементом)
				counterElem = counterElem->next;    //йдемо далі по контейнеру
			}
		}

		// тут або за останнім (він же end->next)
		// або на позиції першого меншого
		newElem->next = counterElem;               // оскільки вставляємо на місце поточного то поточний стане наступним для нашого
		if (previousElem)						   // якщо не на першому елементі (існує попередній)
		{
			previousElem->next = newElem;          //тепер попередній вказує на наш новий (а новий вже перенаправили вище)
			if (!counterElem)					   //якщо стоїмо після останнього (тобто тепер наш стане останнім) зберігаємо у END
				end = newElem;
		}
		else
			begin = newElem;                      //якщо на першому елементі (попереднього не існує) зберігаємо у BEGIN
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
	//	ConstIterator ci(end->next); // відповідно до принципів STL. правда тут nullptr!!! :)))) але ладно. для практики.
	//else
		ConstIterator ci(nullptr);
	return ci;
}