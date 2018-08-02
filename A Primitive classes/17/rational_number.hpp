// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _RATIONAL_NUMBER_HPP_
#define _RATIONAL_NUMBER_HPP_

#include <iostream>

class RationalNumber
{
	int getGCD(int _l, int _number);

	int Numerator;
	int Denominator;

public:

	RationalNumber(int _Numerator,int _Denominator);
	~RationalNumber() = default;

	int getNumerator() const
	{
		return Numerator;
	}
	int getDenominator() const
	{
		return Denominator;
	}
	bool operator == (const RationalNumber & _number)
	{
		return Numerator == _number.Numerator && Denominator == _number.Denominator;
	}
	bool operator != (const RationalNumber & _number)
	{
		return !(*this == _number);
	}
	bool operator >= (const RationalNumber & _number)
	{
		return (double) *this >= (double)_number;

	}
	bool operator <= (const RationalNumber & _number)
	{
		return (double) *this <= (double)_number;
	}
	bool operator > (const RationalNumber & _number)
	{
		return (double) *this > (double)_number;
	}
	bool operator < (const RationalNumber & _number)
	{
		return (double) *this < (double)_number;
	}
	RationalNumber operator * (const RationalNumber & _number)
	{
		return RationalNumber(Numerator * _number.Numerator, Denominator * _number.Denominator);
	}
	RationalNumber operator + (const RationalNumber & _number)
	{
		int most = getGCD(Denominator, _number.Denominator);
		int left_n = Numerator * (most / Denominator);
		int right_n = _number.Numerator * (most / _number.Denominator);

		return RationalNumber(left_n + right_n, most);
	}
	RationalNumber operator / (const RationalNumber & _number) 
	{

		int numerator = Numerator * _number.Denominator;
		int denominator = Denominator *_number.Numerator;

		return RationalNumber(numerator, denominator);
	}
	operator double() const
	{
		return (double)Numerator / (double)Denominator;
	}
	friend std::ostream & operator << (std::ostream & _stream, const RationalNumber & _number)
	{
		_stream << _number.Numerator << "/" << _number.Denominator;
		return _stream;
	}
	void operator *= (const RationalNumber & _number);
	void operator += (const RationalNumber & _number);
	void operator -= (const RationalNumber & _number);
	RationalNumber operator - (const RationalNumber & _number);
	void operator /= (const RationalNumber & _number);
};

/*****************************************************************************/

#endif //  _RATIONAL_NUMBER_HPP_
