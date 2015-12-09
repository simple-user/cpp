#include "Inversion.h"

const HANDLE Inversion::hand = GetStdHandle(STD_OUTPUT_HANDLE);

Inversion::Inversion(string fName) : fileName(fName), countWords(0)
{
	std::fstream f(fileName, std::ios::in | std::ios::out);
	if (!f.is_open())
		std::ofstream f(fileName, std::ios::out);
	else
	{
		char sline[80];
		my strLine;
		size_t pos = 0;
		f.seekg(0, std::ios::beg);
		f.seekp(0, std::ios::beg);
		
		while (!f.eof())
		{
			if (f.get() == '\n')
				++countWords;
		}
		
		f.close();
		f.open(fileName, std::ios::in | std::ios::out);
		f.seekg(0);
		f.seekp(0);

		size_t count = 0;

		SetConsoleCursorPosition(hand, { 0, 0 });
		cout << "Loading file: \n";

		SetConsoleCursorPosition(hand, { 5, 1 });
		for (size_t a = 0; a < 20; ++a)
			cout << '-';

		size_t counterOld = 0;
		while (!f.eof())
		{
			++count;
			
			if (count * 100 / countWords > counterOld)
			{
				++counterOld;
				SetConsoleCursorPosition(hand, { 0, 1 });
				cout << counterOld-1 << '%';
				SetConsoleCursorPosition(hand, { 5 + (count * 20 / countWords), 1 });
				cout << 'x' << endl;
			}
			// if (count % 1000 == 0) std::cout << count << std::endl;
			
			f.getline(sline, 79, '\n');
			sline[79] = '\0';
			strLine = sline;
			if ((pos = strLine.find_first_not_of("àáâãäåºæçè³¿éêëìíîïðñòóôõö÷øùüåþÿ", 0)) != string::npos || !strLine.size())
				continue; // ÿêùî ÿêèéñü áàã - òóïî ³ãíîðèìî :)
			dic.insert(strLine);
		}
		SetConsoleCursorPosition(hand, { 0, 1 });
		cout << "100% ";
		for (size_t a = 0; a < 20; ++a)
			cout << 'x';
		cout << endl;
		cout << "File loaded! (count of words: " << countWords << ")" << endl;

	}
	f.close();
};

//void Inversion::testik(size_t countLet, size_t countFinded)
//{
//	for (auto a : dic)
//	{
//		a.countCharsComp = countLet;
//		vec<my> arrVec;
//		find(a, arrVec);
//		if (arrVec.size() > countFinded)
//		{
//			cout << "results for: " << a << endl;
//			for (auto &b : arrVec)
//				cout << b << endl;
//			cout << "-----------------------" << endl;
//		}
//	}
//}

Inversion::~Inversion()
{
	size_t count = 0;
	std::ofstream f(fileName, std::ios::out);
	f.seekp(0, std::ios::beg);
	size_t counterOld = 0;
	system("cls");

	SetConsoleCursorPosition(hand, { 0, 0 });
	cout << "Saving file: \n";

	for (const auto &a : dic)
	{
		// çàïèñóºìî çíà÷åííÿ
		++count;

		if (count * 100 / countWords > counterOld)
		{
			++counterOld;
			SetConsoleCursorPosition(hand, { 0, 1 });
			cout << counterOld - 1 << "% ";
			for (size_t a = 0; a < count * 20 / countWords; ++a)
				cout << 'x';
			cout << endl;
		}
		
		// if (count % 1000 == 0) std::cout << count << std::endl;

		for (size_t b = 0; b < a.size(); ++b)
			f.put(a[b]);
		f.put('\n');
	}
	SetConsoleCursorPosition(hand, { 0, 1 });
	cout << "100% ";
	for (size_t a = 0; a < 20; ++a)
		cout << 'x';
	cout << endl;
	cout << "File saved! (count of words: " << countWords << ")" << endl;
}

void Inversion::push(string s)
{
	size_t pos = 0;
	std::transform(s.begin(), s.end(), s.begin(), tolower);
	if ((pos = s.find_first_not_of("àáâãäåºæçè³¿éêëìíîïðñòóôõö÷øùüåþÿ", 0)) != string::npos)
		throw std::logic_error(string("wrong symbol") + s[pos]);

	dic.insert(std::move(s));
}

bool Inversion::find(my m, vec<my> &arrVec)
{
	if (m.getCountCharsComp() > m.size())
		return false;
	
	set<my, myComp>::const_iterator citSet = dic.find(m);

	if (citSet == dic.cend() || !(*citSet == m))
		return false;

	while (citSet != dic.cbegin())
	{
		if (*citSet == m)
			--citSet;
		else
		{
			++citSet;
			break;
		}
	}


	while (citSet != dic.end() && *citSet == m)
	{
		arrVec.push_back(*citSet);
		++citSet;
	}
	return true;
}