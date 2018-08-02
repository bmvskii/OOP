// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _WATERCONSUMER_HPP_
#define _WATERCONSUMER_HPP_

/*****************************************************************************/

#include <string>


class WaterConsumer
{

	/*-----------------------------------------------------------------*/

public:

	WaterConsumer(
		int _consumerID,
		std::string const & _fullOwnerName,
		std::string const & _address
	);

	virtual ~WaterConsumer() = default;

	virtual void payment(double _amount) = 0;

	virtual void usingWater(double _amount) = 0;

	virtual double getDebt(double _cost) = 0;

	void pay(double _amount);

	int getConsumerID() const;

	double getPaymentSummary() const;

	std::string const & getConsumerFullName() const;

	std::string const & getConsumerAddress() const;

private:

	int m_consumerID;
	double m_paymentSummary;
	std::string m_consumerFullName;
	std::string m_consumerAddress;

	/*-----------------------------------------------------------------*/


};

inline
void WaterConsumer::pay(double _amount)
{
	m_paymentSummary += _amount;
}

inline
int WaterConsumer::getConsumerID() const
{
	return m_consumerID;
}

/*****************************************************************************/

inline
double WaterConsumer::getPaymentSummary() const
{
	return m_paymentSummary;
}

/*****************************************************************************/

inline
std::string const &
WaterConsumer::getConsumerFullName() const
{
	return m_consumerFullName;
}

/*****************************************************************************/

inline
std::string const &
WaterConsumer::getConsumerAddress() const
{
	return m_consumerAddress;
}

/*****************************************************************************/


#endif // _WATERCONSUMER_HPP_