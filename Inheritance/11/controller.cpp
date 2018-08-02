// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "controller.hpp"
#include "messages.hpp"
#include "countingwaterconsumer.hpp"
#include "standartwaterconsumer.hpp"
#include "subsidizedwaterconsumer.hpp"
#include "waterconsumer.hpp"

/*****************************************************************************/

Controller::Controller() = default;

/*****************************************************************************/

Controller::~Controller() = default;

/*****************************************************************************/

void Controller::createCountedConsumer(
	int _consumerID
	, std::string const & _consumerName
	, std::string const & _consumerAddress
)
{
	if (_consumerAddress.empty())
		throw std::logic_error(Messages::EmptyConsumerAddress);

	if (_consumerName.empty())
		throw std::logic_error(Messages::EmptyConsumerName);

	if (_consumerID < 0)
		throw std::logic_error(Messages::NegativeConsumerID);

	if (m_clients.find(_consumerID) != m_clients.end())
		throw std::logic_error(Messages::NonUniqueConsumerID);

	m_clients.insert(std::make_pair(
		_consumerID,
		std::make_unique<CountingWaterConsumer>(
			_consumerID,
			_consumerName,
			_consumerAddress
			)
		)
	);
}

/*****************************************************************************/

void Controller::createStandardConsumer(
	int _consumerID
	, std::string const & _consumerName
	, std::string const & _consumerAddress
	, int _nUsers
)
{
	if (_consumerAddress.empty())
		throw std::logic_error(Messages::EmptyConsumerAddress);

	if (_consumerName.empty())
		throw std::logic_error(Messages::EmptyConsumerName);

	if (_consumerID < 0)
		throw std::logic_error(Messages::NegativeConsumerID);

	if (_nUsers < 1)
		throw std::logic_error(Messages::NonPositiveUsersCount);

	if (m_clients.find(_consumerID) != m_clients.end())
		throw std::logic_error(Messages::NonUniqueConsumerID);

	m_clients.insert(std::make_pair(
		_consumerID,
		std::make_unique<StandartWaterConsumer>(
			_consumerID,
			_consumerName,
			_consumerAddress,
			_nUsers
			)
	)
	);
}

/*****************************************************************************/

void Controller::createSubsidizedConsumer(
	int _consumerID
	, std::string const & _consumerName
	, std::string const & _consumerAddress
)
{
	if (_consumerAddress.empty())
		throw std::logic_error(Messages::EmptyConsumerAddress);

	if (_consumerName.empty())
		throw std::logic_error(Messages::EmptyConsumerName);

	if (_consumerID < 0)
		throw std::logic_error(Messages::NegativeConsumerID);

	if (m_clients.find(_consumerID) != m_clients.end())
		throw std::logic_error(Messages::NonUniqueConsumerID);

	m_clients.insert(std::make_pair(
		_consumerID,
		std::make_unique<SubsidizedWaterConsumer>(
			_consumerID,
			_consumerName,
			_consumerAddress
			)
	)
	);
}

/*****************************************************************************/

void Controller::useWater(int _consumerID, double _volumeM3)
{
	auto it = m_clients.find(_consumerID);
	if (it == m_clients.end())
		throw std::logic_error(Messages::UnknownConsumerID);

	if (_volumeM3 < 1)
		throw std::logic_error(Messages::NonPositiveConsumption);

	it->second->usingWater(_volumeM3);
}

/*****************************************************************************/

double Controller::getConsumerDebt(int _consumerID, double _price) const
{
	auto it = m_clients.find(_consumerID);
	if (it == m_clients.end())
		throw std::logic_error(Messages::UnknownConsumerID);

	if (_price < 0)
		throw std::logic_error(Messages::NegativePrice);

	return it->second->getDebt(_price);
}

/*****************************************************************************/

double Controller::getTotalDebt(double _price) const
{
	double total = 0;
	if (_price < 0)
		throw std::logic_error(Messages::NegativePrice);

	for (auto const & c : m_clients)
		total += c.second->getDebt(_price);

	return total;
}

/*****************************************************************************/

void Controller::trackConsumerPayment(int _consumerID, double _amount)
{
	auto it = m_clients.find(_consumerID);
	if (it == m_clients.end())
		throw std::logic_error(Messages::UnknownConsumerID);

	if (_amount < 1)
		throw std::logic_error(Messages::NonPositivePaymentAmount);

	it->second->payment(_amount);
}

/*****************************************************************************/
