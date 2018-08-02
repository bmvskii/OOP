// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _TEAPOT_HPP_
#define _TEAPOT_HPP_

/*****************************************************************************/

static const int ROOM_TEMPERATURE = 20;

class Teapot
{

	/*-----------------------------------------------------------------*/
protected:

	Teapot(
		int _maxVolume,
		int _boilingSpeed
	);

public:

	virtual ~Teapot();

	virtual void waterBoilingReaction() = 0;

	virtual void waterAbsenceReaction() = 0;

	virtual void takeWater(int _volume);

	virtual void addWater(int _volume);

	virtual bool isImediatelyReaction() const = 0;
	
	void updateState();
	
	void turn(bool _status);

	int getCurrentWaterVolume() const;

	int getCurrentTemperature() const;

	int getMaxWaterVolume() const;

	int getBoilingSpeed() const;

	bool getStatus() const;

private:
	
	int m_maxWaterVolume;
	int m_boilingSpeed;

	int m_currentWaterVolume;
	int m_currentTemperature;

	bool m_status;

	/*-----------------------------------------------------------------*/
};

/*****************************************************************************/

inline
void Teapot::turn(bool _status)
{
	m_status = _status;
}

/*****************************************************************************/

inline
int Teapot::getCurrentWaterVolume() const
{
	return m_currentWaterVolume;
}

/*****************************************************************************/

inline
bool Teapot::getStatus() const
{
	return m_status;
}

/*****************************************************************************/

inline
int Teapot::getCurrentTemperature() const
{
	return m_currentTemperature;
}

/*****************************************************************************/

inline
int Teapot::getMaxWaterVolume() const
{
	return m_maxWaterVolume;
}

/*****************************************************************************/

inline
int Teapot::getBoilingSpeed() const
{
	return m_boilingSpeed;
}

/*****************************************************************************/

#endif // _TEAPOT_HPP_