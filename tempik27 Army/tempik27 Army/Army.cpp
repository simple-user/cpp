#include "Army.h"


Army::Army(int countUnits)
{
	srand(unsigned(time(0)));
	// масив на стеку з трьох варіантів воїнів, які потім рандомно додаються до армії
	Unit uArr[3] = { Swordsman(), Archer(), Mage() };
	for (int a(0); a < countUnits; a++)
		Units.push_back(uArr[rand() % 3]);

}

void Army::printArmy() const
{
	// друк всього війська
	for (unsigned int a(0); a < Units.size(); a++)
	{
		std::cout << a + 1 << ". " << Units[a].getName() << ", (hp: " << Units[a].getHp() << ")" << std::endl;
	}
	std::cout << std::endl;
}


bool Army::delVarior(int index)
{
	if (Units[index].died())
	{
		// якщо воїн загинув. похоронили як героя, видалили зі списків.
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
	int opponentWarior = rand() % ar.Units.size();

	// друкуємо хто кого атакує
	std::cout << Units[myWarior].getName() << " on position " << myWarior + 1 << " attacks "
		<< ar.Units[opponentWarior].getName() << "(hp: " << ar.Units[opponentWarior].getHp() << ") on position " << opponentWarior + 1 << std::endl;

	if (Units[myWarior].attack(ar.Units[opponentWarior]))
	{
		// якщо успєх
		std::cout << "got it!" << std::endl;

		//перевіримо чи опонент не загинув від удару
		if (ar.Units[opponentWarior].died())
		{
			// загинув. друкуємо, видаляємо зі списку
			std::cout << ar.Units[opponentWarior].getName() << " died." << std::endl;
			ar.delVarior(opponentWarior);

			// перевіримо чи опонент розгромлений
			if (ar.Units.size() == 0)
				return 1;
		}
		else
		{
			// вижив. друкуємо скільки лишилось ХП
			std::cout << ar.Units[opponentWarior].getName() << " alive! (hp: " << ar.Units[opponentWarior].getHp() << ')' << std::endl;
		}
	}
	else
		std::cout << Units[myWarior].getName() << " missed! :(\n";

	return 0;

}