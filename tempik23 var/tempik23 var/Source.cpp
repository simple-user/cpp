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
	cout << "v1 = " << v1 << endl;
	cout << "v2 = " << v2 << endl;
	cout << "v3 = " << v3 << endl;
	cout << "iVar = " << iVar << endl;
	cout << "dVar = " << dVar << endl;
	cout << "xVar = " << xVar << endl;
	cout << "----------------------------------\n";
	cout << "v1+=4 = " << (v1 += 4) << endl;
	cout << "v1+=xVar = " << (v1 += xVar) << endl;
	cout << "v1 += v2 = " << (v1 += v2) << endl;
	cout << "v3 += v1 = " << (v3 += v1) << endl;

	cout << "----------------------------------\n";
	cout << "v + int:" << endl;
	cout << "v1 + 1 = " << v1 + 1 << endl;
	cout << "v2 + 1 = " << v2 + 1 << endl;
	cout << "v3 + 1 = " << v3 + 1 << endl;
	cout << "----------------------------------\n";
	cout << "v + v(int):" << endl;
	cout << "v1 + v(1) = " << v1 + v1 << endl;
	cout << "v2 + v(1) = " << v2 + v1 << endl;
	cout << "v3 + v(1) = " << v3 + v1 << endl;
	cout << endl;
	cout << "----------------------------------\n";
	cout << "int + v:" << endl;
	cout << "1 + v1 = " << 1 + v1 << endl;
	cout << "1 + v2 = " << 1 + v2 << endl;
	cout << "1 + v3 = " << 1 + v3 << endl;
	cout << "----------------------------------\n";
	cout << "v(int) + v:" << endl;
	cout << "1 + v1 = " << v1 + v1 << endl;
	cout << "1 + v2 = " << v1 + v2 << endl;
	cout << "1 + v3 = " << v1 + v3 << endl;
	cout << "----------------------------------\n";


	return 0;
}

