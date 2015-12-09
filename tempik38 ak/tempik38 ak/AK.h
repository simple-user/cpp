#pragma once
#include <vector>
#include "Magazine.h"

class AK
{
public:
	AK() : pMag(nullptr) {};
	AK(Magazine *p) : pMag(p) {};
	
	struct Res
	{
		size_t num;
		bool   res;

		Res() : num(0), res(false) {}
		Res(size_t n, bool r) : num(n), res(r) {}
	};

	bool ejectMag()
	{
		if (!pMag)
			return false;
		pMag = nullptr;
		return true;
	}

	bool insertMag(Magazine *m)
	{
		if (pMag)
			return false;
		pMag = m;
		return true;
	}

	bool pif(Res &res)
	{
		if (!pMag || !(pMag->getSize()))
			return false;

		res.num = pMag->top()->getNumber();
		res.res = pMag->top()->pif();
		pMag->pop();
		return true;
	}

	bool tratata(size_t count, std::vector<Res> &vecRes)
	{
		if (!pMag || !(pMag->getSize()))
			return false;

		for (size_t a = 0; a < count && pMag->getSize(); ++a)
		{
			vecRes.emplace_back(pMag->top()->getNumber(), pMag->top()->pif());
			pMag->pop();
		}
		return true;
	}
	
private:
	Magazine *pMag;
};

