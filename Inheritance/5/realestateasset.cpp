// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "realestateasset.hpp"
#include "messages.hpp"

/*****************************************************************************/

RealEstateAsset::RealEstateAsset(
	std::string const & _name,
	double _cost,
	RealEstateState _state
)
	: Asset(_name,_cost)
	, m_state(_state)
{}

/*****************************************************************************/

void RealEstateAsset::damage()
{
	switch (m_state)
	{
	case RealEstateState::Ideal:
		m_state = RealEstateState::CosmeticRepairs;
		break;
	case RealEstateState::CosmeticRepairs:
		m_state = RealEstateState::CapitalRepairs;
		break;
	case RealEstateState::CapitalRepairs:
		m_state = RealEstateState::Construction;
		break;
	case RealEstateState::Construction:
		break;
	default:
		break;
	}
}

/*****************************************************************************/

void RealEstateAsset::repair()
{
	switch (m_state)
	{
	case RealEstateState::Ideal:
		throw std::logic_error(Messages::RepairingIdealRealEstate);
		break;
	case RealEstateState::CosmeticRepairs:
		m_state = RealEstateState::Ideal;
		break;
	case RealEstateState::CapitalRepairs:
		m_state = RealEstateState::CosmeticRepairs;
		break;
	case RealEstateState::Construction:
		m_state = RealEstateState::CapitalRepairs;
		break;
	default:
		break;
	}
}

/*****************************************************************************/

double RealEstateAsset::getCost() const
{
	switch (m_state)
	{
	case RealEstateState::Ideal:
		return getStartCost();
		break;
	case RealEstateState::CosmeticRepairs:
		return getStartCost() - (getStartCost() * 0.15);
		break;
	case RealEstateState::CapitalRepairs:
		return getStartCost() - (getStartCost() * 0.3);
		break;
	case RealEstateState::Construction:
		return getStartCost() - (getStartCost() * 0.5);
		break;
	default:
		break;
	}
}

/*****************************************************************************/