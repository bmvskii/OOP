// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _NULLEXPIRYPOLICY_HPP_
#define _NULLEXPIRYPOLICY_HPP_

/*****************************************************************************/

#include "expirypolicy.hpp"

/*****************************************************************************/

class NullExpiryPolicy
	: public ExpiryPolicy
{

	/*-----------------------------------------------------------------*/

public:
	
	bool isBadConsignment(Consignment const & _c) const override;

	double getSalePercetage(Consignment const & _c) const override;

	virtual ExpiryPolicyKind getKind() const override;

	NullExpiryPolicy();

	~NullExpiryPolicy();

	/*-----------------------------------------------------------------*/

};

/*****************************************************************************/

#endif // _NULLEXPIRYPOLICY_HPP_