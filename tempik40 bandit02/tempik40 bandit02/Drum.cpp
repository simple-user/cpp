#include "Drum.h"

const char Drum::alphabet[] = { 1, 2, 3, 4, 5, 6, 11, 12, 14, 15 };
//                              1  2  3  4  5  6   7   8   9  10

const HANDLE Drum::hand = GetStdHandle(STD_OUTPUT_HANDLE);

Drum::Drum(size_t s, size_t x, size_t y, size_t start, int k0, clock_t period, clock_t stopSpan) : Updatable(period),  stopSpan(stopSpan), k(k0), size(s), xMin(x), yMin(y), startChar(start), counterUpdate(0)
{
	if (startChar + size > ALPH_COUNT)
		throw "error in Drum::Drum \n";
	
	size_t bitMask = 0;
	size_t t = 0;
	for (size_t a = 0; a < size; ++a)
	{
		do
		{
			t = start + rand() % size;  // підбираються з діапазону (size не входить - виходу за діапаз. немає)
		} while ((bitMask >> t) & 1); // якщо 1  - то біт вже й так встановлено
		// якщо вийшли то біт не встановлено
		//тоді для початку встановимо!
		bitMask |= (1 << t);
		deqDrum.push_back(alphabet[t]);
	}
	// в довільному порядку забили нашу чергу
	
}

void Drum::show() const
{
	SetConsoleCursorPosition(hand, COORD{ xMin, yMin });
	cout << deqDrum[0];
	SetConsoleCursorPosition(hand, COORD{ xMin, yMin+2 });
	cout << deqDrum[1];
	SetConsoleCursorPosition(hand, COORD{ xMin, yMin+4 });
	cout << deqDrum[2];

}

inline void Drum::tick()
{
	deqDrum.push_back(deqDrum.front());
	deqDrum.pop_front();
}

void Drum::update()
{
	if (isTimeToAction() && getPeriod()<stopSpan)
	{
		tick();
		show();
		++counterUpdate;

//		setPeriod(getPeriod() + counterUpdate*k);
//		setPeriod(getPeriod() + (-1 / (counterUpdate - 100) * 100 * k) );
//		setPeriod(getPeriod() + counterUpdate*counterUpdate / k);
		
		if (counterUpdate>50)
			setPeriod(getPeriod() + static_cast<clock_t>( exp((counterUpdate - 50) / k) ));

		//SetConsoleCursorPosition(hand, COORD{ xMin * 5, yMin + 8 });
		//cout << counterUpdate << " (" << getPeriod() << ")                 ";


	}
}