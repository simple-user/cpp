#include "Army.h"
#include <typeinfo>


Army::Army(int countUnits)
{
	srand(unsigned(time(0)));
	Unit *temp = nullptr;

	for (int a(0); a < countUnits; a++)
	{
		switch(rand() % 3)
		{
		case 0:	temp = new Swordsman(); break;
		case 1:	temp = new Archer(); break;
		case 2:	temp = new Mage(); break;
		}
		Units.push_back(temp);
	}

}

void Army::printArmy() const
{
	// друк всього війська
	for (unsigned int a(0); a < Units.size(); a++)
	{
		std::cout << a + 1 << ". " << Units[a]->getName() << ", (hp: " << Units[a]->getHp() << ")" << std::endl;
	}
	std::cout << std::endl;
}


bool Army::delVarior(int index)
{
	if (Units[index]->died())
	{
		// якщо воїн загинув. похоронили як героя, видалили зі списків.
		delete Units[index];
		Units.erase(Units.cbegin() + index);
		return 1;
	}

	return 0;
}

bool Army::attack(Army &ar) // 1 - виграш бою всього!
{
	srand(unsigned(time(0)));
	// вибираємо воїнів з кожної армії
	int myWarior = rand() % Units.size();
	// шукаємо такого самого у опонента
	int opponentWarior = -1;
	for (unsigned int a(0); a < ar.Units.size(); a++)
		if (typeid(*Units[myWarior]) == typeid(*ar.Units[a]))
		{
			//std::cout << typeid(*Units[myWarior]).name() << " <===> " << typeid(*ar.Units[a]).name() << std::endl;
			// std::cout << typeid(*(Units.data() + myWarior)).name() << " <===> " << typeid(ar.Units[a]).name() << std::endl;
			opponentWarior = a;
			break;
		}
	
	// якщо не знайшли - тоді рандом
	if (opponentWarior==-1)
		opponentWarior= rand() % ar.Units.size();

	// друкуємо хто кого атакує
	std::cout << Units[myWarior]->getName() << " on position " << myWarior + 1 << " attacks "
		<< ar.Units[opponentWarior]->getName() << "(hp: " << ar.Units[opponentWarior]->getHp() << ") on position " << opponentWarior + 1 << std::endl;

	if (Units[myWarior]->attack(*ar.Units[opponentWarior]))
	{
		// якщо успєх
		std::cout << "got it!" << std::endl;

		//перевіримо чи опонент не загинув від удару
		if (ar.Units[opponentWarior]->died())
		{
			// загинув. друкуємо, видаляємо зі списку
			std::cout << ar.Units[opponentWarior]->getName() << " died." << std::endl;
			ar.delVarior(opponentWarior);

			// перевіримо чи опонент розгромлений
			if (ar.Units.size() == 0)
				return 1;
		}
		else
		{
			// вижив. друкуємо скільки лишилось ХП
			std::cout << ar.Units[opponentWarior]->getName() << " alive! (hp: " << ar.Units[opponentWarior]->getHp() << ')' << std::endl;
		}
	}
	else
		std::cout << Units[myWarior]->getName() << " missed! :(\n";

	return 0;

}