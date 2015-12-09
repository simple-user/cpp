#include <iostream>
#include <array>
#include <algorithm>
#include <string>
#include <functional>
#include <fstream>

using namespace std;



int main()
{

	ios::skipws; // - ����������� �����������
	ios::left; // ����� ������ ����������� �� ����� ����
	ios::right; // ����� ������ ����������� �� ����� ����
	ios::internal; // �� �����
	ios::oct; ios::dec; ios::hex;
	ios::showbase;
	ios::uppercase; // 
	ios::showpos; // ���� ����� ��������
	ios::showpoint; 
	ios::scientific;
	ios::fixed;
	ios::unitbuf; //���� ����� �������� ����� ���������
	ios::boolalpha;
	
	// ��� ���� ������� �� 1 ��� :)
	//cout.precision(4); //���� ������� ������� ������� ���� ������
	//cout.fill(' '); // ������ ��������, ���� ������ �����
	//cout.width(30); // ���������� ������ ������

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
	// ������� getline ������� ����������� � ������
	// istream & getline(char *buf, streamsize num)
	// istream & getline(char *buf, streamsize num, char delim)

	// ostream & put(char ch)
	// istream & ignore(sreamsize num=1, int_type delim=EOF) ������� ������� (�������, �� ���� �� ��������� �������)
	// int_type peek()  - ������� ��������� ������ �� �������� ���� � ������
	// istream &putback(char ch) - �������� ����� ������ 
	// ostream &flush() - ������������� �������� �����, ���� ����������� � ����� � �����
	// istream &seekg(off_type  offset, seekdir  origin); - ���������� ������� 
	// ostream &seekp(off_type  offset, seekdir  origin); - ���������� �������
	
	// ������� �������
	// pos_type tellg();
	// pos_type tellp();

	//iostate rdstate();
	//of.rdstate(); ����� ios::iostate 
	//ios::goodbit; // ��� ���
	//ios::eofbit; //����� �����
	//ios::failbit; //������ ��� ����� ���������
	//ios::badbit; //�������, ��� �� ����� ���������
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