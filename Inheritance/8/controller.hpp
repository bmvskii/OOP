// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _CONTROLLER_HPP_
#define _CONTROLLER_HPP_

/*****************************************************************************/

#include <unordered_map>
#include <memory>

class Teapot;

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

	void createManualTeapot(int _maxVolume, int _speed);

	void createAutomaticTeapot(int _maxVolume, int _speed);

	/*-----------------------------------------------------------------*/

	int getTeapotCurrentVolume(int _teapotIndex) const;

	int getTeapotMaxVolume(int _teapotIndex) const;

	int getTeapotCurrentTemperature(int _teapotIndex) const;

	int getTeapotBoilingSpeed(int _teapotIndex) const;

	/*-----------------------------------------------------------------*/

	bool isTeapotOn(int _teapotIndex) const;

	void turnOnTeapot(int _teapotIndex);

	void turnOffTeapot(int _teapotIndex);

	/*-----------------------------------------------------------------*/

	void addWater(int _teapotIndex, int _volume);

	void takeWater(int _teapotIndex, int _volume);

	/*-----------------------------------------------------------------*/

	void wait(int _minutesCount);

	/*-----------------------------------------------------------------*/

private:

	/*-----------------------------------------------------------------*/

	std::unordered_map<int /*index*/, std::unique_ptr<Teapot>> m_teapots;

	int m_nTeapotCounter;

	/*-----------------------------------------------------------------*/

};

/*****************************************************************************/

#endif // _CONTROLLER_HPP_