// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "countingwaterconsumer.hpp"
#include <iostream>

/*****************************************************************************/

CountingWaterConsumer::CountingWaterConsumer(
	int _consumerID,
	std::string const & _fullOwnerName,
	std::string const & _address
)
	: WaterConsumer(_consumerID,_address,_fullOwnerName)
	, m_nUsingWater(0.0)
{}

/*****************************************************************************/

void CountingWaterConsumer::payment(double _cost)
{
	pay(_cost);
}

/*****************************************************************************/

void CountingWaterConsumer::usingWater(double _amount)
{
	m_nUsingWater += _amount;
}

/*****************************************************************************/

double CountingWaterConsumer::getDebt(double _cost)
{
	return m_nUsingWater * _cost - getPaymentSummary();
}

/*****************************************************************************/