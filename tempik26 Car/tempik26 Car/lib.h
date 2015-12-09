#pragma once
#include "Odometr.h"

bool odInit(Odometr *&od);
void goOneKm(Odometr *od);
void goXKm(Odometr *od);
void putOneLiter(Odometr *od);
void putXLiters(Odometr *od);
void printInfa(Odometr *od);

void goKM(Odometr *od, int km);
void putLiter(Odometr *od, int l);