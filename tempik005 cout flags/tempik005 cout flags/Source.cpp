#include <iostream>
#include <array>
#include <algorithm>
#include <string>
#include <functional>

using namespace std;






void func1(long f)
{
	string str;
	while (f)
	{
		str.insert(str.begin(), (f & 1) + 48);
		f >>= 1;
	}
	cout << str << endl;
};

ostream & dendl(ostream & o)
{
	o << "\n\n";
	return o;
}

ostream & cspace(int count, ostream &o)
{
	for (; count; --count)
		cout << ' ';

	return o;
}

int main()
{

	ios::skipws; // - ігноруються разделители
	ios::left; // рядки виводу вирівнюються по лівому краю
	ios::right; // рядки виводу вирівнюються по лівому краю
	ios::internal; // по ширині
	ios::oct; ios::dec; ios::hex;
	ios::showbase;
	ios::uppercase; // 
	ios::showpos; // знак перед додатніми
	ios::showpoint; 
	ios::scientific;
	ios::fixed;
	ios::unitbuf; //після кожної операції буфер очищається
	ios::boolalpha;
	
	// цих штук вистачає на 1 раз :)
	//cout.precision(4); //задає кількість символів точності після крапки
	//cout.fill(' '); // добиває символом, якщо ширина більша
	//cout.width(30); // встановлює ширину виводу

	
	
	long f = cout.flags();
	
	
	auto func = [](long f)
	{
		string str;
		while (f)
		{
			str.insert(str.begin(), (f & 1) + 48);
			f >>= 1;
		}

		while (str.size() < 11)
		{
			str.insert(str.cbegin(), ' ');
		}
		cout << str << endl;
	};

	
	function<void(long f)> func2 = [](long f)
	{
		// string str;
		long l = 0x20000;
		while (l)
		{
			if (l & f)
				cout << '1';
			else
				cout << '0';
			l >>= 1;
		}
		cout << endl;
	};

		func2(64);
		func2(f);
		cout.setf(ios::right);
		cout.unsetf(ios::right);
		func2(f);
		cout << dendl;
		func2(ios::basefield);
		func2(ios::dec);
		func2(ios::hex);
		func2(ios::oct);
		cout << "some" << cspace() << endl;

	return 0;
}