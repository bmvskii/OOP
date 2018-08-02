// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "automaticteapot.hpp"

/*****************************************************************************/

AutomaticTeapot::AutomaticTeapot(
	int _maxVolume,
	int _boilingSpeed
)
	: Teapot(_maxVolume,_boilingSpeed)
{}

/*****************************************************************************/

void AutomaticTeapot::waterBoilingReaction()
{
	turn(false);
}

/*****************************************************************************/

void AutomaticTeapot::waterAbsenceReaction()
{
	turn(false);
}

/*****************************************************************************/

void AutomaticTeapot::addWater(int _volume)
{
	Teapot::addWater(_volume);
}

/*****************************************************************************/

void AutomaticTeapot::takeWater(int _volume)
{
	Teapot::takeWater(_volume);
}

/*****************************************************************************/