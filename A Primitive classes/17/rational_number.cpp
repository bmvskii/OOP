// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "rational_number.hpp"
#include <stdexcept>


RationalNumber::RationalNumber(int _Numerator,int _Denominator)
{
	int min = 1;
	bool minus = false;

	if (_Denominator == 0) throw std::logic_error("Zero denominator");
	
	if (_Denominator < 0 || _Numerator < 0) minus = true;
	if (_Denominator < 0 && _Numerator < 0) minus = false;
	Numerator = std::abs(_Numerator);
	Denominator = std::abs(_Denominator);

	for (int i = 1; i < Numerator + 1; i++)
		if (Numerator % i == 0 && Denominator % i == 0 && i != 1) min = i;

	while (Numerator % min == 0 && Denominator % min == 0)
	{
		if (min == 1) break;
		Numerator /= min;
		Denominator /= min;
	}
	if (minus) Numerator = -Numerator;
}

void RationalNumber::operator *= (const RationalNumber & _Numeratorber)
{
	int min = 1;
	Numerator *= _Numeratorber.Numerator;
	Denominator *= _Numeratorber.Denominator;
	
	for (int i = 1; i < Numerator + 1; i++)
		if (Numerator % i == 0 && Denominator % i == 0 && i != 1)
			min = i;

	while (Numerator % min == 0 && Denominator % min == 0)
	{
		if (min == 1) break;
		Numerator /= min;
		Denominator /= min;
	}
}

void RationalNumber::operator += (const RationalNumber & _Numeratorber)
{
	int most = getGCD(Denominator, _Numeratorber.Denominator);
	int right_n = _Numeratorber.Numerator * (most / _Numeratorber.Denominator);
	int min = 1;

	Numerator *= (most / Denominator);
	Numerator += right_n;
	Denominator = most;

	for (int i = 1; i < Numerator + 1; i++)
		if (Numerator % i == 0 && Denominator % i == 0 && i != 1) min = i;

	while (Numerator % min == 0 && Denominator % min == 0)
	{
		if (min == 1) break;
		Numerator /= min;
		Denominator /= min;
	}
}

void RationalNumber::operator -= (const RationalNumber & _Numeratorber)
{
	int most = getGCD(Denominator, _Numeratorber.Denominator);
	int right_n = _Numeratorber.Numerator * (most / _Numeratorber.Denominator);
	int min = 1;

	Numerator *= (most / Denominator);
	if (Numerator - right_n == 0)
	{
		Denominator = 1;
		Numerator = 0;
	}
	Numerator -= right_n;
	Denominator = most;
	for (int i = 1; i < Numerator + 1; i++)
		if (Numerator % i == 0 && Denominator % i == 0 && i != 1) min = i;

	while (Numerator % min == 0 && Denominator % min == 0)
	{
		if (min == 1) break;
		Numerator /= min;
		Denominator /= min;
	}
}

RationalNumber RationalNumber::operator - (const RationalNumber & _Numeratorber)
{
	int most = getGCD(Denominator, _Numeratorber.Denominator);
	int left_n = Numerator * (most / Denominator);
	int right_n = _Numeratorber.Numerator * (most / _Numeratorber.Denominator);
	if (left_n - right_n == 0) 
		return RationalNumber(0, 1);
	return RationalNumber(left_n - right_n, most);
}


void RationalNumber::operator /= (const RationalNumber & _Numeratorber)
{
	Numerator *= _Numeratorber.Denominator;
	Denominator *= _Numeratorber.Numerator;

	int min = 1;
	for (int i = 1; i < Numerator + 1; i++)
		if (Numerator % i == 0 && Denominator % i == 0 && i != 1) min = i;

	while (Numerator % min == 0 && Denominator % min == 0)
	{
		if (min == 1) break;
		Numerator /= min;
		Denominator /= min;
	}
}

int RationalNumber::getGCD(int _l, int _Numeratorber)
{
	if (_l == _Numeratorber) return _l;
	int getGCD = _l * _Numeratorber;
	int min = 0;
	for (int i = getGCD; i >= 1; i--)if (i % _l == 0 && i % _Numeratorber == 0) min = i;
	return min;
}