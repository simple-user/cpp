#pragma once
#include "Menu.h"
#include "Group.h"
#include "Student.h"

struct Groups
{
	Group **arrGroup;
	int countGroups;
	int activeGroup;
};

void menuResultCatch(int res, Groups &groups);
void addGroup(Groups &groups);
bool showGroupList(const Groups &groups);
int selectGroup(Groups &groups);
void removeGroup(Groups &groups);
void showGroup(const Groups groups, int index);


template <typename T>
bool addElementToDoublePointArr(T **&arr, int &len) 
{
	len++;
	T** temp = new T*[len];
	for (int a(0); a < len; a++)
	{
		*(temp + a) = *(arr + a);
	}
	delete[] arr;
	arr = temp;
	
}




