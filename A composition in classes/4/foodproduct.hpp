// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _FOODPRODUCT_HPP_
#define _FOODPRODUCT_HPP_

/*****************************************************************************/

#include "foodcomponents.hpp"

#include <string>

/*****************************************************************************/


class FoodProduct
{

/*-----------------------------------------------------------------*/

public:

/*-----------------------------------------------------------------*/

	FoodProduct(
		std::string const & _name,
		FoodComponents const & _components,
		double _energyValue
	);

	~FoodProduct() = default;

	std::string const & getName() const;

	FoodComponents const & getComponents() const;

	double getEnergyValue() const;

/*-----------------------------------------------------------------*/

private:

/*-----------------------------------------------------------------*/
	
	std::string m_name;

	FoodComponents m_components;

	double m_energyValue;

/*-----------------------------------------------------------------*/

};

/*****************************************************************************/

inline
std::string const & FoodProduct::getName() const
{
	return m_name;
}

/*****************************************************************************/

inline
FoodComponents const & FoodProduct::getComponents() const
{
	return m_components;
}

/*****************************************************************************/

inline
double FoodProduct::getEnergyValue() const
{
	return m_energyValue;
}

/*****************************************************************************/

#endif //  _FOODPRODUCT_HPP_
