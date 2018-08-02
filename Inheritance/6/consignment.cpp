// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "consignment.hpp"
#include "expirypolicy.hpp"

/*****************************************************************************/

Consignment::Consignment(
	std::string const & _name,
	double _weight,
	double _cost,
	Date const & _date,
	ExpiryPolicy & _e
)
	: m_name(_name)
	, m_weigth(_weight)
	, m_cost(_cost)
	, m_date(_date)
	, m_rule(_e)
{}

/*****************************************************************************/

double Consignment::getCostFresh() const
{
	return (m_cost - (m_cost*m_rule.getSalePercetage(*this))) * m_weigth;
}

/*****************************************************************************/

bool Consignment::isBadProduct() const
{
	return m_rule.isBadConsignment(*this);
}

/*****************************************************************************/