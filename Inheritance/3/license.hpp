// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _LICENSE_HPP_
#define _LICENSE_HPP_

/*****************************************************************************/

#include "date.hpp"
#include "license_type.hpp"

class License
{

	/*-----------------------------------------------------------------*/
public:

	License(
		Date const & _date
	);

	virtual ~License() = default;

	virtual bool isAvailable(Date const & _date) const = 0;
	
	virtual void use() = 0;
	
	virtual LicenseType getType() const = 0;

	Date const getBirthDate() const;

private:

	const Date m_birthDate;

	/*-----------------------------------------------------------------*/
};

inline Date const License::getBirthDate() const
{
	return m_birthDate;
}

#endif // _LICENSE_HPP_