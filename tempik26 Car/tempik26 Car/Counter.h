#pragma once
#include <climits>
class Counter
{
private:
	int _start;
	int _finish;
	int _now;
	bool plus;
public:
	Counter(int start, int finish, int now=INT_MIN);
	bool tick();
	int getNow() const;
};

