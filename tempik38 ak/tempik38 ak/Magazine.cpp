#include "Magazine.h"

Magazine::Magazine(const Magazine &src)
{
	copyMagazine(src);
}

Magazine::Magazine(Magazine &&src) // move не забуваємо про всякі ніштякі з оптимізацією :)
{
	begin = src.begin;
	size = src.size;
	src.begin = nullptr;
	src.size = 0;
}

void swap(Magazine &m1, Magazine &m2)
{
	std::swap(m1.begin, m2.begin);
	std::swap(m1.size, m2.size);
}

Magazine & Magazine::operator=(const Magazine &src)
{
	copyMagazine(src);
	return *this;
}

Magazine & Magazine::operator=(Magazine &&src)  // оптимізація канєш слабенька, натомість виглядає норм! :)
{
	swap(*this, src); // оппа :) 
	return *this;
}


Magazine::~Magazine()
{
	Am *t = begin;
	while (begin)
	{
		t = t->next;
		delete begin->val;
		delete begin;
		begin = t;
	}

}

Ammo * Magazine::top() const
{
	if (!begin)
		throw "tratata...";
	return begin->val;
}


void Magazine::push(Ammo *val)
{
	if (size == maxSize)
		throw "Bla-bla-bla... eror push!\n";
	
	Am *t = new Am(val);
	t->next = begin;
	begin = t;
	++size;
}

void Magazine::pop()
{
	if (size==0)
		throw "Bla-bla-bla... eror pop!\n";

	Am *t = begin;
	begin = begin->next;
	delete t->val;
	delete t;
	--size;
}

size_t Magazine::getSize() const
{
	return size;
}



void Magazine::copyMagazine(const Magazine & src)
{
	size_t minSize = (size < src.size ? size : src.size);
	Am *t1 = src.begin; // src
	Am *t2 = begin;     // this
	for (; minSize; --minSize) // менша кількість буде у двох. там можна просто покопіювати значення
	{
		*(t2->val) = *(t1->val);
		t1 = t1->next;
		t2 = t2->next;
	}

	if (size>src.size) // значить в нашому ще є патрони, а src - вже кінець. чистимо наш
	{
		while (t2)
		{
			t1 = t2->next;
			delete t2->val;
			delete t2;
			t2 = t1;
			size--;
		}
	}
	else // наш менший, тому треба допушати(ЗАКРЕСЛЕНО!) вручну додати в кінець вже з виділенням пам"яті
	{
		t1 = t1->next; // так як ми його вже вписали у самому першому циклі
		while (t1)     // навіть якщо вони однакові по довжині попаде сюди і на першій ітерації вилетить 
		{
			Am *n = new Am(new Ammo( *(t1->val) ));
			t2->next = n;
			t2 = t2->next;
			t1 = t1->next;
			size++;
		}

	}
}
