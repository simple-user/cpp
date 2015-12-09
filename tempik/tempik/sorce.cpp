#include <iostream>
#include <iomanip>
#include <ctime>
#include "Date.h"

using namespace std;



int main()
{
        setlocale(0, "");


        Date *d1 = date_init("10", "08", "2003");
        Date *d2 = date_init2("10", "08", "2003");


        cout << "d1: ", print_date(d1); cout << endl;
        cout << "d1: ", print_date(d1, 1); cout << endl;
        cout << "d2: ", print_date(d2); cout << endl;
        cout << "d2: ", print_date(d2, 1); cout << endl;

        return 0;
}
