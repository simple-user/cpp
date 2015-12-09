#include "Drob.h"



Drob::Drob(int a, int b) : A(a), B(b)
{
	if (!b)
		exit(1);
	else if (b < 0)
	{
		B *= -1;
		A *= -1; 
	}
	sprost();
}

Drob::Drob(double a)
{
	if (floor(a) == a)
	{
		A = a;
		B = 1;
		return;
	}
	else
	{
		int k = 100000;
		if (a>0)
			A = (a + 5e-08) * k;
		else
			A = (a - 5e-08) * k;

		B = k;
		
	}
	sprost();
}


ostream& operator<<(ostream &os, const Drob &d)
{
	if (d.B == 1)
		os << d.A;
	else if (d.A > d.B )
		os << d.A / d.B << "(" << d.A % d.B << "/" << d.B << ")";
	else if (d.A < d.B && d.A < 0)
		os << d.A / d.B << "(" << d.A % d.B * -1 << "/" << d.B << ")";
	else
		os << d.A << "/" << d.B;

	return os;
}

Drob Drob::operator+(const Drob &d) const
{
	Drob res;
	if (B == d.B)
	{
		res.A = A + d.A;
		res.B = B;
	}
	else
	{
		res.A = A*d.B + d.A*B;
		res.B = B*d.B;
	}
	res.sprost();
	return res;
}
Drob Drob::operator+(const int i) const
{
	Drob res;
	if (B == 1)
	{
		res.A = A + i;
		res.B = 1;
	}
	else
	{
		res.A = i*B + A;
		res.B = B;
	}
	res.sprost();
	return res;
}
Drob operator+(const int i, const Drob &d) 
{
	Drob res;
	if (d.B == 1)
	{
		res.A = d.A + i;
		res.B = 1;
	}
	else
	{
		res.A = d.B * i + d.A;
		res.B = d.B;
	}
	res.sprost();
	return res;
}

Drob Drob::operator-(const Drob &d) const
{
	Drob res;
	if (B == d.B)
	{
		res.A = A - d.A;
		res.B = B;
	}
	else
	{
		res.A = A*d.B - d.A*B;
		res.B = B*d.B;
	}
	res.sprost();
	return res;
}
Drob Drob::operator-(const int i) const
{
	Drob res;
	if (B == 1)
	{
		res.A = A - i;
		res.B = 1;
	}
	else
	{
		res.A = A - i * B;
		res.B = B;
	}
	res.sprost();
	return res;
}
Drob operator-(const int i, const Drob &d) 
{
	Drob res;
	if (d.B == 1)
	{
		res.A = i - d.A;
		res.B = 1;
	}
	else
	{
		res.A = i * d.B - d.A;
		res.B = d.B;
	}
	res.sprost();
	return res;
}

Drob Drob::operator*(const Drob &d) const
{
	Drob res;
	res.A = A*d.A;
	res.B = B*d.B;
	res.sprost();
	return res;
}
Drob Drob::operator*(const int i) const
{
	Drob res;
	res.A = A*i;
	res.B = B;
	res.sprost();
	return res;
}
Drob operator*(const int i, const Drob &d)
{
	Drob res;
	res.A = i * d.A;
	res.B = d.B;
	res.sprost();
	return res;
}

Drob Drob::operator/(const Drob &d) const
{
	Drob res;
	if (d.A == 0)
	{
		res = *this;
	}
	else
	{
		res.A = A*d.B;
		res.B = B*d.A;
		res.sprost();
	}
	return res;
}
Drob Drob::operator/(const int i) const
{
	Drob res;
	if (i == 0)
	{
		res = *this;
	}
	else
	{
		res.A = A;
		res.B = B*i;
		res.sprost();
	}
	return res;
}
Drob operator/(const int i, const Drob &d)
{
	Drob res;
	if (d.A == 0)
	{
		res.A = i;
		res.B = 1;
	}
	else
	{
		res.A = i*d.B;
		res.B = d.A;
		res.sprost();
	}
	return res;
}

Drob& Drob::operator++()
{
	A = 1*B + A;
	sprost();
	return *this;
}
Drob Drob::operator++(int opa)
{
	Drob t = *this;
	A = 1*B+A;
	sprost();
	return t;
}

Drob& Drob::operator--()
{
	A = 1*B - A;
	sprost();
	return *this;
}
Drob Drob::operator--(int opa)
{
	Drob t = *this;
	A = 1*B - A;
	sprost();
	return *this;
}

Drob::operator int()
{
	return A / B;
}

Drob::operator double()
{
	return (double)A / B;
}



void Drob::sprost()
{
	int a1 = abs(A), b1 = abs(B);
	int min = a1 > b1 ? b1 : a1;
	int max = a1 > B ? a1 : b1;
	
	for (int a = min; a > 0; a--)
		if (max%a == 0 && min%a == 0)
		{
			A /= a;
			B /= a;
			break;
		}

	if (B < 0) // про всяк випадок :)
	{
		B *= -1;
		A *= -1;
	}
	
}
