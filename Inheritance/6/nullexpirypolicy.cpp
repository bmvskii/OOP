// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "nullexpirypolicy.hpp"

/*****************************************************************************/

bool NullExpiryPolicy::isBadConsignment(Consignment const & _c) const
{
	return false;
}

/*****************************************************************************/

double NullExpiryPolicy::getSalePercetage(Consignment const & _c) const
{
	return 0.0;
}

/*****************************************************************************/

ExpiryPolicyKind NullExpiryPolicy::getKind() const
{
	return ExpiryPolicyKind::Null;
}

/*****************************************************************************/

NullExpiryPolicy::NullExpiryPolicy() = default;


/*****************************************************************************/

NullExpiryPolicy::~NullExpiryPolicy() = default;

/*****************************************************************************/