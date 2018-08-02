// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _CONSIGNMENT_HPP_
#define _CONSIGNMENT_HPP_

/*****************************************************************************/

#include <string>
#include "date.hpp"

class ExpiryPolicy;

class Consignment
{

	/*-----------------------------------------------------------------*/

public:

	Consignment(
		std::string const & _name,
		double _weight,
		double _cost,
		Date const & _date,
		ExpiryPolicy & _e
	);

	~Consignment() = default;

	std::string const & getName() const;

	double getWeigth() const;

	double getCostFresh() const;

	Date getDate() const;

	double getCostExpired() const;

	ExpiryPolicy & getExpiryPolicy() const;

	bool isBadProduct() const;

	double getPrice() const;

	void sell(double _amount);

private:

	std::string m_name;
	ExpiryPolicy & m_rule;	
	
	double m_weigth;
	double m_cost;

	Date m_date;

	/*-----------------------------------------------------------------*/

};

/*****************************************************************************/

inline
std::string const &
Consignment::getName() const
{
	return m_name;
}

/*****************************************************************************/

inline
double Consignment::getWeigth() const
{
	return m_weigth;
}

/*****************************************************************************/

inline
double Consignment::getCostExpired() const
{
	return m_cost * m_weigth;
}

/*****************************************************************************/

inline
Date Consignment::getDate() const
{
	return m_date;
}

/*****************************************************************************/

inline
ExpiryPolicy &
Consignment::getExpiryPolicy() const
{
	return m_rule;
}

/*****************************************************************************/

inline
double Consignment::getPrice() const
{
	return m_cost;
}

/*****************************************************************************/

inline
void Consignment::sell(double _amount)
{
	m_weigth -= _amount;
}

/*****************************************************************************/

#endif // _CONSIGNMENT_HPP_