#include <Windows.h>
#include <string>
#include <vector>
#include <iostream>
#include <exception>
#include <conio.h>
#include <algorithm>
#include "Ammo.h"
#include "Magazine.h"
#include "AK.h"


#define br cout << endl

#define _EXEPT_START try {
#define _EXEPT_END } \
	catch (std::exception &e) { \
	std::cout << "Error: " << e.what(); \
	} \
	catch (...) { \
	std::cout << "���-�� ����� �� ���... Chrome.(c) "; \
	} 

using std::cout;
using std::endl;


int main()
{

	_EXEPT_START
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	

	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	

	
	Ammo::numberStar = 1001;

	
	Magazine mag1;
	cout << "���������� ��������� ������� 1 (30 ����):" << endl;
	for (size_t a = 0; a < 30; ++a)
	{
		mag1.push(new Ammo());
		cout << "���������� ������: " << mag1.top()->getNumber() << endl;
	}
	br;


	Magazine mag2;
	cout << "���������� ��������� ������� 2 (15 ����):" << endl;
	for (size_t a = 0; a < 15; ++a)
	{
		mag2.push(new Ammo());
		cout << "���������� ������: " << mag2.top()->getNumber() << endl;
	}
	br;


	AK ak(&mag1);

	AK::Res res;

	cout << "������ ���������: " << endl;
	if (ak.pif(res))
		cout << "�������� ���������. ������ �" << res.num << " ���������: " << (res.res ? "������" : "��������") << endl;
	else
		cout << "�����!";
	br;

	cout << "������ ������ 10 �������: " << endl;
	
	std::vector<AK::Res> vecRes;
	if (ak.tratata(10, vecRes))
	{
		cout << "�������� ������. ����������:\n";
		std::for_each(vecRes.cbegin(), vecRes.cend(), [](const AK::Res &r) {cout << "������ �" << r.num << " ���������: " << (r.res ? "������" : "��������") << endl; });
	}
	else
		cout << "�����!";
	vecRes.clear();
	br;

	cout << "��������������. ������ ������ 100 �������: " << endl;

	if (ak.tratata(100, vecRes))
	{
		cout << "�������� ������. ����������:\n";
		std::for_each(vecRes.cbegin(), vecRes.cend(), [](const AK::Res &r) {cout << "������ �" << r.num << " ���������: " << (r.res ? "������" : "��������") << endl; });
	}
	else
		cout << "�����!";
	vecRes.clear();
	br;

	cout << "������ ���������: " << endl;
	if (ak.pif(res))
		cout << "�������� ���������. ������ �" << res.num << " ���������: " << (res.res ? "������" : "��������") << endl;
	else
		cout << "�����!";
	br;

	if (ak.ejectMag())
		cout << "������� ������� 1" << endl;
	else
		cout << "������� ��������� 1" << endl;
	br;

	if (ak.insertMag(&mag2))
		cout << "�������� ������� 2" << endl;
	else
		cout << "������� 2 �� ������������ :(" << endl;
	br;

	vecRes.clear();
	cout << "������ ������ �� ������� (100): " << endl;
	if (ak.tratata(100, vecRes))
	{
		cout << "�������� ������. ����������:\n";
		std::for_each(vecRes.cbegin(), vecRes.cend(), [](const AK::Res &r) {cout << "������ �" << r.num << " ���������: " << (r.res ? "������" : "��������") << endl; });
	}
	else
		cout << "�����!";
	vecRes.clear();
	cout << endl;


	_EXEPT_END
	return 0;
}



