// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _SLOWEXPIRYPOLICY_HPP_
#define _SLOWEXPIRYPOLICY_HPP_

/*****************************************************************************/

#include "daysexpirypolicy.hpp"

/*****************************************************************************/

class SlowExpiryPolicy
	: public DaysExpiryPolicy
{

	/*-----------------------------------------------------------------*/

public:

	SlowExpiryPolicy(
		Date const & _date,
		int _maxStoredDays
	);

	~SlowExpiryPolicy() = default;

	double getSalePercetage(Consignment const & _c) const override;

	virtual ExpiryPolicyKind getKind() const override;

	/*-----------------------------------------------------------------*/

};

/*****************************************************************************/

#endif // _SLOWEXPIRYPOLICY_HPP_