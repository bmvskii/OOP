// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "subsidizedwaterconsumer.hpp"
#include "messages.hpp"

/*****************************************************************************/

SubsidizedWaterConsumer::SubsidizedWaterConsumer(
	int _consumerID,
	std::string const & _fullOwnerName,
	std::string const & _address
)
	: WaterConsumer(_consumerID, _address, _fullOwnerName)
{}

/*****************************************************************************/

void SubsidizedWaterConsumer::payment(double _cost)
{
	throw std::logic_error(Messages::SubsidizedConsumersDontPay);
}

/*****************************************************************************/

void SubsidizedWaterConsumer::usingWater(double _amount)
{
	return;
}

/*****************************************************************************/

double SubsidizedWaterConsumer::getDebt(double _cost)
{
	return 0.0;
}

/*****************************************************************************/