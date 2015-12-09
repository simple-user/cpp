#pragma once
#include <utility> // std::swap
#include "Ammo.h"
class Magazine
{
private:
	struct Am
	{
		Am() : val(nullptr), next(nullptr) {}
		Am(Ammo * v) : val(v), next(nullptr) {}
		
		Ammo *val;
		Am   *next;
	};

public:
	Magazine() : begin(nullptr), size(0) {};
	Magazine(const Magazine &src);  // �� ����������� ��������� �� � ��������� ���� :)
	Magazine(Magazine &&src); // move �� �������� ��� ���� ����� � ����������� :)

	~Magazine();

	void push(Ammo *val);
	void pop();
	Ammo *top() const ;
	size_t getSize() const;
	Magazine & operator=(const Magazine &src);
	Magazine & operator=(Magazine &&src);
	friend void swap(Magazine &m1, Magazine &m2);

private:
	
	void copyMagazine(const Magazine & src);

	Am *begin;
	size_t size;
	const size_t maxSize = 30;
};


