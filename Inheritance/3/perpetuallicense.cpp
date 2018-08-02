// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "perpetuallicense.hpp"

PerpetualLicense::PerpetualLicense(
	Date const & _date
)
	: License(_date)
{}

bool PerpetualLicense::isAvailable(Date const & _date) const
{
	return _date >= getBirthDate();
}

void PerpetualLicense::use()
{
	return;
}