// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "overdraftaccount.hpp"

/*****************************************************************************/

OverdraftAccount::OverdraftAccount(
	std::string const & _fullOwnerName,
	double _startBalance,
	double _overdraftLimit
)
	: Account(_fullOwnerName,_startBalance)
	, m_overdraftLimit(_overdraftLimit)
{}

/*****************************************************************************/

double OverdraftAccount::getOverdraftLimit() const
{
	return m_overdraftLimit;
}

/*****************************************************************************/