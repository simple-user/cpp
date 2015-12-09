#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <Windows.h>

using namespace std;


struct Node
{
	Node() :y(-1), n(-1) {}
	string q;
	int y;
	int n;
};


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	// setlocale(LC_ALL, ".1251");

	vector<Node> tree;
	Node n;
	n.q = "��";
	tree.push_back(n);

	int i = 0;
	int ans = 0;
	char temp[101];
	string animal, difference;
	cout << "����� ������! ������ ���� ����� ������� ��������? ����� ������� ����� ��������. ��� � ��� ��������� ����!!! �� ������� � � ������� �������!" << endl;
	cout << "������? 1-���, 2-�: ";
	cin >> ans;
	cin.get();
	if (ans == 2)
	{
		cout << "�� �� � ���� �����!" << endl;
		return 0;
	}

	while (1)
	{
		if (tree[i].n != -1 && tree[i].y != -1)
		{
			cout << tree[i].q << "? 1-���, 2-�: ";
			cin >> ans;
			if (ans == 1)
				i = tree[i].y;
			else
				i = tree[i].n;
		}
		else
		{
			cout << "�� " << tree[i].q << "? 1-���, 2-�: ";
			cin >> ans;
			cin.get();
			if (ans == 1)
				cout << "����!!!!" << endl;
			else
			{
				cout << "� ��� ��? (����� �������): ";
				cin.getline(temp,100,'\n');
				animal = temp;
				cout << "��� " << animal << " ����������� �� " << tree[i].q << ": ";
				cin.getline(temp, 100, '\n');
				difference=temp;
				Node yes;
				yes.q = animal;
				Node no;
				no.q = tree[i].q;
				tree[i].q = difference;
				tree[i].y = tree.size();
				tree.push_back(yes);
				tree[i].n = tree.size();
				tree.push_back(no);
				cout << "����� ����, �� " << animal << " " << difference << endl;
			}
			cout << "����� ��, ����� ��!!!! ���� ������� �� ��������!!!! *����� ������*" << endl;
			cout << "������ �� �����? 1-���, 2-� ";
			cin >> ans;
			if (ans == 2)
			{
				cout << "����� �� ������� ������ ��� �������� ������� ������! " << endl;
				break;
			}
			else
			{
				i = 0;
				cout << "���ﳳ!!! ����� ������� ��������. ����� ���������� ��� � ��� �� �� �������." << endl;
				cout << "�� ����� ������� ������" << endl;
				_getch();
			}
		}
	}
	
	return 0;
}

