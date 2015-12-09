#include <Windows.h>
#include "Group.h"
#include "Head.h"
#include "Menu.h"


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Menu m;
	m.addPunkt(0, "1. �������� ���� ����� (������)");
	m.addPunkt(0, "2. �������� �����");
	m.addPunkt(0, "3. ������� ����� (��� ������ � ���)");
	m.addPunkt(0, "4. ������ � ������ (�������� �.3) >>>");
	m.addMenu(4);
	m.addPunkt(4, "1. �������� �����");
	m.addPunkt(4, "2. ������ ��������");
	m.addPunkt(4, "3. �������� ��������");
	m.addPunkt(4, "4. ��������� �������� � ���� �����");
	m.addPunkt(4, "5. ���� ������� >>>");
	m.addMenu(45);
	m.addPunkt(45, "1. �� ������ �����");
	m.addPunkt(45, "2. � �� ���� >>>");
	m.addMenu(452);
	m.addPunkt(452, "1. ����� �������������������");
	m.addPunkt(452, "2. �������");

	Groups groups = { nullptr, 0, -1 };
	int res = 0;

	do{
		res = m.runMenu();
		menuResultCatch(res, groups);
	} while (res);
	
	gotoxy(0, 10, 7 | 0 << 4);
	return 0;
}

