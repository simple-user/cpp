#include <Windows.h>
#include "Xstring.h"

#define br cout << endl;

using std::cout;
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
	cout << s1 + " " + s2 << endl;
	br
	cout << s1 + s2 << endl;
	cout << s1 + "Windows" << endl;
	cout << "Microsoft" + s2 << endl;
	cout << ch + s2 << endl;
	cout << s1 + ch << endl;
	cout << (s1 += s2) << endl;
	s1 = "Microsoft";
	br
	cout << s1 * s2 << endl;
	cout << s1 * "Windows" << endl;
	cout << "Microsoft" * s2 << endl;
	cout << (s1 *= s2) << endl;
	s1 = "Microsoft";
	br
	cout << s1 / s2 << endl;
	cout << s1 / "Windows" << endl;
	cout << "Microsoft" / s2 << endl;
	cout << (s1 /= s2) << endl;
	s1 = "Microsoft";
	br
	cout << "s1[3] = " << s1[3] << endl;
	cout << "s1(3,3) = " << s1(3, 3) << endl;
	br;
	cout << (s1 > s2) << endl;
	cout << ("Microsoft" > s2) << endl;
	cout << (s1 > "Windows") << endl;
	br;
	cout << (s1 >= s2) << endl;
	cout << ("Microsoft" >= s2) << endl;
	cout << (s1 >= "Windows") << endl;
	br;
	cout << (s1 < s2) << endl;
	cout << ("Microsoft" < s2) << endl;
	cout << (s1 < "Windows") << endl;
	br;
	cout << (s1 <= s2) << endl;
	cout << ("Microsoft" <= s2) << endl;
	cout << (s1 <= "Windows") << endl;
	br;
	cout << (s1 == s2) << endl;
	cout << ("Microsoft" == s2) << endl;
	cout << (s1 == "Windows") << endl;
	br;
	cout << (s1 != s2) << endl;
	cout << ("Microsoft" != s2) << endl;
	cout << (s1 != "Windows") << endl;
	return 0;
}

