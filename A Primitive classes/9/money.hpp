// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine
#define _CRT_SECURE_NO_WARNINGS

#ifndef _MONEY_HPP_
#define _MONEY_HPP_

/*****************************************************************************/

#include <string>
#include <math.h>
#include <iostream>

class Money
{
public:

	Money();
	
	Money(
		int _dollars,
		int _cents
	);

	Money(std::string const & _str);

	Money(long double _summary);

	~Money() = default;

	int getDollars() const;

	int getCents() const;

	const char * asString() const;

	bool operator == (const Money & _rhs) const;

	bool operator !=(const Money & _rhs) const;
	
	bool operator >=(const Money & _rhs) const;
	
	bool operator <=(const Money & _rhs) const;
	
	bool operator >(const Money & _rhs) const;

	bool operator <(const Money & _rhs) const;

	void operator +=(const Money & _rhs);

	void operator -=(const Money & _rhs);

	Money operator -(const Money & _rhs);

	Money operator +(const Money & _rhs);

	Money operator * (const int);

	Money operator / (const int);

	void operator /= (const int);

	void operator *= (const int);

	friend Money operator "" _USD (long double);

private:
	
	int m_dollars;
	int m_cents;

};

/*****************************************************************************/

inline bool 
Money::operator == (const Money & _rhs) const
{
	return m_dollars == _rhs.m_dollars  && m_cents == _rhs.m_cents;
}

/*****************************************************************************/

inline bool
Money::operator !=(const Money & _rhs) const
{
	return !(*this == _rhs);
}

/*****************************************************************************/

inline bool
Money::operator >=(const Money & _rhs) const
{
	int lhs = m_dollars * 100 + m_cents;
	int rhs = _rhs.m_dollars * 100 + _rhs.m_cents;
	return lhs == rhs || lhs > rhs;
}

/*****************************************************************************/

inline bool
Money::operator <=(const Money & _rhs) const
{
	int lhs = m_dollars * 100 + m_cents;
	int rhs = _rhs.m_dollars * 100 + _rhs.m_cents;
	return lhs == rhs || lhs < rhs;
}

/*****************************************************************************/

inline bool
Money::operator >(const Money & _rhs) const
{
	int lhs = m_dollars * 100 + m_cents;
	int rhs = _rhs.m_dollars * 100 + _rhs.m_cents;
	return lhs > rhs;
}

/*****************************************************************************/

inline bool
Money::operator <(const Money & _rhs) const
{
	int lhs = m_dollars * 100 + m_cents;
	int rhs = _rhs.m_dollars * 100 + _rhs.m_cents;
	return lhs < rhs;
}

/*****************************************************************************/

inline void
Money::operator +=(const Money & _rhs)
{
	m_dollars += _rhs.m_dollars;
	m_cents += _rhs.m_cents;

	if (m_cents > 99)
	{
		m_dollars++;
		m_cents -= 100;
	}
}

/*****************************************************************************/

inline void
Money::operator -=(const Money & _rhs)
{
	m_dollars -= _rhs.m_dollars;
	m_cents -= _rhs.m_cents;
	
	if (m_dollars == 1 && m_cents < 0)
	{
		m_dollars--;
		m_cents = std::abs(100 + m_cents);
	}

	m_cents = std::abs(m_cents);
}

/*****************************************************************************/

inline Money
Money::operator -(const Money & _rhs)
{
	int dollars = m_dollars - _rhs.m_dollars;
	int	cents = m_cents - _rhs.m_cents;
	if (cents < 0)
	{
		dollars--;
		cents = std::abs(100 + m_cents);
	}
	return Money(dollars,cents);
}

/*****************************************************************************/

inline Money
Money::operator +(const Money & _rhs)
{
	int dollars = m_dollars + _rhs.m_dollars;
	int cents = m_cents + _rhs.m_cents;
	if (cents > 99)
	{
		dollars++;
		cents -= 100;
	}
	return Money(dollars, cents);
}

/*****************************************************************************/

inline Money
Money::operator * (const int _const)
{
	int dollars = m_dollars * _const;
	int cents = m_cents * _const;

	int additionalDollars = cents / 100;
	dollars += additionalDollars;
	cents -= (additionalDollars * 100);
	
	return Money(dollars, cents);
}

/*****************************************************************************/

inline Money
Money::operator / (const int _const)
{
	if (_const == 0)
		throw std::logic_error("Division by zero");

	int total = m_dollars * 100 + m_cents;
	int dollars, cents;
	
	total /= _const;
	if (total > -100 && total < 100)
	{
		dollars = 0;
		cents = std::abs(total);
	}
	else
	{
		dollars = total / 100;
		cents = total - (dollars * 100);
	}

	return Money(dollars, cents);
}

/*****************************************************************************/

inline void
Money::operator /= (const int _const)
{
	if (_const == 0)
		throw std::logic_error("Division by zero");

	int total = m_dollars * 100 + m_cents;
	total /= _const;

	if (total > -100 && total < 100)
	{
		m_dollars = 0;
		m_cents = std::abs(total);
	}
	else
	{
		m_dollars = total / 100;
		m_cents = total - (m_dollars * 100);
	}
}

/*****************************************************************************/

inline void
Money::operator *= (const int _const)
{
	m_dollars *= _const;
	m_cents *= _const;

	int additionalDollars = m_cents / 100;

	m_dollars += additionalDollars;
	m_cents -= (additionalDollars * 100);
}

/*****************************************************************************/

inline
int Money::getDollars() const
{
	return m_dollars;
}

/*****************************************************************************/

inline
int Money::getCents() const
{
	return m_cents;
}

/*****************************************************************************/

inline const char * Money::asString() const
{
	char dollars[20], cents[5];
	char buffer[25];
	
	std::string result;
	result += std::string(_itoa(m_dollars, dollars, 10)) + '.';

	if (m_cents < 10) result += "0";
	result += std::string(_itoa(m_cents, cents, 10));

	strcpy(buffer, result.c_str());

	return buffer;
}

/*****************************************************************************/

#endif //  _MONEY_HPP_Ö