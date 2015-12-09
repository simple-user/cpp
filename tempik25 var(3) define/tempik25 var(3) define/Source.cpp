#include <Windows.h>
#include "Xstring.h"
#include "Var.h"

#define br cout << endl;

using std::cout;
using std::endl;
using std::Var;

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	Var v1(4), v2(5.5), v3("asd");
	int iVar = 1;
	double dVar = 2;
	std::Xstring xVar("3");
	
	cout << (v1 + v1 + v2 + v3 - v1 - v2 - v3 + 1 + 1.0 + "5" - 1 - 9.7 - "45" + std::Xstring("55")) * v1 * v2 << endl;
	
	cout << (v1 > 5 && v2 <= v3 || v3 == "asd" || v2 != 5.7) << endl;
	
	cout << "v1 = " << v1 << endl;
	cout << "v1 += 10 = " << (v1 += 10) << endl;
	cout << "v1 += \"13\" = " << (v1 += "13") << endl;
	cout << "v1 += \"asd\" = " << (v1 += "asd") << endl;
	cout << endl;
	cout << "v3 = " << v3 << endl;
	cout << "v3 += 10 = " << (v3 += 10) << endl;
	cout << "v3 += \"13\" = " << (v3 += "13") << endl;
	cout << "v3 += \"asd\" = " << (v3 += "asd") << endl;

	cout << endl;
	cout << "v2 = " << v3 << endl;
	cout << "v2 = 10.6 = " << (v2 = 10.6) << endl;
	cout << "v2 += 10 = " << (v2 += 10) << endl;
	cout << "v2 += \"13\" = " << (v2 += "13") << endl;
	cout << "v2 += \"asd\" = " << (v2 += "asd") << endl;
	cout << "v2 += v1 = " << (v2 += v1) << endl;

	return 0;
}

