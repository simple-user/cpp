#include <Windows.h>
#include "Xstring.h"
#include <stdexcept>

#define br cout << endl;

using std::cout;
using std::cin;
using std::endl;
using std::Xstring;

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	Xstring s1(Xstring("Microsoft"));
	Xstring s2("Windows");
	char ch[20] = "qwe";
	
	cout << "s1 : " << s1 << endl;
	cout << "s2 : " << s2 << endl;
	br
	int index = 0;
		
	while (1)
	{
		try
		{
			cout << "input index" << endl; cin >> index;
			cout << "s1[" << index << "] = " << s1[index] << endl;
			break;
		}
		catch (const char *e)
		{
			cout << "Error: " << e << endl;
		}
		catch (std::out_of_range &e)
		{
			std::cout << "Message: " << e.what() << endl;
		}
	} 
	return 0;
}

