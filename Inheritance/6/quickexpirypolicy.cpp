// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "quickexpirypolicy.hpp"
#include "consignment.hpp"

/*****************************************************************************/

QuickExpiryPolicy::QuickExpiryPolicy(
	Date const & _date,
	int _maxStoredDays
)
	: DaysExpiryPolicy(_date,_maxStoredDays)
{}

/*****************************************************************************/

double QuickExpiryPolicy::getSalePercetage(Consignment const & _c) const
{
	if (getDiffernceBetweenTwoDates(_c.getDate(), getCurrentDate()) <= getMaxStoredDays())
		return 0.0;
	else
		return 1.0;
}

/*****************************************************************************/

ExpiryPolicyKind QuickExpiryPolicy::getKind() const
{
	return ExpiryPolicyKind::Quick;
}

/*****************************************************************************/
