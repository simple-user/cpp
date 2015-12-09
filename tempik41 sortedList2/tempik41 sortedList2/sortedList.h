#pragma once
#include <iostream>
#include <exception>
#include <string>

template <typename T>
class sortedList
{
public:
	typedef typename T& reference;
	typedef typename const T& const_reference;
private:
	struct node
	{
		// node() : val(), next(nullptr), prev(nullptr) {}
		// node(const T &srcVal) : val(srcVal), next(nullptr), prev(nullptr) {}
		template<typename ...types>
		node(types&& ... args) : val(args...),  next(nullptr), prev(nullptr) {}

		T val;
		node *next;
		node *prev;
	};

	struct indexator
	{
		indexator(size_t i, reference v, sortedList<T> *p) : index(i), slPtr(p), indVal(v) {}

		size_t index; // for del;
		sortedList<T> *slPtr; 
		reference indVal;

		friend std::ostream & operator<<(std::ostream &o, const indexator &i)
		{
			o << i.indVal;
			return o;
		}

		indexator operator=(const_reference val)
		{
			if (indVal == val)
				return indexator(*this);

			slPtr->removeAt(index);
			size_t newIndex = slPtr->insert(val);

			return indexator(newIndex, getRef(val), slPtr);

		}

		indexator operator=(const indexator &iSrc)
		{
			if (indVal == iSrc.indVal)
				return indexator(*this);

			slPtr->removeAt(index);
			size_t newIndex = slPtr->insert(iSrc.indVal);

			return indexator(newIndex, getRef(iSrc.indVal), slPtr);

		}

		reference getRef(const_reference val)
		{
			node *t = slPtr->begin;
			while (t && !(t->val == val))
				t = t->next;

			if (!t)
				throw std::logic_error("Error!");

			return t->val;
		}

	};

public:
	
	
	
	indexator operator[](size_t index)
	{
		if (index >= size)
		{
			throw std::out_of_range(std::string("Error: out of range. MaxIndex=" + std::to_string(size - 1) + ", curIndex=" + std::to_string(index)));
		}

		return indexator (index, getPtrByIndex(index)->val, this);
	}

	sortedList() : begin(nullptr), end(nullptr), size(0) {} // c-tor
	sortedList(const sortedList<T> &src) : begin(nullptr), end(nullptr), size(0) // copy constructor
	{
		copy(src);
	}
	sortedList(sortedList<T> &&src) // move c-tor;
	{
		begin = src.begin;
		src.begin = nullptr;

		end = src.end;
		src.end = nullptr;

		size = src.size;
		src.size = 0;
	}
	sortedList<T> & operator=(const sortedList<T> &src) // copy operator =
	{
		copy(src);
		return *this;
	}
	sortedList<T> & operator=(sortedList<T> &&src) //move operator =
	{
		std::swap(begin, src.begin);
		std::swap(end, src.end);
		std::swap(size, src.size);
	}

	size_t insert(const T &val)  // повертає номер позіції (індекса) в яку вставив
	{
		node *n = new node(val);
		return pushCreated(n);
	}

	bool remove(const T &val)  
	{
		node *t = begin;
		while (t)
		{
			if (t->val == val)
			{
				removeByPtr(t);
				--size;
				return true;
			}
			t = t->next;
		}
		return false;
	}
	int indexOf(const T &val)
	{
		node *t = begin;
		size_t pos = 0;
		while (t && !(t->val==val)) //t && t->val!=val
		{
			++pos;
			t = t->next;
		}
		if (t) // існує -  значить знайдено
			return pos;
		else   // незнайдено
			return -1
	}
	bool contains(const T &val)
	{
		if (indexOf(val) == -1)
			return false;
		return true;
	}

	template<typename ...types>
	size_t emplace(types&& ...args)
	{
		node *n = new node(std::forward<types>(args)...);
		return pushCreated(n);
	}
	
	const_reference first() const
	{
		if (!begin)
			throw std::logic_error("Error in const_reference first(). Container is empty;");
		return begin->val;
	}
	const_reference last() const
	{
		if (!end)
			throw std::logic_error("Error in const_reference last(). Container is empty;");
		return end->val;
	}
	
	void removeAt(size_t index)
	{
		removeByPtr(getPtrByIndex(index));
		--size;
	}
	bool removeFirst()
	{
		if (begin)
		{
			removeByPtr(begin);
			--size;
			return true;
		}
		return false;
	}
	bool removeLast()
	{
		if (end)
		{
			removeByPtr(end);
			--size;
			return true;
		}
		return false;
	}
	void clear()
	{
		clearMemory();
		begin = end = nullptr;
		size = 0;
	}
	size_t getSize() const
	{
		return size;
	}
	
