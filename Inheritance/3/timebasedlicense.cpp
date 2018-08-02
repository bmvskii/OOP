// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "timebasedlicense.hpp"

TimeBasedLicense::TimeBasedLicense(
	Date const & _birthDate,
	Date const & _endDate
)
	: License(_birthDate)
	, m_endDate(_endDate)
{}

bool TimeBasedLicense::isAvailable(Date const & _date) const
{
	return _date >= getBirthDate() && _date <= m_endDate;
}

void TimeBasedLicense::use()
{
	return;
}

void TimeBasedLicense::continuate(Date const & _date)
{
	m_endDate = _date;
}