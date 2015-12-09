#include "Printer.h"


void Printer::print() // printing
{
	bool caseDone = 0;
	status = TRY_PREPARE; // ��������� ������� ���������
	// Sleep(100);
	while (status != EXIT)
	{
		check();
		do
		{
			switch (status)
			{
			case TRY_PRINT:
				// ���� ������ ���� preparing ���� �������� ����� �!
				printing = clock();
				status = PRINTING;
				caseDone = 1;   // ��������� ���� �������
				writePrinting();
				break;
			case PRINTING:
				writePrinting();
				break;
			case TRY_WAIT:
				wait = clock();
				status = WAITING;
				caseDone = 1;   // ��������� ���� �������
				writeWait();
				break;
			case WAITING:
				//���� ������ ���������� �� ����� ������ �� �������
				if (spooler.getSize())
				{
					status = TRY_PREPARE;
					caseDone = 0; //���������� ��� �����
					break;
				}
				writeWait();
				break;
			case TRY_PREPARE:
				if (!spooler.getSize())
				{
					status = TRY_WAIT;
					caseDone = 0;      // ����� �������� ����������
					break;
				}
				else
				{
					mut.lock();
					d =	spooler.pop();
					
					MyPriorityQueue<Document>::Iterator it = spooler.ibegin();
					int spoolerSize = spooler.getSize();
					gtoxy(40, 10, 40, 14, 7);
					for (int a(0); a < spoolerSize && a < 14; ++a, ++it) // a < 14 - ��� �� ��� ������ �� �����!
					{
						gtoxy(40, 10 + a, 7);
						std::cout << "Add: \"" << (*it).getName() << "\" size: " << (*it).getSize() << " by " << owners[(*it).getOwner()];
					}
									
					mut.unlock();
					printingMax = d.getSize() * 1000;
					preparing = clock();
					status = PREPARING;
					caseDone = 1;   // ��������� ���� �������
					writePrepare();
				}
				break;
			case PREPARING:
				writePrepare();
				break;
			}
		} while (!caseDone);
		Sleep(500);
	}
	writeWait(1); // time is over!
}

void Printer::check()
{
	if (status == PRINTING && (clock() - printing >= printingMax))
		status = TRY_PREPARE;
	else if (status == WAITING && (clock() - wait >= waitMax))
		status = EXIT;
	else if (status == PREPARING && (clock() - preparing >= preparingMax))
		status = TRY_PRINT;
}

inline void Printer::writeWait(bool end)
{
	mut.lock();
	gtoxy(0, 10, 38, 2, 7);
	gtoxy(0, 10, 7);
	if (end)
		std::cout << "Time is over!\n";
	else
		std::cout << "We are waiting for: " << (waitMax - (clock() - wait)) / 1000 << '.' << (waitMax - (clock() - wait)) % 1000 / 100 << "s\n";
	mut.unlock();
}
inline void Printer::writePrepare()
{
	mut.lock();
	gtoxy(0, 10, 38, 2, 7);
	gtoxy(0, 10, 7);
	std::cout << "Preparing: " << d.getName() << " by " << owners[d.getOwner()] << " ("
		<< (preparingMax - (clock() - preparing)) / 1000 << '.' << (preparingMax - (clock() - preparing)) % 1000 / 100 << "s)";
	gtoxy(0, 11, 7);
	std::cout << "Printing: wait";
	mut.unlock();
}
inline void Printer::writePrinting()
{
	mut.lock();
	gtoxy(0, 10, 38, 2, 7);
	gtoxy(0, 10, 7);
	std::cout << "Preparing: complete!";
	gtoxy(0, 11, 7);
	std::cout << "Printing: " << d.getName() << " by " << owners[d.getOwner()] << " ("
		<< (printingMax - (clock() - printing)) / 1000 << '.' << (printingMax - (clock() - printing)) % 1000 /100 << "s)";
	mut.unlock();
}