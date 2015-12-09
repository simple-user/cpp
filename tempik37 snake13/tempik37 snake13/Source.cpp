#include <Windows.h>
#include <string>
#include <iostream>
#include <exception>
#include <conio.h>
#include "Pole.h"
#include "Nyamka.h"
#include "Snake.h"
#include "Menu.h"

#define br cout << endl

#define _EXEPT_START try {
#define _EXEPT_END } \
	catch (std::exception &e) { \
	std::cout << "Error: " << e.what(); \
	} \
	catch (...) { \
	std::cout << "���-�� ����� �� ���... Chrome.(c) "; \
	} 

using std::cout;
using std::endl;

int main()
{

	_EXEPT_START
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	

	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

	Pole p(1, 1, 70, 20);
	Nyamka n(p);
	n.setCountNyam(10);
	Snake s(3, p,n);
	s.setSpeed(100);
	Menu m(n,p,s);

	
	while (m.runStartMenu())
	{
		bool restartGame = false;
		do
		{
			if (!m.is_loadingGame())
			{
				// ���� �� ������ ������� ���� ��� ���� ����!
				n.init();
				s.init();
			}
			p.drawPole();
			p.rewritePole();
			int resGame = 0;
			bool endRaund = false;
			do
			{
				if (resGame = s.move())
				{
					COORD co = { 0, p.yMax + 2 };
					SetConsoleCursorPosition(h, co);
					if (resGame == 1)
						cout << "You win!             ";
					else
						cout << "You lose!              ";

					// ���� ���� �� ������ �� ��� ��������� 
					// ���� ��������� �� �������� � ��������� ESC
					int arrKey[2] = {};
					do
					{
						arrKey[0] = _getch();
						if (_kbhit()) arrKey[1] = _getch();
					} while (arrKey[0] != 27);
					endRaund = true;

					m.SaveScore();

					p.clearPole();
					n.clear();
					s.clear();
				}
				else // resGame == 0 ����� ������ �� ESC (����� - �������� �������)
				{
					// ��� ��� �����. � ��� ����������� ��� ��� ��
					// ����� ������� �������� goto... ��... ������ ������� ��������... ����� ������� :)
					pausePoint: // ����� ����� ������� �� ������. ��� ��������� :)
					int resPause = m.runPauseMenu();
					switch (resPause)
					{
					case 0: // restart
						endRaund = 1; // ��� ��� �� ������
						restartGame = 1; // ��������� � ���� ����� ������
						//������� ���� ���
						p.clearPole();
						n.clear();
						s.clear();
						break;
					case 1: // new game
						endRaund = 1;
						restartGame = 1;
						//������� ���� ���
						p.clearPole();
						n.clear();
						s.clear();
						m.startNewGame();
						break;
					case 2: // save game
					{
						string s;
						m.inputStr("Enter name: ",s);
						m.saveGame(s);
						// �� ��� ��� ������! :)
						goto pausePoint;
						break;
					}
					case 3: // main menu
						endRaund = 1;
						restartGame = 0;
						p.clearPole();
						n.clear();
						s.clear();
						break;
					case -1: // contin
						endRaund = 0;
						p.rewritePole();
						break;
					}
					
				}
			} while (!endRaund);
		} while (restartGame);

	}
	


	_EXEPT_END
	return 0;
}



