// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "vehicleasset.hpp"
#include "messages.hpp"

/*****************************************************************************/

VehicleAsset::VehicleAsset(
	std::string const & _name,
	double _cost,
	int _years,
	bool _isDamaged
)
	: Asset(_name,_cost)
	, m_years(_years)
	, m_isDamaged(_isDamaged)
{}

/*****************************************************************************/

void VehicleAsset::damage()
{
	m_isDamaged = true;
}

/*****************************************************************************/

void VehicleAsset::repair()
{
	if (!m_isDamaged)
		throw std::logic_error(Messages::RepairingWorkingVehicle);
	m_isDamaged = false;
}

/*****************************************************************************/

double VehicleAsset::getCost() const
{
	double total = getStartCost();
	
	if (m_isDamaged)
		total /= 2;

	for (int i = 0; i < m_years; i++)
		total -= total * 0.15;

	return total;
}

/*****************************************************************************/