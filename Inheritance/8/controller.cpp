// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "controller.hpp"
#include "messages.hpp"
#include "teapot.hpp"
#include "automaticteapot.hpp"
#include "manualteapot.hpp"

/*****************************************************************************/

Controller::Controller()
	: m_nTeapotCounter(0)
{}

/*****************************************************************************/

Controller::~Controller() = default;

/*****************************************************************************/

void Controller::createManualTeapot(int _maxVolume, int _speed)
{
	if (_maxVolume < 1)
		throw std::logic_error(Messages::NonPositiveVolume);

	if (_speed < 1)
		throw std::logic_error(Messages::NonPositiveSpeed);

	m_teapots.insert(std::make_pair(m_nTeapotCounter++,std::make_unique<ManualTeapot>(_maxVolume,_speed)));
}

/*****************************************************************************/

void Controller::createAutomaticTeapot(int _maxVolume, int _speed)
{
	if (_maxVolume < 1)
		throw std::logic_error(Messages::NonPositiveVolume);

	if (_speed < 1)
		throw std::logic_error(Messages::NonPositiveSpeed);

	m_teapots.insert(std::make_pair(m_nTeapotCounter++, std::make_unique<AutomaticTeapot>(_maxVolume, _speed)));
}

/*****************************************************************************/

int Controller::getTeapotCurrentVolume(int _teapotIndex) const
{
	auto it = m_teapots.find(_teapotIndex);
	if (it == m_teapots.end())
		throw std::logic_error(Messages::WrongTeapotIndex);

	return it->second->getCurrentWaterVolume();
}

/*****************************************************************************/

int Controller::getTeapotMaxVolume(int _teapotIndex) const
{
	auto it = m_teapots.find(_teapotIndex);
	if (it == m_teapots.end())
		throw std::logic_error(Messages::WrongTeapotIndex);

	return it->second->getMaxWaterVolume();
}

/*****************************************************************************/

int Controller::getTeapotCurrentTemperature(int _teapotIndex) const
{
	auto it = m_teapots.find(_teapotIndex);
	if (it == m_teapots.end())
		throw std::logic_error(Messages::WrongTeapotIndex);

	return it->second->getCurrentTemperature();
}

/*****************************************************************************/

int Controller::getTeapotBoilingSpeed(int _teapotIndex) const
{
	auto it = m_teapots.find(_teapotIndex);
	if (it == m_teapots.end())
		throw std::logic_error(Messages::WrongTeapotIndex);

	return it->second->getBoilingSpeed();
}

/*****************************************************************************/

bool Controller::isTeapotOn(int _teapotIndex) const
{
	auto it = m_teapots.find(_teapotIndex);
	if (it == m_teapots.end())
		throw std::logic_error(Messages::WrongTeapotIndex);

	return it->second->getStatus();
}

/*****************************************************************************/

void Controller::turnOnTeapot(int _teapotIndex)
{
	auto it = m_teapots.find(_teapotIndex);
	if (it == m_teapots.end())
		throw std::logic_error(Messages::WrongTeapotIndex);

	it->second->turn(true);
}

/*****************************************************************************/

void Controller::turnOffTeapot(int _teapotIndex)
{
	auto it = m_teapots.find(_teapotIndex);
	if (it == m_teapots.end())
		throw std::logic_error(Messages::WrongTeapotIndex);

	it->second->turn(false);
}

/*****************************************************************************/

void Controller::addWater(int _teapotIndex, int _volume)
{
	auto it = m_teapots.find(_teapotIndex);
	if (it == m_teapots.end())
		throw std::logic_error(Messages::WrongTeapotIndex);

	if (_volume < 1)
		throw std::logic_error(Messages::NonPositiveVolume);

	if (it->second->getCurrentWaterVolume() + _volume > it->second->getMaxWaterVolume())
		throw std::logic_error(Messages::TeapotVolumeOverflow);

	if (it->second->getStatus())
		throw std::logic_error(Messages::TeapotIsNotModifiable);

	it->second->addWater(_volume);
}

/*****************************************************************************/

void Controller::takeWater(int _teapotIndex, int _volume)
{
	auto it = m_teapots.find(_teapotIndex);
	if (it == m_teapots.end())
		throw std::logic_error(Messages::WrongTeapotIndex);

	if (_volume < 1)
		throw std::logic_error(Messages::NonPositiveVolume);

	if (it->second->getCurrentWaterVolume() < _volume)
		throw std::logic_error(Messages::TeapotVolumeUnderflow);

	if (it->second->getStatus())
		throw std::logic_error(Messages::TeapotIsNotModifiable);

	it->second->takeWater(_volume);

}

/*****************************************************************************/

void Controller::wait(int _minutesCount)
{
	for (int i = 0; i < _minutesCount; i++)
		for (auto & teapot : m_teapots)
			teapot.second->updateState();
}

/*****************************************************************************/