#include "Army.h"


Army::Army(int countUnits)
{
	srand(unsigned(time(0)));
	// ����� �� ����� � ����� ������� ����, �� ���� �������� ��������� �� ��쳿
	Unit uArr[3] = { Swordsman(), Archer(), Mage() };
	for (int a(0); a < countUnits; a++)
		Units.push_back(uArr[rand() % 3]);

}

void Army::printArmy() const
{
	// ���� ������ ������
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
		// ���� ��� �������. ���������� �� �����, �������� � ������.
		Units.erase(Units.cbegin() + index);
		return 1;
	}

	return 0;
}

bool Army::attack(Army &ar) // 1 - ������ ��� ������!
{
	srand(unsigned(time(0)));
	// �������� ���� � ����� ��쳿
	int myWarior = rand() % Units.size();
	int opponentWarior = rand() % ar.Units.size();

	// ������� ��� ���� �����
	std::cout << Units[myWarior].getName() << " on position " << myWarior + 1 << " attacks "
		<< ar.Units[opponentWarior].getName() << "(hp: " << ar.Units[opponentWarior].getHp() << ") on position " << opponentWarior + 1 << std::endl;

	if (Units[myWarior].attack(ar.Units[opponentWarior]))
	{
		// ���� ����
		std::cout << "got it!" << std::endl;

		//��������� �� ������� �� ������� �� �����
		if (ar.Units[opponentWarior].died())
		{
			// �������. �������, ��������� � ������
			std::cout << ar.Units[opponentWarior].getName() << " died." << std::endl;
			ar.delVarior(opponentWarior);

			// ��������� �� ������� ������������
			if (ar.Units.size() == 0)
				return 1;
		}
		else
		{
			// �����. ������� ������ �������� ��
			std::cout << ar.Units[opponentWarior].getName() << " alive! (hp: " << ar.Units[opponentWarior].getHp() << ')' << std::endl;
		}
	}
	else
		std::cout << Units[myWarior].getName() << " missed! :(\n";

	return 0;

}