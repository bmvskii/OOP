// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "tokenbasedlicense.hpp"

/*****************************************************************************/

TokenBasedLicense::TokenBasedLicense(
	Date const & _date,
	int _days
)
	: License(_date)
	, m_nDays(_days)
{}

/*****************************************************************************/

bool TokenBasedLicense::isAvailable(Date const & _date) const
{
	return _date >= getBirthDate() && m_nDays > 0;
}

/*****************************************************************************/

void TokenBasedLicense::use()
{
	m_nDays--;
}