// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "organization.hpp"
#include "messages.hpp"
#include "payment.hpp"

/*****************************************************************************/

// TODO implement your methods here

/*****************************************************************************/

Organization::Organization(
	std::string const & _name,
	std::string const & _registrationID,
	double _startBalance
)
	: m_name(_name)
	, m_registationID(_registrationID)
	, m_balance(_startBalance)
{}

/*****************************************************************************/

void Organization::addIncomePayment(Payment const & _p)
{
	m_incomePayments.insert(std::make_pair(_p.getID(), &_p));
}

/*****************************************************************************/

void Organization::addOutcomePayment(Payment const & _p)
{
	m_outcomePayments.insert(std::make_pair(_p.getID(), &_p));
}

/*****************************************************************************/

void Organization::forEachIncomePayment(std::function<void(Payment const&_p)> _f)
{
	for (auto p : m_incomePayments)
		_f(*p.second);
}

/*****************************************************************************/

void Organization::forEachOutcomePayment(std::function<void(Payment const&_p)> _f)
{
	for (auto p : m_outcomePayments)
		_f(*p.second);
}

/*****************************************************************************/
