#pragma once
#include <queue>
#include <ctime>
#include "Document.h"
#include "ConManip.h"
#include <mutex>


enum Status {TRY_PRINT, PRINTING, TRY_WAIT, WAITING, TRY_PREPARE, PREPARING, EXIT};
static const char* owners[7] = { "BOSS", "BOOKER", "CLERK", "STUDENT", "PUPIL", "CHILD", "BABY" };

class Printer
{
public:
	Printer(std::priority_queue<Document> &sp, std::mutex & m) : spooler(sp), mut(m), wait(0), printing(0), printingMax(0), preparing(0) {};

	void print();


private:
	void check();

	inline void writeWait(bool end=0);
	inline void writePrepare();
	inline void writePrinting();

	std::priority_queue<Document> &spooler;
	std::mutex &mut;
	Document d; 
	Status status;
	
	clock_t wait;
	static const clock_t waitMax = 10000;
	
	clock_t printing;
	clock_t printingMax;
	
	clock_t preparing;
	static const clock_t preparingMax = 3000;
};

