#include "Head.h"

static HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);





void menuResultCatch(int res, Groups &groups)
{
	char name[20];
	char surname[20];
	int index = 0;
	int index2 = 0;
	switch (res)
	{
	case 1:
		addGroup(groups);
		break;
	case 2:
		removeGroup(groups);
		break;
	case 3:
		selectGroup(groups);
		break;
	case 41:
		gotoxy(0, 10, 7);
		if (groups.activeGroup != -1)
			groups.arrGroup[groups.activeGroup]->printMe();
		else
			cout << "You didn't select a group" << endl;
		system("pause");
		system("cls");
		break;
	case 42:
		gotoxy(0, 10, 7);
		if (groups.activeGroup == -1)
			cout << "You didn't select a group" << endl;
		else
		{
			cout << "Input name: "; cin.getline(name, 19, '\n');
			cout << "Input surname"; cin.getline(surname, 19, '\n');
			groups.arrGroup[groups.activeGroup] -> addStudent(name, surname);
			cout << "OK!" << endl;
		}
		system("pause");
		system("cls");
		break;
	case 43:
		gotoxy(0, 10, 7);
		if (groups.activeGroup == -1)
			cout << "You didn't select a group" << endl;
		else
		{
			groups.arrGroup[groups.activeGroup]->printMe();
			cout << "Input index: "; cin >> index; index--; cin.get();
			if(groups.arrGroup[groups.activeGroup]->deleteStudent(index))
				cout << "OK!" << endl;
			else
				cout << "FAIL!" << endl;
		}
		system("pause");
		system("cls");
		break;
	case 44:
		gotoxy(0, 10, 7);
		if (groups.activeGroup == -1)
			cout << "You didn't select a group" << endl;
		else
		{
			groups.arrGroup[groups.activeGroup]->printMe();
			cout << "Input number of student: "; cin >> index; index--; cin.get();
			showGroupList(groups);
			cout << "Input number of group to move to: "; cin >> index2; index2--; cin.get();
			Student * st = groups.arrGroup[groups.activeGroup]->removeStudent(index);
			if (st)
			{
				groups.arrGroup[index2]->addStudent(st);
				cout << "OK!" << endl;
			}
			else
			{
				cout << "fail to get student!" << endl;
			}
		}
		system("pause");
		system("cls");
		break;
	}
}


void addGroup(Groups &groups)
{
	char groupNameT[100];
	char groupSpecT[100];
	int quantityT = 0;
	int kursT = 0;

	gotoxy(0, 10, 7 ); cout << "Input name of course: "; cin.getline(groupNameT,99,'\n');
	cout << "Input spec: "; cin.getline(groupSpecT,99,'\n');
	cout << "Input quantity: "; cin >> quantityT;
	cout << "Input kurs: "; cin >> kursT; cin.get();

	Group **g = new Group*[groups.countGroups+1];
	if (groups.arrGroup)
	{
		for (int a(0); a < groups.countGroups; a++)
			g[a] = groups.arrGroup[a];

		delete[] groups.arrGroup;
	}
	g[groups.countGroups] = new Group(quantityT, groupNameT, groupSpecT, kursT);
	groups.countGroups++;

	groups.arrGroup = g;
	
	system("pause");
	system("cls");
}

bool showGroupList(const Groups &groups)
{
	if (!groups.arrGroup)
	{
		cout << "There is no group!" << endl;
		return 0;
	}

	for (int a(0); a < groups.countGroups; a++)
		cout << a + 1 << ". " << groups.arrGroup[a]->getName() << endl;
	return 1;
}

int selectGroup(Groups &groups)
{
	int t = -1;
	gotoxy(0, 10, 7);
	if (showGroupList(groups))
	{
		cout << "Input your choice: "; cin >> t; t -= 1; cin.get();
		if (t >= 0 && t < groups.countGroups)
		{
			groups.activeGroup = t;
			cout << "OK!" << endl;
		}
		else
		{
			cout << "FAIL!" << endl;
			t = -1;
		}
	}

	system("pause");
	system("cls");

	return t;
}

void removeGroup(Groups &groups)
{
	int t = -1;
	gotoxy(0, 10, 7);
	if (showGroupList(groups))
	{
		cout << "Input your choice: "; cin >> t; t -= 1; cin.get();
		if (t >= 0 && t < groups.countGroups)
		{
			delete groups.arrGroup[t];
			for (int a(t); a < groups.countGroups - 1; a++)
				groups.arrGroup[a] = groups.arrGroup[a + 1];
			groups.countGroups--;
			if (!groups.countGroups)
				groups.arrGroup = nullptr;
			groups.activeGroup = -1;
			cout << "OK!" << endl;
			cout << "Remember that you have to choose an active group again!" << endl;
		}
		else
			cout << "FAIL!" << endl;
	}

	system("pause");
	system("cls");
}