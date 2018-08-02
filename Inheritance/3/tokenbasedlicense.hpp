// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _TOKENBASEDLICENSE_HPP_
#define _TOKENBASEDLICENSE_HPP_

#include "license.hpp"

class TokenBasedLicense
	: public License
{

	/*-----------------------------------------------------------------*/
public:
	TokenBasedLicense(
		Date const & _date,
		int _days
	);

	~TokenBasedLicense() = default;

	bool isAvailable(Date const & _date) const override;

	void updateDays(int _newNumber);

	void use() override;

	int getDays() const;

	LicenseType getType() const override;

private:

	int m_nDays;

	/*-----------------------------------------------------------------*/

};

inline
int TokenBasedLicense::getDays() const
{
	return m_nDays;
}

inline
void TokenBasedLicense::updateDays(int _newNumber)
{
	m_nDays += _newNumber;
}

inline LicenseType TokenBasedLicense::getType() const
{
	return LicenseType::TokenBased;
}

#endif // _TOKENBASEDLICENSE_HPP_