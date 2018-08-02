// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "account.hpp"

/*****************************************************************************/

Account::Account(
	std::string const & _fullOwnerName,
	double _startBalance
)
	: m_fullOwnerName(_fullOwnerName)
	, m_currentBalance(_startBalance)
	, m_ID(0)
{}

/*****************************************************************************/

double Account::getOverdraftLimit() const
{
	return 0.0;
}

/*****************************************************************************/