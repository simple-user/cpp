#pragma once
#include "Student.h"

class Group
{
public:
	Group(int newQuantity, const char* newName, const char* newSpec, short newKurs);
	~Group();

	bool addStudent(const char * const nameStudnet, const char *  const surnameStudent);  // створює студента по імені і прізвищу
	bool addStudent(Student * student);  // приймає вказівник на уже існуючого студента (наприклад при переведенні з іншої групи)

	bool deleteStudent(const int index); // видаляє з групи і вивільняє пам'ять (знищує студента)
	Student * removeStudent(const int index);   // видаляє лише з цієї групи (не знищує студента) і повертає вказівник  -- напр. для переведення в іншу
	Student * getStudent(const int index);   // повертає вказ. на студента (для зміни імені, прізвища і т.п.)
	void printMe();
	const char* getName() const;

private:
	Student ** arrStudents;  // масив студентів (вказівників на студентів)
	int quantity;                  // к-ть студентів у групі (місць)
	int indexFree;			// вільний ід\ндекс в масиві для додавання студента
	char * name;               // назва групи
	char* spec;                 // спеціальність
	short kurs;
	inline void setStr(char *& dest, const char * const sorce);


};