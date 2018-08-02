// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "controller.hpp"
#include "messages.hpp"
#include "organization.hpp"
#include "payment.hpp"

#include <algorithm>

/*****************************************************************************/

Controller::Controller() = default;

/*****************************************************************************/

Controller::~Controller() = default;

/*****************************************************************************/

void Controller::addOrganization(
	const std::string & _name,
	const std::string & _registrationNumber,
	double _initialBalance
)
{
	if (_name.empty())
		throw std::logic_error(Messages::EmptyOrganizationName);

	if (_registrationNumber.length() == 8)
		for (int i = 0; i < _registrationNumber.length(); i++)
		{
			if (!isdigit(_registrationNumber[i]))
				throw std::logic_error(Messages::InvalidRegistrationNumberFormat);
		}
	else
		throw std::logic_error(Messages::InvalidRegistrationNumberFormat);

	if (m_organizations.find(_name) != m_organizations.end())
		throw std::logic_error(Messages::DuplicateOrganization);

	for (auto it = m_organizations.begin(); it != m_organizations.end(); ++it)
		if (it->second->getID() == _registrationNumber)
			throw std::logic_error(Messages::DuplicateRegistrationNumber);

	m_organizations.insert(std::make_pair(_name,std::make_unique<Organization>(_name, _registrationNumber, _initialBalance)));
}

/*****************************************************************************/

const std::string & Controller::getRegistrationNumber(const std::string & _organizationName) const
{
	if (m_organizations.find(_organizationName) == m_organizations.end())
		throw std::logic_error(Messages::OrganizationCannotBeFound);

	return m_organizations.find(_organizationName)->second->getID();
}

/*****************************************************************************/

double Controller::getBalance(const std::string & _organizationName) const
{
	if (m_organizations.find(_organizationName) == m_organizations.end())
		throw std::logic_error(Messages::OrganizationCannotBeFound);

	return m_organizations.find(_organizationName)->second->getBalance();
}

/*****************************************************************************/

void Controller::addPayment(
	const std::string & _senderName,
	const std::string & _recieverName,
	const std::string & _paymentId,
	const std::string & _purpose, 
	DateTime _time, double _sum
)
{
	if (m_organizations.find(_senderName) == m_organizations.end())
		throw std::logic_error(Messages::OrganizationCannotBeFound);

	if (m_organizations.find(_recieverName) == m_organizations.end())
		throw std::logic_error(Messages::OrganizationCannotBeFound);

	if (_senderName == _recieverName)
		throw std::logic_error(Messages::PaymentForItself);

	if (_paymentId.empty())
		throw std::logic_error(Messages::EmptyPaymentId);

	if (_purpose.empty())
		throw std::logic_error(Messages::EmptyPaymentPurpose);

	DateTime current;
	if (_time > current)
		throw std::logic_error(Messages::InvalidPaymentTime);

	if (_sum < 1)
		throw std::logic_error(Messages::InvalidPaymentSum);

	if (m_payments.find(_paymentId) != m_payments.end())
		throw std::logic_error(Messages::DuplicatePayment);

	m_payments.insert(std::make_pair(_paymentId, std::make_unique<Payment>(
		*m_organizations.find(_senderName)->second.get(),
		*m_organizations.find(_recieverName)->second.get(),
		_paymentId,
		_purpose,
		_time,
		_sum
		)));

	m_organizations.find(_senderName)->second->changeBalance(-_sum);
	m_organizations.find(_senderName)->second->addOutcomePayment(*m_payments.find(_paymentId)->second.get());

	m_organizations.find(_recieverName)->second->changeBalance(_sum);
	m_organizations.find(_recieverName)->second->addIncomePayment(*m_payments.find(_paymentId)->second.get());
}

/*****************************************************************************/

const std::string & Controller::getSenderName(const std::string & _paymentId) const
{
	if (m_payments.find(_paymentId) == m_payments.end())
		throw std::logic_error(Messages::PaymentCannotBeFound);

	return m_payments.find(_paymentId)->second->getSender().getName();
}

/*****************************************************************************/

const std::string & Controller::getReceiverName(const std::string & _paymentId) const
{
	if (m_payments.find(_paymentId) == m_payments.end())
		throw std::logic_error(Messages::PaymentCannotBeFound);

	return m_payments.find(_paymentId)->second->getReceiver().getName();
}

/*****************************************************************************/

const std::string & Controller::getPaymentPurpose(const std::string & _paymentId) const
{
	if (m_payments.find(_paymentId) == m_payments.end())
		throw std::logic_error(Messages::PaymentCannotBeFound);

	return m_payments.find(_paymentId)->second->getPurpose();
}

/*****************************************************************************/

DateTime Controller::getPaymentDateTime(const std::string & _paymentId) const
{
	if (m_payments.find(_paymentId) == m_payments.end())
		throw std::logic_error(Messages::PaymentCannotBeFound);

	return m_payments.find(_paymentId)->second->getDateTime();
}

/*****************************************************************************/

double Controller::getPaymentSum(const std::string & _paymentId) const
{
	if (m_payments.find(_paymentId) == m_payments.end())
		throw std::logic_error(Messages::PaymentCannotBeFound);

	return m_payments.find(_paymentId)->second->getSummary();
}

/*****************************************************************************/

std::vector<std::pair<std::string, double>> Controller::getFinalBalances() const
{
	std::vector<std::pair<std::string, double>> organizations;

	for (auto it = m_organizations.begin(); it != m_organizations.end(); ++it)
		organizations.push_back(std::make_pair(it->first, it->second->getBalance()));

	std::sort(
		organizations.begin(),
		organizations.end(),
		[](std::pair<std::string, double> const & lhs,
		   std::pair<std::string, double> const & rhs
		)
	{
		return lhs < rhs;
	}
	);

	return organizations;
}

/*****************************************************************************/

std::vector<std::string> Controller::getOrganizationsWithNegativeSaldo() const
{
	std::vector<std::string> organizations;

	for (auto it = m_organizations.begin(); it != m_organizations.end(); ++it)
		if (it->second->getBalance() < 1)
		organizations.push_back(it->first);

	std::sort(organizations.begin(), organizations.end());

	return organizations;
}

/*****************************************************************************/

std::string Controller::getIdOfBiggestPayment() const
{
	std::string ID;
	double max = 0.0;
	for (auto it = m_payments.begin(); it != m_payments.end(); it++)
		if (it->second->getSummary() > max)
		{
			max = it->second->getSummary();
			ID = it->second->getID();
		}
	return ID;
}

/*****************************************************************************/

Date Controller::getDateWithBiggestTotalPayments() const
{
	Date biggestDay;
	double max = 0.0;

	for (auto it = m_payments.begin(); it != m_payments.end(); it++)
		if (it->second->getSummary() > max)
		{
			max = it->second->getSummary();
			biggestDay = Date(
				it->second->getDateTime().getYear(),
				it->second->getDateTime().getMonth(),
				it->second->getDateTime().getDay()
			);
		}

	return m_payments.empty() ? Date() : biggestDay;
}

/*****************************************************************************/
