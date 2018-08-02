// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "slowexpirypolicy.hpp"
#include "consignment.hpp"

/*****************************************************************************/

SlowExpiryPolicy::SlowExpiryPolicy(
	Date const & _date,
	int _maxStoredDays
)
	: DaysExpiryPolicy(_date,_maxStoredDays)
{}

/*****************************************************************************/

double SlowExpiryPolicy::getSalePercetage(Consignment const & _c) const
{	
	if (getDiffernceBetweenTwoDates(_c.getDate(), getCurrentDate()) == 0)
		return 0.0;
	else 
		return (double)getDiffernceBetweenTwoDates(_c.getDate(), getCurrentDate()) / (double)getMaxStoredDays();
}

ExpiryPolicyKind SlowExpiryPolicy::getKind() const
{
	return ExpiryPolicyKind::Slow;
}

/*****************************************************************************/