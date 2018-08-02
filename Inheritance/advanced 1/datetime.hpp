// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _DATETIME_HPP_
#define _DATETIME_HPP_

/*****************************************************************************/

#include <iostream>

/*****************************************************************************/


class DateTime
{

	/*-----------------------------------------------------------------*/

public:

	/*-----------------------------------------------------------------*/

	DateTime();
	DateTime(int _year, int _month, int _day);
	// Format: YYYY/MM/DD-H:M:S
	explicit DateTime(const char* _datetime, char _datesep = '/', char _datetimesep = '-', char _timesep = ':');

	int getYear() const;
	int getMonth() const;
	int getDay() const;

	bool isLeapYear() const;

	bool operator == (DateTime _d) const;
	bool operator != (DateTime _d) const;
	bool operator < (DateTime _d) const;
	bool operator <= (DateTime _d) const;
	bool operator > (DateTime _d) const;
	bool operator >= (DateTime _d) const;

	DateTime operator ++(int);

	/*-----------------------------------------------------------------*/

private:

	void changeDate(const int _dayLimit, bool _isNewYear = false);

	/*-----------------------------------------------------------------*/

	bool isValid() const;

	/*-----------------------------------------------------------------*/

	int m_year, m_month, m_day, m_hours;

	/*-----------------------------------------------------------------*/

};


/*****************************************************************************/

std::ostream & operator << (std::ostream & o, DateTime d);

std::istream & operator >> (std::istream & i, DateTime & d);

/*****************************************************************************/

#endif // _DATETIME_HPP_