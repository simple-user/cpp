#include <iostream>
#include <climits>
#include "Counter.h"

using namespace std;

//Counter(int min, int max, int start);
Counter::Counter(int start, int finish, int now) : _start(start), _finish(finish), _now(now==INT_MIN ? start : now)
{
	if (start==finish)
		exit(1);

	plus = finish>start;
	
	if(plus && (_now<_start || _now>_finish) || !plus && (_now>_start || _now<_finish))
		exit(1);
}
//bool tick();
bool Counter::tick()
{
	plus ? _now++ : _now--;
	if (plus && _now>_finish || !plus && _now<_finish)
	{
		_now=_start;
		return 1;
	}
	return 0;
}

//	int getNow() const;
int Counter::getNow() const
{
	return _now;
}


