// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _AUTOMATICTEAPOT_HPP_
#define _AUTOMATICTEAPOT_HPP_

/*****************************************************************************/

#include "teapot.hpp"

/*****************************************************************************/

class AutomaticTeapot
	: public Teapot
{

	/*-----------------------------------------------------------------*/
public:

	AutomaticTeapot(
		int _maxVolume,
		int _boilingSpeed
	);

	~AutomaticTeapot() = default;

	void waterBoilingReaction() override;

	void waterAbsenceReaction() override;

	void addWater(int _volume) override;

	void takeWater(int _volume) override;

	bool isImediatelyReaction() const override;

	/*-----------------------------------------------------------------*/

};

inline
bool AutomaticTeapot::isImediatelyReaction() const
{
	return true;
}

/*****************************************************************************/

#endif // _AUTOMATICTEAPOT_HPP_