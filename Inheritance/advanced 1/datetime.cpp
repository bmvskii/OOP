// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

/*****************************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include "datetime.hpp"

#include <ctime>
#include <cassert>
#include <cstdio>
#include <stdexcept>

/*****************************************************************************/


DateTime::DateTime()
{
	time_t currentTime = time(nullptr);

	tm* currentTM = gmtime(&currentTime);

	m_year = currentTM->tm_year + 1900;
	m_month = currentTM->tm_mon + 1;
	m_day = currentTM->tm_mday;
}


/*****************************************************************************/


DateTime::DateTime(int _year, int _month, int _day)
	: m_year(_year), m_month(_month), m_day(_day)
{
	if (!isValid())
		throw std::logic_error("Invalid datetime");
}


/*****************************************************************************/


DateTime::DateTime(const char * _datetime, char _datesep, char _datetimesep, char _timesep)
{
	char sep1, sep2, spacesep, sep3, sep4;
	int nMatched = sscanf(
		_datetime
		, "%d%c%d%c%d%"
		, &m_year, &sep1, &m_month, &sep2, &m_day
	);
	if (nMatched != 5
		|| sep1 != _datesep || sep2 != _datesep
		)
		throw std::logic_error("Invalid datetime format");

	if (!isValid())
		throw std::logic_error("Invalid datetime");
}


/*****************************************************************************/


int
DateTime::getYear() const
{
	return m_year;
}


/*****************************************************************************/


int
DateTime::getMonth() const
{
	return m_month;
}


/*****************************************************************************/


int
DateTime::getDay() const
{
	return m_day;
}


/*****************************************************************************/


bool
DateTime::isLeapYear() const
{
	if (m_year % 4 != 0)
		return false;

	else if (m_year % 100 == 0)
		return (m_year % 400 == 0);

	return true;
}


/*****************************************************************************/


bool
DateTime::operator == (DateTime d) const
{
	return m_year == d.getYear()
		&& m_month == d.getMonth()
		&& m_day == d.getDay();
}


/*****************************************************************************/


bool
DateTime::operator != (DateTime d) const
{
	return !(*this == d);
}


/*****************************************************************************/


bool
DateTime::operator < (DateTime d) const
{
	if (m_year < d.getYear())
		return true;

	else if (m_year == d.getYear())
	{
		if (m_month < d.getMonth())
			return true;

		else if (m_month == d.getMonth())
		{
			if (m_day < d.getDay())
				return true;
		}
	}

	return false;
}


/*****************************************************************************/


bool
DateTime::operator > (DateTime d) const
{
	return d < *this;
}


/*****************************************************************************/


bool
DateTime::operator <= (DateTime d) const
{
	return (*this < d) || (*this == d);
}


/*****************************************************************************/


bool
DateTime::operator >= (DateTime d) const
{
	return (d < *this) || (*this == d);
}

/*****************************************************************************/


void DateTime::changeDate(const int _dayLimit, bool _isNewYear)
{
	if (m_day < _dayLimit)
		m_day++;
	else
	{
		m_month++;
		m_day = 1;
		if (_isNewYear)
		{
			m_year++;
			m_month = 1;
		}			
	}
}

/*****************************************************************************/

DateTime DateTime::operator ++(int)
{
	DateTime copy(*this);

	int nFebruaryDays = isLeapYear() ? 29 : 28;

	switch (m_month)
	{
	case 2:
		changeDate(nFebruaryDays);
		break;
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
		changeDate(31);
		break;
	case 12:
		changeDate(31, true);
		break;
	case 4:
	case 6:
	case 9:
	case 11:
		changeDate(30);
	default:
		break;
	}

	return copy;
}


/*****************************************************************************/


bool
DateTime::isValid() const
{
	if (m_year == 0)
		return false;

	if (m_month < 1 || m_month > 12)
		return false;

	if (m_day < 1)
		return false;

	else if (m_month == 2 && isLeapYear())
		return m_day <= 29;

	else
	{
		static const int s_daysInMonth[] = {
			31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
		};

		if (m_day > s_daysInMonth[m_month - 1])
			return false;
	}

	return true;
}


/*****************************************************************************/


std::ostream & operator << (std::ostream & o, const DateTime & d)
{
	o << d.getYear() << '/' << d.getMonth() << '/' << d.getDay();
	return o;
}


/*****************************************************************************/


std::istream & operator >> (std::istream & i, DateTime & d)
{
	char buf[100];
	i >> buf;

	d = DateTime(buf);
	return i;
}


/*****************************************************************************/

