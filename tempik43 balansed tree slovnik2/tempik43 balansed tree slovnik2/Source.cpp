#include <iostream>
#include <ctime>
#include <Windows.h>
#include <conio.h>
#include <string>
#include "dictionary.h"

using std::cout;
using std::endl;
using std::string;

#define br cout << endl

#define _EXEPT_START try {
#define _EXEPT_END } \
	catch (std::exception &e) { \
	std::cout << "Error: " << e.what(); \
} \
catch (...) { \
	std::cout << "Что-то пошло не так... Chrome.(c) "; \
}



int main() 
{
	_EXEPT_START

	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);


	
	cout << "Welcome to doctionary!\n";
	dictionary d("dic.txt");
	char key = 0;
	string word;
	string word2;
	string *translation = nullptr;
	
	do
	{
		cout << "enter word: "; std::cin >> word;
		translation = d.translate(word);
		if (translation)
		{
			cout << word << " - " << *translation << endl;
			cout << "do you want to change translation? (y)";
			if (_getch() == 121 || _getch() == 237)
			{
				cout << "\nEnter new translation: "; std::cin >> word2;
				*translation = word2;
				cout << "Word changed successfully.\n";
			}
		}
		else
		{
			cout << "Enter translation: "; std::cin >> word2;
			d.addWord(word, word2);
			cout << "Word added successfully.\n";
		}
		cout << "esc? (y) \n";
	} while (_getch() != 121 && _getch() != 237);
	

	

	
	_EXEPT_END
	return 0;
}
