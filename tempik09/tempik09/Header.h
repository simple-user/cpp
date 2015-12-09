#include <iostream>
#include <iomanip>
#include <string>

enum Type { COOL, SOSO };

using namespace std;

class Monitor
{
private:
	Type type;
	char *manufacturer;
public:
	//con-tors
	Monitor();
	Monitor(const char* m, Type t=COOL);
	
	//copy c-tor
	Monitor(const Monitor& m);
	
	//move c-tor
	Monitor(Monitor&& m);

	// =
	//Monitor& operator=(const Monitor& m) - ���� ��������������� Monitor(const Monitor& m) ��� Monitor& operator=(Monitor m)
	//Monitor& operator=(Monitor&& m) - ���� ��������������� Monitor(Monitor&& m) ��� Monitor& operator=(Monitor m)
	Monitor& operator=(Monitor m);

	// print
	friend ostream& operator<<(ostream& os, Monitor& m);
	void printInf() const;

	void setType(const Type t);
	void setManufacturer(const char* m);

	Type getType() const;
	const char* getManufacturer() const;

	// ���������� �������� =
	const Monitor& returnMeLink() const;
	Monitor  returnMeValue() const; /// ???? �� ����� �� ��������...


	//d-tor
	~Monitor();
};