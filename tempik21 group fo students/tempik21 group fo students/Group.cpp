#include "Group.h"
#include <string>
#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;


inline void Group::setStr(char *& dest, const char * const sorce)
{
	if (dest)
		delete[] dest;
	if (sorce)
	{
		int len = strlen(sorce);
		dest = new char[len + 1];
		strcpy_s(dest, len + 1, sorce);
	}
	else
		dest = nullptr;
}


Group::Group(int newQuantity, const char* newName, const char* newSpec, short newKurs)
: quantity(newQuantity), kurs(newKurs), indexFree(0), name(nullptr), spec(nullptr)
{
	setStr(name, newName);
	setStr(spec, newSpec);
	arrStudents = new Student*[quantity];

}

Group::~Group()
{
	for (int a(0); a < indexFree; a++)
		delete arrStudents[a];
	delete[] arrStudents;
}

bool Group::addStudent(const char * const nameStudnet, const char *  const surnameStudent)  // ������� �������� �� ���� � �������
{
	if (indexFree < quantity)
	{
		arrStudents[indexFree] = new Student(nameStudnet, surnameStudent);
		indexFree++;
		return 1;
	}
	return 0;
}

bool Group::addStudent(Student * student)  // ������ �������� �� ��� ��������� �������� (��������� ��� ���������� � ���� �����)
{
	if (indexFree < quantity)
	{
		arrStudents[indexFree] = student;
		indexFree++;
		return 1;
	}
	return 0;
}

bool Group::deleteStudent(const int index) // ������� � ����� � �������� ���'��� (����� ��������)
{
	if (index < 0 || index >= indexFree)
		return 0;

	
	delete arrStudents[index];
	for (int a(index); a < indexFree; a++)
		arrStudents[a] = arrStudents[a + 1];
	indexFree--;
	return 1;
}

Student * Group::removeStudent(const int index)   // ������� ���� � ���� ����� (�� ����� ��������) � ������� ��������  -- ����. ��� ����������� � ����
{
	if (index < 0 || index >= indexFree)
		return nullptr;

	Student *t = arrStudents[index];
	for (int a(index); a < indexFree; a++)
		arrStudents[a] = arrStudents[a + 1];
	indexFree--;
	return t;
}
Student * Group::getStudent(const int index)   // ������� ����. �� �������� (��� ���� ����, ������� � �.�.)
{
	if (index < 0 || index >= indexFree)
		return nullptr;
	
	return arrStudents[index];
}

void Group::printMe()
{
	cout << "Name of group: " << (name ? name : "_null_") << endl;
	cout << "Spec: " << (spec ? spec : "_null_") << endl;
	cout << "Quantity of class: " << quantity << endl;
	cout << "Count of students: " << indexFree << endl;
	cout << "List of students:" << endl;
	for (int a(0); a < indexFree; a++)
		cout << std::setw(2) << a + 1 << ". " << arrStudents[a]->getName() << ' ' << arrStudents[a]->getSurname() << endl;
	
}

const char* Group::getName() const
{
	return name;
}