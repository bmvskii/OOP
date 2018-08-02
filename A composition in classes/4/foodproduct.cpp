// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "foodproduct.hpp"
#include "messages.hpp"

/*****************************************************************************/

FoodProduct::FoodProduct(
	std::string const & _name,
	FoodComponents const & _components,
	double _energyValue
)
	: m_name(_name)
	, m_components(_components)
	, m_energyValue(_energyValue)
{}

/*****************************************************************************/
