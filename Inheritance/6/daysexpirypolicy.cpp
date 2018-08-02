// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "daysexpirypolicy.hpp"
#include "consignment.hpp"

/*****************************************************************************/

DaysExpiryPolicy::DaysExpiryPolicy(
	Date const & _date,
	int _maxStoredDays
)
	: m_currentDate(_date)
	, m_maxStoredDays(_maxStoredDays)
{}

/*****************************************************************************/

bool DaysExpiryPolicy::isBadConsignment(Consignment const & _c) const
{
	Date date = _c.getDate();

	if (getDiffernceBetweenTwoDates(date, m_currentDate) == -1)
		return false;

	else if (getDiffernceBetweenTwoDates(date, m_currentDate) <= m_maxStoredDays)
		return false;

	return true;
}

/*****************************************************************************/

int DaysExpiryPolicy::getDiffernceBetweenTwoDates(Date _lhs, Date _rhs) const
{
	int nCountDiffer = 0;
	if (_lhs > _rhs)
		return -1;

	while (_lhs++ != _rhs)
		nCountDiffer++;

	return nCountDiffer;
}

/*****************************************************************************/