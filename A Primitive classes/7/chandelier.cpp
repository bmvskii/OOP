// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "chandelier.hpp"

#include <stdexcept>

/*****************************************************************************/

Chandelier::Chandelier(int _N)
{
	if (_N < 1)
		throw std::logic_error("Non-positive number of slots");

	m_slotsAmount = _N;
	m_slotsPower = new int[m_slotsAmount];
	m_powerMode = PowerMode::Power_Off;

	for (int i = 0; i < m_slotsAmount; i++) m_slotsPower[i] = 0;
}

/*****************************************************************************/

Chandelier::~Chandelier()
{
	delete[]m_slotsPower;
}

/*****************************************************************************/

Chandelier::Chandelier(const Chandelier & _c)
{
	m_powerMode = _c.m_powerMode;
	m_slotsAmount = _c.m_slotsAmount;

	m_slotsPower = new int[m_slotsAmount];
	for (int i = 0; i < m_slotsAmount; i++)
		m_slotsPower[i] = _c.m_slotsPower[i];
}

/*****************************************************************************/

Chandelier & Chandelier::operator=(const Chandelier & _c)
{
	if (this == &_c)
		return *this;

	m_powerMode = _c.m_powerMode;
	m_slotsAmount = _c.m_slotsAmount;

	m_slotsPower = new int[m_slotsAmount];
	for (int i = 0; i < m_slotsAmount; i++)
		m_slotsPower[i] = _c.m_slotsPower[i];

	return *this;
}

/*****************************************************************************/

Chandelier::Chandelier(Chandelier && _c)
{
	std::swap(m_powerMode, _c.m_powerMode);
	std::swap(m_slotsAmount, _c.m_slotsAmount);
	std::swap(m_slotsPower, _c.m_slotsPower);
}

/*****************************************************************************/

Chandelier & Chandelier::operator=(Chandelier && _c)
{
	if (this == &_c)
		return *this;

	std::swap(m_powerMode, _c.m_powerMode);
	std::swap(m_slotsAmount, _c.m_slotsAmount);
	std::swap(m_slotsPower, _c.m_slotsPower);

	return *this;
}

/*****************************************************************************/

int Chandelier::getTotalPower() const
{
	int total = 0;
	
	if (m_powerMode == PowerMode::Power_Off)
		return 0;
	else if (m_powerMode == PowerMode::Power_Full)
		for (int i = 0; i < m_slotsAmount; i++)
			total += m_slotsPower[i];
	else
	{
		int divider = m_powerMode == PowerMode::Power_Half ? 2 : 3;

		for (int i = 0; i < m_slotsAmount / divider; i++)
			total += m_slotsPower[i];
	}

	return total;
}

/*****************************************************************************/

std::ostream & operator<<(std::ostream & _s, const Chandelier & _c)
{
	if (_c.m_powerMode == Chandelier::PowerMode::Power_Off)
		_s << "()";
	else
	{
		_s << "(";
		for (int i = 0; i < _c.m_slotsAmount; i++)
		{
			if (_c.m_slotsPower[i] != 0)
			{
				_s << _c.m_slotsPower[i];
				if (i != _c.m_slotsAmount - 1)
					_s << "-";
			}
		}
		_s << ")";
	}

	return _s;
}

/*****************************************************************************/