#include "Printer.h"
#include "ConManip.h"
#include "Document.h"
#include "Menu.h"
#include <queue>
#include <Windows.h>
#include <string>


void tr1_printer(Printer & pr);
void tr2_add_queue(std::priority_queue<Document> & spooler);
void tr2_add_queue_menu(Menu &m, std::priority_queue<Document> & spooler, int &nom);

void menuInit(Menu &m);
void resultMenuCatch(int res, std::priority_queue<Document> & spooler, int &nom);
