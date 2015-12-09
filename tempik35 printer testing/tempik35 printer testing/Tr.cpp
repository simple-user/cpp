#include "Tr.h"

static const char* owners2[7] = { "BOSS", "BOOKER", "CLERK", "STUDENT", "PUPIL", "CHILD", "BABY" };
static const char* docType[4] = { "small doc", "Millde doc", "Big doc", "Foto" };

void tr1_printer(Printer & pr)
{
	pr.print();
}

void tr2_add_queue(std::priority_queue<Document> & spooler)
{
	int size = 0;
	Owner o = BOSS;
	std::string name;
	Sleep(4000);
	for (int a(0); a < 5; a++)
	{
		name = std::string("Doc") + std::to_string(a + 1);
		size = rand() % 3 + 3;
		o = Owner(rand() % 6);

		gtoxy(40, 10 + a, 7);
		std::cout << "Add doc: \"" << name << "\" size: " << size << " by " << owners2[o];
		spooler.push(Document(name, size, o));
		Sleep(4000);
	}
}

void menuInit(Menu &m)
{
	m.addPunkt(0, "1. BOSS printing    >>>");
	m.addMenu(1);
	m.addPunkt(1, "1. Small document (1-3 sec.)");
	m.addPunkt(1, "1. Millde document (3 - 5 sec.)");
	m.addPunkt(1, "1. Big document (5-8 sec.)");
	m.addPunkt(1, "1. Foto (10 sec.)");

	m.addPunkt(0, "2. BOOKER printing  >>>");
	m.addMenu(2);
	m.addPunkt(2, "1. Small document (1-3 sec.)");
	m.addPunkt(2, "1. Millde document (3 - 5 sec.)");
	m.addPunkt(2, "1. Big document (5-8 sec.)");
	m.addPunkt(2, "1. Foto (10 sec.)");

	m.addPunkt(0, "3. CLERK printing   >>>");
	m.addMenu(3);
	m.addPunkt(3, "1. Small document (1-3 sec.)");
	m.addPunkt(3, "1. Millde document (3 - 5 sec.)");
	m.addPunkt(3, "1. Big document (5-8 sec.)");
	m.addPunkt(3, "1. Foto (10 sec.)");

	m.addPunkt(0, "4. STUDENT printing >>>");
	m.addMenu(4);
	m.addPunkt(4, "1. Small document (1-3 sec.)");
	m.addPunkt(4, "1. Millde document (3 - 5 sec.)");
	m.addPunkt(4, "1. Big document (5-8 sec.)");
	m.addPunkt(4, "1. Foto (10 sec.)");

	m.addPunkt(0, "5. PUPIL printing   >>>");
	m.addMenu(5);
	m.addPunkt(5, "1. Small document (1-3 sec.)");
	m.addPunkt(5, "1. Millde document (3 - 5 sec.)");
	m.addPunkt(5, "1. Big document (5-8 sec.)");
	m.addPunkt(5, "1. Foto (10 sec.)");

	m.addPunkt(0, "6. CHILD printing   >>>");
	m.addMenu(6);
	m.addPunkt(6, "1. Small document (1-3 sec.)");
	m.addPunkt(6, "1. Millde document (3 - 5 sec.)");
	m.addPunkt(6, "1. Big document (5-8 sec.)");
	m.addPunkt(6, "1. Foto (10 sec.)");

	m.addPunkt(0, "7. BABY printing    >>>");
	m.addMenu(7);
	m.addPunkt(7, "1. Small document (1-3 sec.)");
	m.addPunkt(7, "1. Millde document (3 - 5 sec.)");
	m.addPunkt(7, "1. Big document (5-8 sec.)");
	m.addPunkt(7, "1. Foto (10 sec.)");
}

void resultMenuCatch(int res, std::priority_queue<Document> & spooler, int &nom, std::mutex &mu)
{

	if (!res)
		return;

	Owner o = Owner(res / 10 - 1);
	size_t size0 = res % 10 - 1;
	size_t size1 = 0;
	switch (size0)
	{
	case 0: size1 = rand() % 3 + 1; break;
	case 1: size1 = rand() % 2 + 3; break;
	case 2: size1 = rand() % 3 + 5; break;
	case 3: size1 = 10; break;
	}

	mu.lock();
	gtoxy(40, 10 + nom, 7);
	std::cout << "Add: \"" << docType[size0] << "\" size: " << size1 << " by " << owners2[o];
	mu.unlock();
	spooler.push(Document(docType[size0], size1, o));
	nom++;
}



void tr2_add_queue_menu(Menu &m, std::priority_queue<Document> & spooler, int & nom, std::mutex &mu)
{
	int menuRes = 0;
	
	menuInit(m);

	do
	{
		menuRes = m.runMenu();
		resultMenuCatch(menuRes, spooler, nom,mu);
		mu.lock();
		gtoxy(0, 0, 80, 10, 7);
		mu.unlock();
	} while (menuRes);
	
}
