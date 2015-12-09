#pragma once
#include "Student.h"

class Group
{
public:
	Group(int newQuantity, const char* newName, const char* newSpec, short newKurs);
	~Group();

	bool addStudent(const char * const nameStudnet, const char *  const surnameStudent);  // ������� �������� �� ���� � �������
	bool addStudent(Student * student);  // ������ �������� �� ��� ��������� �������� (��������� ��� ���������� � ���� �����)

	bool deleteStudent(const int index); // ������� � ����� � �������� ���'��� (����� ��������)
	Student * removeStudent(const int index);   // ������� ���� � ���� ����� (�� ����� ��������) � ������� ��������  -- ����. ��� ����������� � ����
	Student * getStudent(const int index);   // ������� ����. �� �������� (��� ���� ����, ������� � �.�.)
	void printMe();
	const char* getName() const;

private:
	Student ** arrStudents;  // ����� �������� (��������� �� ��������)
	int quantity;                  // �-�� �������� � ���� (����)
	int indexFree;			// ������ ��\����� � ����� ��� ��������� ��������
	char * name;               // ����� �����
	char* spec;                 // ������������
	short kurs;
	inline void setStr(char *& dest, const char * const sorce);


};