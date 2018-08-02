// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _PERPETUALLICENSE_HPP_
#define _PERPETUALLICENSE_HPP_

#include "license.hpp"

class PerpetualLicense
	: public License
{

	/*-----------------------------------------------------------------*/
public:
	PerpetualLicense(
		Date const & _date
	);

	~PerpetualLicense() = default;
	
	bool isAvailable(Date const & _date) const override;

	void use() override;

	LicenseType getType() const override;

	/*-----------------------------------------------------------------*/

};

inline
LicenseType PerpetualLicense::getType() const
{
	return LicenseType::Perpetual;
}

#endif // _PERPETUALLICENSE_HPP_