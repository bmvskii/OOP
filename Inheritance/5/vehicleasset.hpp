// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _VEHICLEASSET_HPP_
#define _VEHICLEASSET_HPP_

/*****************************************************************************/

#include "asset.hpp"

/*****************************************************************************/


class VehicleAsset
	: public Asset
{

	/*-----------------------------------------------------------------*/

public:

	VehicleAsset(
		std::string const & _name,
		double _cost,
		int _years,
		bool _isDamaged
	);

	~VehicleAsset() = default;

	void damage() override;

	void repair() override;

	double getCost() const override;

	int getYears() const;

	bool isDamaged() const;

private:

	int m_years;

	bool m_isDamaged;

	/*-----------------------------------------------------------------*/
};

/*****************************************************************************/

inline
int VehicleAsset::getYears() const
{
	return m_years;
}

/*****************************************************************************/

inline
bool VehicleAsset::isDamaged() const
{
	return m_isDamaged;
}

/*****************************************************************************/

#endif // _VEHICLEASSET_HPP_