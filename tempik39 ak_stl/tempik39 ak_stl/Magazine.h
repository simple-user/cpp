#pragma once
#include <utility> // std::swap
#include <stack>
#include <forward_list>
#include <list>
#include "Ammo.h"

using std::stack;
using std::forward_list;
using std::list;

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
	
	Magazine() = default;
	Magazine(const Magazine &src) = default;
	~Magazine() = default;

	void push(Ammo *val) { if (container.size() < maxSize) container.emplace(val); }
	void pop() { container.pop(); }
	Ammo *top() const { return container.top().val; }
	size_t getSize() const { return container.size(); }
	
	Magazine & operator=(const Magazine &src) = default;
	
private:
	 
	stack<Am, list<Am>> container;
	const size_t maxSize = 30;
};


