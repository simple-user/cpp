#pragma once
#include <deque>
#include <cstdlib>
#include <iostream>
#include <Windows.h>
#include "Updatable.h"

using std::deque;
using std::cout;
using std::endl;

class Drum : public Updatable
{
public:
	
	Drum(size_t s, size_t x, size_t y, size_t start, int k0, clock_t period);
	Drum(const Drum&) = delete;
	Drum & operator=(const Drum &) = delete;
	~Drum() = default;

	virtual void update() override;
	void show() const;
	inline void tick();
	static const HANDLE hand;
	char getRes() const
	{
		return deqDrum[1];
	}

	void resetCounterUpdate()
	{
		counterUpdate = 0;
	}

private:
	deque<char> deqDrum;
	size_t size; 
	size_t xMin;
	size_t yMin;
	size_t startChar;
	size_t counterUpdate;
	int k; //коефіцієнт сповільненя
	static const size_t ALPH_COUNT = 10;
	static const char alphabet[ALPH_COUNT];
};