	~sortedList()
	{
		clearMemory();
	}
	void show() // for tests
	{
		node *t = begin;
		while (t)
		{
			std::cout << t->val << ' ';
			t = t->next;
		}
		cout << endl;
	}


private:

	inline node* getPtrByIndex(size_t index)
	{
		if (index >= size)
		{
			throw std::out_of_range(std::string("Error: out of range. MaxIndex=" + std::to_string(size - 1) + ", curIndex=" + std::to_string(index)));
		}

		node *t = nullptr;
		if (size / 2 < index) // з початку
		{
			t = begin;
			for (size_t a = 0; a < index; ++a)
				t = t->next;
		}
		else // з кінця
		{
			t = end;
			for (size_t a = size - 1; a>index; --a)
				t = t->prev;
		}

		return t;
	}

	inline void removeByPtr(node * t)
	{
		if (t->prev) //якщо існує попередній
			t->prev->next = t->next;
		else         // якщо не існує - значить початок
			begin = t->next;

		if (t->next) //якщо існує наступний
			t->next->prev = t->prev;
		else         // якщо неіснує - значить кінець
			end = t->prev;
		delete t;
	}

	inline void clearMemory()
	{
		if (!begin) return;
		
		while (begin->next)
		{
			begin = begin->next;
			delete begin->prev;
		}
		delete begin;
	}

	void copy(const sortedList<T> &src)
	{
		size_t minSize = (size < src.size ? size : src.size);
		node *t1 = src.begin; // src
		node *t2 = begin;     // this
		for (; minSize; --minSize) // менша кількість буде у двох. там можна просто покопіювати значення
		{
			(t2->val) = (t1->val);
			t1 = t1->next;
			t2 = t2->next;
		}

		if (size>src.size) // значить наш список довший, підчищаємо
		{
			t2->prev->next = nullptr;
			end = t2->prev;
			
			while (t2)
			{
				t1 = t2->next;
				delete t2;
				t2 = t1;
				size--;
			}
		}
		else // наш менший, тому треба допушати(ЗАКРЕСЛЕНО!) вручну додати в кінець вже з виділенням пам"яті
		{	 // причому враховуючи, що src також впорядкований можна не перейматись сортуванням а тупо копіювати значення
			// ? t1 = t1->next; // так як ми його вже вписали у самому першому циклі
			
			// при чому якщо попали сюди то this <= src а t2 вказує на наступний після останнього елемент
			// значить перед додаванням поставимо t2 на останній (на end)
			t2 = end;
			// при чому якщо поточний пустий, то треба перший елемент створити вручну
			if (!end)
			{
				node *n = new node(t1->val);
				t2 = begin = end = n;
				t1 = t1->next;
				++size;
			}
			// при цьому t2 продовжує вказувати на кінець

			while (t1)     // навіть якщо вони однакові по довжині попаде сюди і на першій ітерації вилетить
			{
				node *n = new node(t1->val); // створили новий елемент
				n->prev = t2;				 // ввказали що для нього попередній - останній на даний час в списку
				t2->next = n;				 // для останнього вказали що наступний новостворений
				t2 = n;						 // перевели обидва вказівника
				t1 = t1->next;
				size++;
			}
			end = t2;	// при виході t2 буде вказувати на останній елемент

		}
	}

	size_t pushCreated(node* n)
	{
		node *t = begin;
		size_t pos = 0;

		if (!begin) // якщо пустий 
		{
			begin = end = n;
			++size;
			return pos;
		}

		// якщо непустий
		while (t && t->val <= n->val)  // t && t->val<=val
		{
			t = t->next;
			++pos;
		}

		if (!t) // значить додаємо в кінець
		{
			n->prev = end;
			end->next = n;
			end = n;
		}
		else
		{	// стоїмо на ноді перед якою потрібно вставити
			n->prev = t->prev;  // попередній для нового стане попередній для поточного
			n->next = t;        // наступний для нового стане поточний

			t->prev = n;		// для поточного попереднім тепер стане новий

			if (t != begin)		// якщо вписуємо не в початок, то той що перед новим повинен вказувати на новий
				n->prev->next = n;
			else
				begin = n;		// якщо новий став початком, то переміщаємо вказівник на початок
		}
		++size;
		return pos;
	}

	node *begin;
	node *end;
	size_t size;

};

