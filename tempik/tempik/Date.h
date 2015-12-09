#include <iostream>
#include <iomanip>
using namespace std;



struct Date
{
        int day;
        int month;
        int year;
};

Date* date_init(char *day, char *month, char *year);
Date* date_init2(char *day, char *month, char *year); //date_init2 аналог date_init2 із трохи оптимізованішим але менш зрозумілим кодом
Date* date_init(char* date, char* delimiter);

void print_date(const Date *date, bool wide_month=0);
int date_compare(const Date* date1, const Date* date2);
char *day_of_week(const Date* date);