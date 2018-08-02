// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "standartwaterconsumer.hpp"
#include "constants.hpp"

/*****************************************************************************/

StandartWaterConsumer::StandartWaterConsumer(
	int _consumerID,
	std::string const & _fullOwnerName,
	std::string const & _address,
	int _users
)
	: WaterConsumer(_consumerID, _address, _fullOwnerName)
	, m_nCohabitants(_users)
{}

/*****************************************************************************/

void StandartWaterConsumer::payment(double _cost)
{
	pay(_cost);
}

/*****************************************************************************/

void StandartWaterConsumer::usingWater(double _amount)
{
	return;
}

/*****************************************************************************/

double StandartWaterConsumer::getDebt(double _cost)
{
	return m_nCohabitants * StandardWaterConsumptionPerUser * _cost - getPaymentSummary();
}

/*****************************************************************************/