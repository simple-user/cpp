#include "Header.h"
#include <string>

using namespace std;
class A0
{
public:
	int buffer;
	A0(int b) : buffer(b)
	{
		cout << "create A0, buffer: " << buffer << endl;
	}

	A0(const A0& a)
	{
		cout << "const A0& for buffer: " << buffer << " from bufferr: " << a.buffer << " object" << endl;
		buffer = a.buffer;
	}

	A0(A0&& a)
	{
		cout << "A0&& for buffer: " << buffer << "from buffer: " << a.buffer << " object" << endl;
		//cout << "in (A&& a) adr a: " << &a << endl;
		*this = move(a);
		/*buffer = buffer;
		S = a.S;*/
	}

};

class A
{
public:
	int buffer;
	A0 S;
	
	A(int i) : buffer(i), S(i)
	{
		cout << "create obj A, buffer: " << buffer << endl;
	}

	A(const A& a) : buffer(a.buffer), 
	{
		cout << "const A& for " << S << " from: " << a.S << " object" << endl;
		buffer = a.buffer;
		S = a.S;
	}

	A(A&& a)
	{
		cout << "A&& for " << S << "from: " << a.S << " object" << endl;
		//cout << "in (A&& a) adr a: " << &a << endl;
		this = &a;
		/*buffer = buffer;
		S = a.S;*/
	}

	string& getS()
	{
		return S;
	}

};

A create_A()
{
	A a_local("#A_in_func#");
	cout << "adr S in func: " << &a_local.S << endl;
	return a_local;
}

int main()
{
	
	////--------------------------------------
	//A a1("a1");
	//cout << "adr of a1: " << &a1 << endl;
	//A a2(a1);
	//cout << "adr of a1(after): " << &a1 << " a1.S: " << a1.S << " addr of a1.S: " << &(a1.S) << endl;
	//cout << "adr of a2(after): " << &a2 << " a2.S: " << a2.S << " addr of a2.S: " << &(a2.S) << endl;
	//cout << endl << endl;

	A &&tmp = create_A();

	A a3(tmp);
	cout << "adr of tmp: " << &tmp << " tmp.S: " << tmp.S << " addr of tmp.S: " << &tmp.S << endl;
	cout << "adr of a3: " << &a3 << " a3.S: " << a3.S << " addr of a3.S: " << &a3.S << endl;

	
	////--------------------------------------



	////int a = 4;
	////cout << "a: " << a << " - " << &a << endl;
	//int &&b = 4;
	//const int &c = 4;
	////cout << "a: " << a << " - " << &a << endl;
	//cout << "b: " << b << " - " << &b << endl;
	//cout << "c: " << c << " - " << &c << endl;


	return 0;
	

}

