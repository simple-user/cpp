#pragma once
class Student
{
public:
	Student(const char * const newName, const char * const newSurname);
	~Student();

	void setName(const char * const newName);
	void setSurname(const char * const newSurname);

	const char * const getName() const;
	const char * const getSurname() const;

private:
	char * name;
	char * surname;
	inline void setStr(char *& dest, const char * const sorce);
	Student(const Student&);
	Student& operator=(const Student&);
};