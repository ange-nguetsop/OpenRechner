#include <iostream>
#include <stdio.h>
#include <stdbool.h>
#include <limits>
#include "OpenFraction.h"
#pragma warning (disable: 4996)
using namespace std;



void OpenFraction::ausgabe()
{
	if (n < 0 || z < 0)
	{
		if (n == 1)
			printf("%i\n", z);
		else if ((z > 0 && n < 0) || (z < 0 && n < 0))
			printf("%i/%i\n", (-1) * z, (-1) * n);
		else
			printf("%i/%i\n", z, n);
	}
	else
	{
		if (n == 1)
			printf("%i\n", z);
		else
			printf("%i/%i\n", z, n);
	}
}

bool OpenFraction:: isInteger(double number) {
	int integerPart = static_cast<int>(number);
	double fractionPart = integerPart - number;
	if (fractionPart == 0.0) return true;
	else
		return false;
}

int ggt(int x, int y)
{
	if (y == 0)
		if (x == 0)
			return 1; // der ggt von 0 und 0 ist 1 (per Def.)
		else
			return x;
	else
		return ggt(y, (x % y));
}

OpenFraction OpenFraction::to_frac(double value, double tolerance)
{
	int i = 1;
	double post_value = value;
	const int maxIterations = 1000; // Limite pour éviter une boucle infinie

	while (i <= maxIterations) {
		post_value = value;
		value = value * 10;
		i++;
		if (value > INT_MAX || value < INT_MIN)
		{
			value = post_value;
			i -= 1;
			break;
		}

		if (isInteger(value))
			break;
	}

	int t = ggt(static_cast<int>(value), static_cast<int>(std::pow(10, i - 1)));
	int z = static_cast<int>(value) / t;
	int n = static_cast<int>(std::pow(10, i - 1)) / t;
	return OpenFraction(z, n);
}

ostream& operator<<(ostream& out, OpenFraction& frac)
{
	if (frac.n < 0 || frac.z < 0)
	{
		if (frac.n == 1)
			out << frac.z;
		else if ((frac.z > 0 && frac.n < 0) || (frac.z < 0 && frac.n < 0))
			out << (-1) * frac.z << "/" << (-1) * frac.n;
		else
			out << frac.z << "/" << frac.n;
	}
	else
	{
		if (frac.n == 1)
			out << frac.z;
		else
			out << frac.z << "/" << frac.n;
	}
	
	return out;
}

OpenFraction:: OpenFraction()
{
	z = 0; n = 1;
}

OpenFraction::OpenFraction(int zz)
{
	z = zz;
	n = 1; 
}

OpenFraction::OpenFraction(int zz, int nn)
{
	z = zz; 
	n = nn;
}

OpenFraction:: ~OpenFraction() {}

OpenFraction operator+(OpenFraction r1, OpenFraction r2)
{
	OpenFraction res = { 0,0 };
	int t = 0;
	res.z = (r1.z * r2.n) + (r2.z * r1.n);
	res.n = (r1.n * r2.n);
	t = ggt(res.z, res.n);
	res.z = res.z / t;
	res.n = res.n / t;
	return res;
}

OpenFraction operator-(OpenFraction r1, OpenFraction r2)
{
	OpenFraction res = { 0,0 };
	int t = 0;
	res.z = (r1.z * r2.n) - (r2.z * r1.n);
	res.n = (r1.n * r2.n);
	t = ggt(res.z, res.n);
	res.z = res.z / t;
	res.n = res.n / t;
	return res;
}

OpenFraction operator*(OpenFraction r1, OpenFraction r2)
{
	OpenFraction res = { 0,0 };
	int t = 0;
	res.z = r1.z * r2.z;
	res.n = r1.n * r2.n;
	t = ggt(res.z, res.n);
	res.z = res.z / t;
	res.n = res.n / t;
	return res;
}

OpenFraction operator/(OpenFraction r1, OpenFraction r2)
{
	OpenFraction res = { 0,0 };
	int t = 0;
	res.z = r1.z * r2.n;
	res.n = r1.n * r2.z;
	t = ggt(res.z, res.n);
	res.z = res.z / t;
	res.n = res.n / t;
	return res;
}

OpenFraction& OpenFraction::operator+=(const OpenFraction& f)
{
	this->z = this->z * f.n + this->n * f.z;
	this->n = this->n * f.n;
	int t = ggt(this->z, this->n);
	this->z = this->z / t;
	this->n = this->n / t;

	return *this;
}

OpenFraction& OpenFraction::operator-=(const OpenFraction& f)
{
	this->z = this->z * f.n - this->n * f.z;
	this->n = this->n * f.n;
	int t = ggt(this->z, this->n);
	this->z = this->z / t;
	this->n = this->n / t;

	return *this;
}

OpenFraction& OpenFraction::operator*=(const OpenFraction& f)
{
	this->z = this->z * f.z;
	this->n = this->n * f.n;
	int t = ggt(this->z, this->n);
	this->z = this->z / t;
	this->n = this->n / t;

	return *this;
}

OpenFraction& OpenFraction::operator/=(const OpenFraction& f)
{
	this->z = this->z * f.n;
	this->n = this->n * f.z;
	int t = ggt(this->z, this->n);
	this->z = this->z / t;
	this->n = this->n / t;

	return *this;
}

OpenFraction& OpenFraction::operator++()
{
	this->z = this->z + this->n;
	return *this;
}

OpenFraction& OpenFraction::operator--()
{
	this->z = this->z - this->n;
	return *this;
}

bool OpenFraction::operator==(const OpenFraction& f)
{
	if (this->z == f.z && this->n == f.n) return true;
	else
		return false;
}

bool OpenFraction::operator!=(const OpenFraction& f)
{
	if (this->z != f.z || this->n != f.n) return true;
	else
		return false;
}

