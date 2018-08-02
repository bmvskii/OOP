// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "teapot.hpp"

/*****************************************************************************/

Teapot::Teapot(
	int _maxVolume,
	int _boilingSpeed
)
	: m_boilingSpeed(_boilingSpeed)
	, m_maxWaterVolume(_maxVolume)
	, m_currentTemperature(ROOM_TEMPERATURE)
	, m_currentWaterVolume(0)
	, m_status(false)
{}

/*****************************************************************************/

Teapot::~Teapot() = default;

/*****************************************************************************/

void Teapot::updateState()
{
	if (m_status)
	{
		if (m_currentWaterVolume == 0)
			waterAbsenceReaction();
			
		else if (m_currentTemperature < 100)
		{
			m_currentTemperature += m_boilingSpeed;
			if (isImediatelyReaction() && m_currentTemperature >= 100)
				waterBoilingReaction();
		}

		else if (m_currentTemperature >= 100)
			waterBoilingReaction();
	}
	else
		if (m_currentTemperature > ROOM_TEMPERATURE)
			m_currentTemperature -= 2;
	
}

/*****************************************************************************/

void Teapot::addWater(int _volume)
{
	m_currentWaterVolume += _volume;
}

/*****************************************************************************/

void Teapot::takeWater(int _volume)
{
	m_currentWaterVolume -= _volume;
}

/*****************************************************************************/