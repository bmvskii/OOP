// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _QUICKEXPIRYPOLICY_HPP_
#define _QUICKEXPIRYPOLICY_HPP_

/*****************************************************************************/

#include "daysexpirypolicy.hpp"

/*****************************************************************************/

class QuickExpiryPolicy
	: public DaysExpiryPolicy
{

	/*-----------------------------------------------------------------*/

public:

	QuickExpiryPolicy(
		Date const& _date,
		int _maxStoredDays
	);

	~QuickExpiryPolicy() = default;

	double getSalePercetage(Consignment const & _c) const override;

	virtual ExpiryPolicyKind getKind() const override;

	/*-----------------------------------------------------------------*/

};

/*****************************************************************************/

#endif // _QUICKEXPIRYPOLICY_HPP_