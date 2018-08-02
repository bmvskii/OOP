// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#define _CRT_SECURE_NO_WARNINGS
#include "controller.hpp"
#include "messages.hpp"
#include "expirypolicy.hpp"
#include "consignment.hpp"
#include "daysexpirypolicy.hpp"
#include "nullexpirypolicy.hpp"
#include "quickexpirypolicy.hpp"
#include "slowexpirypolicy.hpp"

/*****************************************************************************/

Controller::Controller() = default;

/*****************************************************************************/

Controller::~Controller() = default;

/*****************************************************************************/

void Controller::createConsignment(
	std::string const & _productName,
	double _initialAmount,
	Date const & _date,
	double _price,
	ExpiryPolicyKind _expiryPolicyKind,
	int _expiresDays
)
{
	if (_productName.empty())
		throw std::logic_error(Messages::EmptyProductName);

	auto it = m_consignments.find(_productName);
	if (it != m_consignments.end())
		throw std::logic_error(Messages::ProductNotUnique);

	if (_initialAmount < 1)
		throw std::logic_error(Messages::NonPositiveAmount);

	if (_price <= 0)
		throw std::logic_error(Messages::NonPositivePrice);

	if (_expiresDays < 1 &&_expiryPolicyKind != ExpiryPolicyKind::Null)
			throw std::logic_error(Messages::NonPositiveExpiryDays);

	switch (_expiryPolicyKind)
	{
	case ExpiryPolicyKind::Null:
		m_policies.insert(std::make_pair(_productName, std::make_unique<NullExpiryPolicy>()));
		break;
	case ExpiryPolicyKind::Quick:
		m_policies.insert(std::make_pair(_productName, std::make_unique<QuickExpiryPolicy>(m_currentDate, _expiresDays)));
		break;
	case ExpiryPolicyKind::Slow:
		m_policies.insert(std::make_pair(_productName, std::make_unique<SlowExpiryPolicy>(m_currentDate, _expiresDays)));
		break;
	default:
		break;
	}

	auto consignment = std::make_unique<Consignment>(
		_productName,
		_initialAmount,
		_price,
		_date,
		*m_policies.find(_productName)->second
		);

	m_consignments.insert(std::make_pair(_productName, std::move(consignment)));
}

/*****************************************************************************/

double Controller::getConsignmentAmount(std::string const & _productName) const
{
	auto it = m_consignments.find(_productName);
	if (it == m_consignments.end())
		throw std::logic_error(Messages::ProductNotFound);

	return it->second->getWeigth();
}

/*****************************************************************************/

double Controller::getConsignmentPrice(std::string const & _productName) const
{
	auto it = m_consignments.find(_productName);
	if (it == m_consignments.end())
		throw std::logic_error(Messages::ProductNotFound);
	
	return it->second->getPrice();
}

/*****************************************************************************/

Date Controller::getConsignmentProductionDate(std::string const & _productName) const
{
	auto it = m_consignments.find(_productName);
	if (it == m_consignments.end())
		throw std::logic_error(Messages::ProductNotFound);
	return it->second->getDate();
}

/*****************************************************************************/

ExpiryPolicyKind 
Controller::getConsignmentExpiryPolicyKind(std::string const & _productName) const
{
	auto it = m_consignments.find(_productName);
	if (it == m_consignments.end())
		throw std::logic_error(Messages::ProductNotFound);

	return it->second->getExpiryPolicy().getKind();
}

/*****************************************************************************/

bool Controller::isConsignmentExpired(std::string const & _productName) const
{
	auto it = m_consignments.find(_productName);
	if (it == m_consignments.end())
		throw std::logic_error(Messages::ProductNotFound);

	return it->second->getExpiryPolicy().isBadConsignment(*it->second);
}

/*****************************************************************************/

double Controller::getTotalFreshCost() const
{
	double totalCost = 0.0;

	for (auto const & c : m_consignments)
	{
		if (!c.second->isBadProduct())
			totalCost += c.second->getCostFresh();
	}
	return totalCost;
}

/*****************************************************************************/

double Controller::getConsignmentFreshCost(std::string const & _productName) const
{
	auto it = m_consignments.find(_productName);
	if (it == m_consignments.end())
		throw std::logic_error(Messages::ProductNotFound);

	return it->second->isBadProduct() ? 0 : it->second->getCostFresh();
}

/*****************************************************************************/

double Controller::getTotalExpiredCost() const
{
	double totalCost = 0.0;

	for (auto const & c : m_consignments)
	{
		if (c.second->isBadProduct())
			totalCost += c.second->getCostExpired();
	}
	return totalCost;
}

/*****************************************************************************/

double Controller::getConsignmentExpiredCost(std::string const & _productName) const
{
	auto it = m_consignments.find(_productName);
	if (it == m_consignments.end())
		throw std::logic_error(Messages::ProductNotFound);

	return !it->second->isBadProduct() ? 0 : it->second->getCostExpired();
}

/*****************************************************************************/

void Controller::sell(std::string const & _productName, double _amount)
{
	auto it = m_consignments.find(_productName);
	if (it == m_consignments.end())
		throw std::logic_error(Messages::ProductNotFound);

	if (_amount <= 0)
		throw std::logic_error(Messages::NonPositiveAmount);

	if (it->second->isBadProduct())
		throw std::logic_error(Messages::SellingExpired);

	if (greaterDoubles(_amount,it->second->getWeigth()))
		throw std::logic_error(Messages::SellingOverAmount);

	it->second->sell(_amount);
	
	if (equalDoubles(it->second->getWeigth(),0.0))
		m_consignments.erase(it);
}

/*****************************************************************************/

void Controller::setCurrentDate(Date _date)
{
	if (_date <= m_currentDate)
		throw std::logic_error(Messages::ExpectLaterDate);

	m_currentDate = _date;
}

/*****************************************************************************/
