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
	n.q = "кіт";
	tree.push_back(n);

	int i = 0;
	int ans = 0;
	char temp[101];
	string animal, difference;
	cout << "привіт матусю! навчиш мене нових цікавих словечок? давай сьогодні вчити тваринок. але я вже одненньку знаю!!! ти загадай а я спробую вгадати!" << endl;
	cout << "поїхали? 1-так, 2-ні: ";
	cin >> ans;
	cin.get();
	if (ans == 2)
	{
		cout << "от же ж гімно нахрін!" << endl;
		return 0;
	}

	while (1)
	{
		if (tree[i].n != -1 && tree[i].y != -1)
		{
			cout << tree[i].q << "? 1-так, 2-ні: ";
			cin >> ans;
			if (ans == 1)
				i = tree[i].y;
			else
				i = tree[i].n;
		}
		else
		{
			cout << "це " << tree[i].q << "? 1-так, 2-ні: ";
			cin >> ans;
			cin.get();
			if (ans == 1)
				cout << "Юпппі!!!!" << endl;
			else
			{
				cout << "а хто це? (назва тварини): ";
				cin.getline(temp,100,'\n');
				animal = temp;
				cout << "чим " << animal << " відрізняється від " << tree[i].q << ": ";
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
				cout << "Тепер знаю, що " << animal << " " << difference << endl;
			}
			cout << "давай ще, давай ще!!!! хочу вивчити ще тваринок!!!! *дригає ніжками*" << endl;
			cout << "поїхали ще разок? 1-так, 2-ні ";
			cin >> ans;
			if (ans == 2)
			{
				cout << "Ладно на сьогодні досить піду рідстрелю якогось гімнюка! " << endl;
				break;
			}
			else
			{
				i = 0;
				cout << "Юпппіі!!! знову загадай тваринку. можеш спробувати вже з тих що ми вивчили." << endl;
				cout << "як будеш готовий тицьни" << endl;
				_getch();
			}
		}
	}
	
	return 0;
}

