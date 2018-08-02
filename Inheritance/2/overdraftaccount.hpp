// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _OVERDRAFTACCOUNT_HPP_
#define _OVERDRAFTACCOUNT_HPP_

/*****************************************************************************/

#include "account.hpp"

/*****************************************************************************/


class OverdraftAccount
	: public Account
{

	/*-----------------------------------------------------------------*/
public:

	OverdraftAccount(
		std::string const & _fullOwnerName,
		double _startBalance,
		double _overdraftLimit
	);

	~OverdraftAccount() = default;

	double getOverdraftLimit() const override;

private:

	double m_overdraftLimit;

	/*-----------------------------------------------------------------*/

};


/*****************************************************************************/

#endif // _OVERDRAFTACCOUNT_HPP_