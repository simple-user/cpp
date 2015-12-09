#include <iostream>
#include <Windows.h>
#include <conio.h>

using namespace std;



int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	for (int a = 0; a < 1000; a++)
		cout << char(64 + a % 26);

	HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);


	CHAR_INFO ch[4 * 4];
	for (int a = 0; a < 16; a++)
	{
		ch[a].Char.AsciiChar = 'a';
		ch[a].Char.UnicodeChar = L'b';
	}
	PCHAR_INFO pChInfo = ch;
	COORD bufSize = { 4, 4 };
	COORD pos = { 5, 0 };
	SMALL_RECT rect = { 5, 0, 8, 3 };

	ReadConsoleOutput(hand, pChInfo, bufSize, pos, &rect);

	

	return 0;
}