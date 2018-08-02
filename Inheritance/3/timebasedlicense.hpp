// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _TIMEBASEDLICENSE_HPP_
#define _TIMEBASEDLICENSE_HPP_

#include "license.hpp"

class TimeBasedLicense
	: public License
{

	/*-----------------------------------------------------------------*/
public:
	TimeBasedLicense(
		Date const & _creatingDate,
		Date const & _endingDate
	);

	~TimeBasedLicense() = default;

	bool isAvailable(Date const & _date) const override;

	void use() override;

	void continuate(Date const & _date);

	Date const getEndDate() const;

	LicenseType getType() const override;

private:
	Date m_endDate;
	/*-----------------------------------------------------------------*/

};

/*****************************************************************************/

inline
Date const 
TimeBasedLicense::getEndDate() const
{
	return m_endDate;
}

inline LicenseType TimeBasedLicense::getType() const
{
	return LicenseType::TimeBased;
}

#endif // _TIMEBASEDLICENSE_HPP_