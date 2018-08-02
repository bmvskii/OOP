// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _ORGANIZATION_HPP_
#define _ORGANIZATION_HPP_

/*****************************************************************************/

#include <string>
#include <unordered_map>
#include <functional>

class Payment;

/*****************************************************************************/

class Organization
{

/*-----------------------------------------------------------------*/

public:

/*-----------------------------------------------------------------*/

	Organization(
		std::string const & _name,
		std::string const & _registrationID,
		double _startBalance = 0.0
	);

	~Organization() = default;

	std::string const & getName() const;

	std::string const & getID() const;

	double getBalance() const;

	void changeBalance(double _summ);

	void addIncomePayment(Payment const & _p);

	void addOutcomePayment(Payment const & _p);

	bool hasIncomePayment(std::string const & _p) const;

	bool hasOutcomePayment(std::string const & _p) const;

	void forEachIncomePayment(std::function<void(Payment const & _p)> _f);

	void forEachOutcomePayment(std::function<void(Payment const & _p)> _f);

/*-----------------------------------------------------------------*/

private:

/*-----------------------------------------------------------------*/

	std::string m_name;

	std::string m_registationID;

	double m_balance;

	std::unordered_map<std::string, Payment const *> m_incomePayments;

	std::unordered_map<std::string, Payment const *> m_outcomePayments;

/*-----------------------------------------------------------------*/    

};

/*****************************************************************************/

inline
bool Organization::hasIncomePayment(std::string const & _p) const
{
	return m_incomePayments.find(_p) != m_incomePayments.end();
}

/*****************************************************************************/

inline
bool Organization::hasOutcomePayment(std::string const & _p) const
{
	return m_outcomePayments.find(_p) != m_outcomePayments.end();
}

/*****************************************************************************/

inline
std::string const & Organization::getName() const
{
	return m_name;
}

/*****************************************************************************/

inline
std::string const & Organization::getID() const
{
	return m_registationID;
}

/*****************************************************************************/

inline
double Organization::getBalance() const
{
	return m_balance;
}

/*****************************************************************************/

inline
void Organization::changeBalance(double _summ)
{
	m_balance += _summ;
}

/*****************************************************************************/

#endif // _ORGANIZATION_HPP_
