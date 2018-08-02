// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _REALESTATEASSET_HPP_
#define _REALESTATEASSET_HPP_

/*****************************************************************************/

#include "asset.hpp"
#include "realestatestate.hpp"

/*****************************************************************************/


class RealEstateAsset
	: public Asset
{

	/*-----------------------------------------------------------------*/

public:
	RealEstateAsset(
		std::string const & _name,
		double _cost,
		RealEstateState _state
	);

	~RealEstateAsset() = default;
	
	void damage() override;

	void repair() override;

	double getCost() const override;

	RealEstateState getState() const;

private:

	RealEstateState m_state;

	/*-----------------------------------------------------------------*/
};

/*****************************************************************************/

inline
RealEstateState RealEstateAsset::getState() const
{
	return m_state;
}

/*****************************************************************************/

#endif // _REALESTATEASSET_HPP_