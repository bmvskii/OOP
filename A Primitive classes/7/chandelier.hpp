// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _CHANDELIER_HPP_
#define _CHANDELIER_HPP_

/*****************************************************************************/

#include <iostream>

/*****************************************************************************/


class Chandelier
{

/*-----------------------------------------------------------------*/

public:

/*------------------------------------------------------------------*/

	enum PowerMode
	{
		Power_Off,
		Power_Full,
		Power_Half,
		Power_Third
	};

/*------------------------------------------------------------------*/

public:

	Chandelier(int _N);

	~Chandelier();

	Chandelier(const Chandelier & _c);

	Chandelier & operator = (const Chandelier & _c);

	Chandelier(Chandelier && _c);

	Chandelier & operator = (Chandelier && _c);

	int getSlotsCount() const;

	PowerMode getPowerMode() const;

	void setPowerMode(PowerMode _new);

	int getSlotPower(int _index) const;

	void setSlotPower(int _index, int _newPower);

	int getTotalPower() const;

	friend std::ostream & operator << (std::ostream & _s, const Chandelier & _c);

private:

	int m_slotsAmount;
	
	int * m_slotsPower;

	PowerMode m_powerMode;
/*------------------------------------------------------------------*/

};

/*****************************************************************************/

inline
int Chandelier::getSlotsCount() const
{
	return m_slotsAmount;
}

/*****************************************************************************/

inline
Chandelier::PowerMode Chandelier::getPowerMode() const
{
	return m_powerMode;
}

/*****************************************************************************/

inline
void Chandelier::setPowerMode(PowerMode _new)
{
	m_powerMode = _new;
}

/*****************************************************************************/

inline
int Chandelier::getSlotPower(int _index) const
{
	if (_index < 0 || _index >= m_slotsAmount)
		throw std::logic_error("Out of range");
		
	return m_slotsPower[_index];
}

/*****************************************************************************/

inline
void Chandelier::setSlotPower(int _index, int _newPower)
{
	if (_index < 0 || _index >= m_slotsAmount)
		throw std::logic_error("Out of range");

	if (_newPower < 0)
		throw std::logic_error("Negative power");

	m_slotsPower[_index] = _newPower;
}

/*****************************************************************************/

#endif //  _CHANDELIER_HPP_
