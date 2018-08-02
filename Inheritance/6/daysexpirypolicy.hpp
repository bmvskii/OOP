// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _DAYSEXPIRYPOLICY_HPP_
#define _DAYSEXPIRYPOLICY_HPP_

/*****************************************************************************/

#include "expirypolicy.hpp"
#include "date.hpp"

/*****************************************************************************/

class DaysExpiryPolicy
	: public ExpiryPolicy
{

	/*-----------------------------------------------------------------*/

protected:

	DaysExpiryPolicy(
		Date const & _date,
		int _maxStoredDays
	);

	int getDiffernceBetweenTwoDates(
		Date _lhs,
		Date _rhs
	) const;

public:

	~DaysExpiryPolicy() = default;

	bool isBadConsignment(Consignment const & _c) const override;

	double getSalePercetage(Consignment const & _c) const = 0;

	Date const getCurrentDate() const;

	int getMaxStoredDays() const;

	ExpiryPolicyKind getKind() const = 0;

private:

	Date const & m_currentDate;
	int m_maxStoredDays;

	/*-----------------------------------------------------------------*/
};

/*****************************************************************************/

inline
Date const 
DaysExpiryPolicy::getCurrentDate() const
{
	return m_currentDate;
}

/*****************************************************************************/

inline
int DaysExpiryPolicy::getMaxStoredDays() const
{
	return m_maxStoredDays;
}

/*****************************************************************************/

#endif // _DAYSEXPIRYPOLICY_HPP_