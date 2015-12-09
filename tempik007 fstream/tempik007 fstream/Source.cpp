#include <iostream>
#include <array>
#include <algorithm>
#include <string>
#include <functional>
#include <fstream>

using namespace std;



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

	struct S
	{
		S() : A(1), B(2), C('3') {}
		int A;
		int B;
		char C;
	} s;

	ofstream of("text", ios::out | ios::binary);

	 
	if (!of)
	{
		cout << "fail" << endl;
		return 1;
	}

	of.write((char*)&s, sizeof(S));
	of.write((char*)&s, sizeof(S));
	of.write((char*)&s, sizeof(S));

	of.close();

	ifstream i("text", ios::in | ios::binary);

	// int get() - 
	// istream & get(char &ch)
	// istream & get(char *buf, streamsize num)   
	// istream & get(char *buf, streamsize num, char delim)
	// функція getline видаляє разделитель з потоку
	// istream & getline(char *buf, streamsize num)
	// istream & getline(char *buf, streamsize num, char delim)

	// ostream & put(char ch)
	// istream & ignore(sreamsize num=1, int_type delim=EOF) пропуск символів (кількість, та поки не досягнуто символа)
	// int_type peek()  - зчитати наступний символ не извлекая його з потоку
	// istream &putback(char ch) - покласти назад символ 
	// ostream &flush() - принудительно записати текст, який знаходиться в буфері у поток
	// istream &seekg(off_type  offset, seekdir  origin); - переміщення курсора 
	// ostream &seekp(off_type  offset, seekdir  origin); - переміщення курсора
	
	// поточна позиція
	// pos_type tellg();
	// pos_type tellp();

	//iostate rdstate();
	//of.rdstate(); вертає ios::iostate 
	//ios::goodbit; // все гуд
	//ios::eofbit; //кінець файла
	//ios::failbit; //пмилка яку можна виправити
	//ios::badbit; //помилка, яку не можна виправити
	//bool bad();
	//bool eof();
	//bool fail();
	//bool good();


	char ch = 0;
	while (i.get(ch))
	if (ch<=255 && ch>=-1 && isprint(ch))
			cout << ch;
	else
		cout << '.';
	cout << endl;

	i.close();



	return 0;
}