#include <windows.h> 
#include <iostream>
using namespace  std;
void main()
{
	char buffer[] =
		"MultiByteToWideChar converts ANSI-string to Unicode-string";
	//  определим размер памяти,  необходимый для хранения Unicode-строки 
	int  length = MultiByteToWideChar(CP_ACP  /*ANSI  code page*/, 0, buffer,
		sizeof(buffer), NULL, 0);
	wchar_t *ptr = new wchar_t[length];
	// конвертируем ANSI-строку в Unicode-строку 
	MultiByteToWideChar(CP_ACP, 0, buffer, sizeof(buffer), ptr, length);
	cout << "---\n";
	wcout << L"=====" << ptr << endl;
	cout << "---\n";
	cout << "Length of sorce-string:  " << strlen(buffer) << endl;
	cout << "length: " << length << endl;
	cout << "Length of Unicode-string:  " << wcslen(ptr) << endl;
	cout << "Size of allocated memory:  " << _msize(ptr) << endl;
	delete[]  ptr;
}