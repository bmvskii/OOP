// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _CONTROLLER_HPP_
#define _CONTROLLER_HPP_

/*****************************************************************************/

#include <string>
#include <memory>
#include <unordered_map>

/*****************************************************************************/

class WaterConsumer;

class Controller
{

	/*-----------------------------------------------------------------*/

public:

	/*-----------------------------------------------------------------*/

	Controller();

	Controller(const Controller &) = delete;

	Controller & operator = (const Controller &) = delete;

	~Controller();

	/*-----------------------------------------------------------------*/

	void createCountedConsumer(
		int _consumerID
		, std::string const & _consumerName
		, std::string const & _consumerAddress
	);

	void createStandardConsumer(
		int _consumerID
		, std::string const & _consumerName
		, std::string const & _consumerAddress
		, int _nUsers
	);

	void createSubsidizedConsumer(
		int _consumerID
		, std::string const & _consumerName
		, std::string const & _consumerAddress
	);

	void useWater(int _consumerID, double _volumeM3);

	double getConsumerDebt(int _consumerID, double _price) const;

	double getTotalDebt(double _price) const;

	void trackConsumerPayment(int _consumerID, double _amount);

	/*-----------------------------------------------------------------*/

private:

	/*-----------------------------------------------------------------*/

	std::unordered_map<int, std::unique_ptr<WaterConsumer> > m_clients;

	/*-----------------------------------------------------------------*/

};


/*****************************************************************************/

#endif //  _CONTROLLER_HPP_