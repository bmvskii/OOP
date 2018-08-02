// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _COUNTINGWATERCONSUMER_HPP_
#define _COUNTINGWATERCONSUMER_HPP_

/*****************************************************************************/

#include "waterconsumer.hpp"

/*****************************************************************************/


class CountingWaterConsumer
	: public WaterConsumer
{

	/*-----------------------------------------------------------------*/
public:

	CountingWaterConsumer(
		int _consumerID,
		std::string const & _fullOwnerName,
		std::string const & _address
	);

	~CountingWaterConsumer() = default;

	void payment(double _amount) override;

	void usingWater(double _amount) override;

	double getDebt(double _cost) override;

private:

	double m_nUsingWater;

	/*-----------------------------------------------------------------*/
};


/*****************************************************************************/

#endif // _COUNTINGWATERCONSUMER_HPP_