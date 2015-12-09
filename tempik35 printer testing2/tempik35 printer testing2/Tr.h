#include "Printer.h"
#include "ConManip.h"
#include "Document.h"
#include "Menu.h"
#include <queue>
#include <Windows.h>
#include <string>
#include <mutex>


void tr1_printer(Printer & pr);
void tr2_add_queue(MyPriorityQueue<Document> & spooler);
void tr2_add_queue_menu(Menu &m, MyPriorityQueue<Document> & spooler, std::mutex &mu);

void menuInit(Menu &m);
void resultMenuCatch(int res, MyPriorityQueue<Document> & spooler, std::mutex &mu);
void printSpooler(MyPriorityQueue<Document> & spooler, std::mutex &mu);
