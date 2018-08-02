// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _STANDARDWATERCONSUMER_HPP_
#define _STANDARDWATERCONSUMER_HPP_

/*****************************************************************************/

#include "waterconsumer.hpp"

/*****************************************************************************/


class StandartWaterConsumer
	: public WaterConsumer
{

	/*-----------------------------------------------------------------*/
public:

	StandartWaterConsumer(
		int _consumerID,
		std::string const & _fullOwnerName,
		std::string const & _address,
		int _users
	);

	~StandartWaterConsumer() = default;

	void payment(double _amount) override;

	void usingWater(double _amount) override;

	double getDebt(double _cost) override;

	int getCohabitantsNumber() const;

private:

	int m_nCohabitants;

	/*-----------------------------------------------------------------*/


};

/*****************************************************************************/

inline
int StandartWaterConsumer::getCohabitantsNumber() const
{
	return m_nCohabitants;
}

/*****************************************************************************/

#endif // _STANDARDWATERCONSUMER_HPP_