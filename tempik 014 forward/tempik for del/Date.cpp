#include "Date.h"


Date* date_init(char* d, char* m, char* y)
{
	int t = 0, nd, nm, ny;
	bool dd29 = 0;

	if ((t = atoi(y)) && t > 1900 && t < 2050)
		ny = t;
	else
	{
		cout << "Problems with convertation year" << endl;
		return nullptr;
	}

	if ((t = atoi(m)) && t > 0 && t < 13)
		nm = t;
	else
	{
		cout << "Problems with convertation month" << endl;
		return nullptr;
	}

	if ((ny % 4 == 0 && ny % 100 != 0) || ny % 400 == 0)
		dd29 = 1;
	
	nd = 0;
	if (nm == 2)
	{
		if (dd29 && (t = atoi(d)) && t > 0 && t < 30)
			nd = t;
		else if (!dd29 && (t = atoi(d)) && t>0 && t < 29)
			nd = t;
	}
	else if (nm < 8)
	{
		if ((t = atoi(d)) && nm % 2 && t >0 && t < 32)
			nd = t;
		else if ((t = atoi(d)) && !(nm % 2) && t >0 && t < 31)
			nd = t;
	}
	else // nm>=8
	{
		if ((t = atoi(d)) && nm % 2 && t >0 && t < 31)
			nd = t;
		else if ((t = atoi(d)) && !(nm % 2) && t >0 && t < 32)
			nd = t;
	}

	if (!nd)
	{
		cout << "Problems with convertation day" << endl;
		return nullptr;
	}

	Date *date = new Date;
	date->day = nd;
	date->month = nm;
	date->year = ny;
	return date;

}

//date_init2 аналог date_init 
//трохи оптимізованіший (але менш зрозумілий) код аналізу правильності вводу дня.
Date* date_init2(char* d, char* m, char* y)
{
	int t=0, nd,nm,ny;
	bool dd29 = 0;
	
	if ((t = atoi(y)) && t > 1900 && t < 2050)
		ny = t;
	else
	{
		cout << "Problems with convertation year" << endl;
		return nullptr;
	}

	if ((t = atoi(m)) && t > 0 && t < 13)
		nm = t;
	else
	{
		cout << "Problems with convertation month" << endl;
		return nullptr;
	}
	
	if ((ny % 4 == 0 && ny % 100 != 0) || ny % 400 == 0)
		dd29 = 1;
	
	nd = 0;
	if (nm == 2 && ((t = atoi(d)) && t > 0 && t < (29 + dd29)))
		nd = t;
	else if (nm < 8 && ((t = atoi(d)) && t >0 && t < (31 + (nm % 2))))
		nd = t;
	else if (nm > 8 && ((t = atoi(d)) && t >0 && t < (32 - (nm % 2))))
		nd = t;

	if (!nd)
	{
		cout << "Problems with convertation day" << endl;
		return nullptr;
	}
	
	Date *date = new Date;
	date->day = nd;
	date->month = nm;
	date->year = ny;
	return date;

}

Date* date_init(char* d, char* delim)
{
	char *t[3];
	char *t2 = nullptr;
	char td[12];
	strcpy_s(td, 12, d);
	t[0] = strtok_s(td, delim, &t2);
	t[1] = strtok_s('\0', delim, &t2);
	t[2] = strtok_s('\0', delim, &t2);
	if (t[0] && t[1] && t[2])
		return date_init(t[0], t[1], t[2]);
	else
		return nullptr;
}



void print_date(const Date* d, bool big)
{
	char *mb[] = { "сiчня", "лютого", "березня", "квiтня", "травня", "червня", "липня", "серпня", "вересня", "жовтня", "листопада", "грудня" };

	if (d)
		if (!big)
			cout << setw(2) << setfill('0') << d->day << '.' << setw(2) << setfill('0') << d->month << '.' << d->year;
		else
			cout << setw(2) << setfill('0') << d->day << ' ' << mb[d->month - 1] << ' ' << d->year;
	else
		cout << "NULL!";
}

int date_compare(const Date* d1, const Date* d2)
{
	if (!d1 || !d2)
		return -2; // :) 
	
	if (d1->year != d2->year)
		return d1->year > d2->year ? 1 : -1;
	else if (d1->month != d2->month)
		return d1->month > d2->month ? 1 : -1;
	else if (d1->day != d2->day)
		return d1->day > d2->day ? 1 : -1;
	else
		return 0;
}


char* day_of_week(const Date * date)
{
	if (!date)
		return "NULL";
	
	char *weekday[] = {"недiля", "понедiлок", "вiвторок", "середа", "четвер", "п\'ятниця", "субота", "недiля"};
	int a = (14 - date->month) / 12;
	int y = date->year - a;
	int m = date->month + 12 * a - 2;
	return weekday[(7000 + (date->day + y + y / 4 - y / 100 + y / 400 + (31 * m) / 12)) % 7];
}
