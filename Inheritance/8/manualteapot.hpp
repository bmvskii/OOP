// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _MANUALTEAPOT_HPP_
#define _MANUALTEAPOT_HPP_

/*****************************************************************************/

#include "teapot.hpp"
#include <exception>

/*****************************************************************************/

static const int MAX_NUMBER_OF_WARNINGS = 3;

class ManualTeapot
	: public Teapot
{

	/*-----------------------------------------------------------------*/
public:

	ManualTeapot(
		int _maxVolume,
		int _boilingSpeed
	);

	~ManualTeapot() = default;

	void waterBoilingReaction() override;

	void waterAbsenceReaction() override;

	void addWater(int _volume) override;

	void takeWater(int _volume) override;

	bool isImediatelyReaction() const override;

private:

	int m_currentWastedWarnings;
	int m_boiledWaterVolume;
	
	/*-----------------------------------------------------------------*/

};

inline
bool ManualTeapot::isImediatelyReaction() const
{
	return false;
}

/*****************************************************************************/

#endif // _MANUALTEAPOT_HPP_