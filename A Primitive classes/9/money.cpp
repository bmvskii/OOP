// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "money.hpp"

#include <stdexcept>
#include <iostream>

/*****************************************************************************/

Money::Money()
	: m_dollars(0)
	, m_cents(0)
{}

/*****************************************************************************/

Money::Money(int _dollars, int _cents)
{
	if (_cents < 0 || _cents > 99)
		throw std::logic_error("Invalid cents");

	m_dollars = _dollars;
	m_cents = _cents;
}

/*****************************************************************************/

Money::Money(std::string const & _str)
{
	int dot = 0;
	for (int i = 0; i < _str.length(); i++)
	{
		if (_str[i] == '.') {
			dot++;
			continue;
		}
		if (isdigit(_str[i]) || _str[i] == '-') continue;
		else throw std::logic_error("Incorrect money format");
	}
	
	if (dot != 1) throw std::logic_error("Incorrect money format");

	std::string base, floatPart;
	int pos = _str.find('.');

	for (int i = 0; i < pos; i++) base += _str[i];
	for (int i = pos+1; i < _str.length(); i++) floatPart += _str[i];

	if (floatPart.empty())
		throw std::logic_error("Incorrect money format");

	m_dollars = std::atoi(base.c_str());
	m_cents = std::atoi(floatPart.c_str());

	if (m_cents < 0 || m_cents > 99)
		throw std::logic_error("Invalid cents");
}

/*****************************************************************************/

Money::Money(long double _summary)
{
	m_dollars = static_cast<int>(_summary);
	m_cents = std::round(std::abs(_summary - m_dollars) * 100.00);
}

/*****************************************************************************/

Money operator""_USD(long double _num)
{
	return Money(_num);
}

/*****************************************************************************/