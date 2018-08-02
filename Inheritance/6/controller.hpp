// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _CONTROLLER_HPP_
#define _CONTROLLER_HPP_

/*****************************************************************************/

#include "date.hpp"
#include "expirypolicykind.hpp"
#include "utils.hpp"

#include <string>
#include <unordered_map>
#include <memory>

/*****************************************************************************/

class ExpiryPolicy;
class Consignment;

class Controller
{

	/*-----------------------------------------------------------------*/

public:

	/*-----------------------------------------------------------------*/

	Controller();

	Controller(const Controller &) = delete;

	Controller & operator = (const Controller &) = delete;

	~Controller();

	/*-----------------------------------------------------------------*/

	void createConsignment(
		std::string const & _productName
		, double _initialAmount
		, Date const & _date
		, double _price
		, ExpiryPolicyKind _expiryPolicyKind
		, int _expiresDays = -1
	);

	double getConsignmentAmount(std::string const & _productName) const;

	double getConsignmentPrice(std::string const & _productName) const;

	Date getConsignmentProductionDate(std::string const & _productName) const;

	ExpiryPolicyKind getConsignmentExpiryPolicyKind(std::string const & _productName) const;

	bool isConsignmentExpired(std::string const & _productName) const;

	/*-----------------------------------------------------------------*/

	double getTotalFreshCost() const;

	double getConsignmentFreshCost(std::string const & _productName) const;

	double getTotalExpiredCost() const;

	double getConsignmentExpiredCost(std::string const & _productName) const;

	/*-----------------------------------------------------------------*/

	void sell(std::string const & _productName, double _amount);

	/*-----------------------------------------------------------------*/

	void setCurrentDate(Date _date);

	/*-----------------------------------------------------------------*/

private:

	/*-----------------------------------------------------------------*/

	std::unordered_map<std::string, std::unique_ptr<ExpiryPolicy> > m_policies;
	std::unordered_map<std::string, std::unique_ptr<Consignment> > m_consignments;

	Date m_currentDate = Date();
	/*-----------------------------------------------------------------*/


};

/*****************************************************************************/

#endif // _CONTROLLER_HPP_