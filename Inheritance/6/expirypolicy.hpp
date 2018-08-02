// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _EXPIRYPOLICY_HPP_
#define _EXPIRYPOLICY_HPP_

/*****************************************************************************/

#include "expirypolicykind.hpp"

class Consignment;

class ExpiryPolicy
{

	/*-----------------------------------------------------------------*/

public:
	
	virtual ~ExpiryPolicy() = default;

	virtual bool isBadConsignment(Consignment const & _c) const = 0;

	virtual double getSalePercetage(Consignment const & _c) const = 0;

	virtual ExpiryPolicyKind getKind() const = 0;

	/*-----------------------------------------------------------------*/

};

/*****************************************************************************/

#endif // _EXPIRYPOLICY_HPP_