// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _SUBSIDIZEDWATERCONSUMER_HPP_
#define _SUBSIDIZEDWATERCONSUMER_HPP_

/*****************************************************************************/

#include "waterconsumer.hpp"

/*****************************************************************************/


class SubsidizedWaterConsumer
	: public WaterConsumer
{

	/*-----------------------------------------------------------------*/
public:

	SubsidizedWaterConsumer(
		int _consumerID,
		std::string const & _fullOwnerName,
		std::string const & _address
	);

	~SubsidizedWaterConsumer() = default;

	void payment(double _amount) override;

	void usingWater(double _amount) override;

	double getDebt(double _cost) override;

private:

	/*-----------------------------------------------------------------*/


};


/*****************************************************************************/

#endif // _SUBSIDIZEDWATERCONSUMER_HPP_