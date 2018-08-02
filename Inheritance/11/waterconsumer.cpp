// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "waterconsumer.hpp"

/*****************************************************************************/

WaterConsumer::WaterConsumer(
	int _consumerID,
	std::string const & _fullOwnerName,
	std::string const & _address
)
	: m_consumerID(_consumerID)
	, m_consumerAddress(_address)
	, m_consumerFullName(_fullOwnerName)
	, m_paymentSummary(0.0)
{}

/*****************************************************************************/
