// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "manualteapot.hpp"
#include "messages.hpp"

/*****************************************************************************/

ManualTeapot::ManualTeapot(
	int _maxVolume,
	int _boilingSpeed
)
	: Teapot(_maxVolume,_boilingSpeed)
	, m_boiledWaterVolume(0)
	, m_currentWastedWarnings(0)
{}

/*****************************************************************************/

void ManualTeapot::waterBoilingReaction()
{
	takeWater(m_boiledWaterVolume);
}

/*****************************************************************************/

void ManualTeapot::waterAbsenceReaction()
{
	if (m_currentWastedWarnings < MAX_NUMBER_OF_WARNINGS)
		m_currentWastedWarnings++;
	
	if (m_currentWastedWarnings == MAX_NUMBER_OF_WARNINGS)
		throw std::exception(Messages::TeapotAlmostBurned);
}

/*****************************************************************************/

void ManualTeapot::addWater(int _volume)
{
	Teapot::addWater(_volume);
	m_boiledWaterVolume = getCurrentWaterVolume() * 0.05;
}

/*****************************************************************************/

void ManualTeapot::takeWater(int _volume)
{
	Teapot::takeWater(_volume);
}

/*****************************************************************************/