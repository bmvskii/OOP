// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "menu.hpp"
#include "messages.hpp"
#include "foodproduct.hpp"

/*****************************************************************************/

Menu::Menu(std::string const & _name)
	: m_name(_name)
{}

/*****************************************************************************/

bool Menu::hasProduct(std::string const & _productName) const
{
	for (auto const & p : m_products)
		if (p.first->getName() == _productName)
			return true;
	return false;
}

/*****************************************************************************/

FoodProduct const * Menu::getProduct(std::string const & _productName) const
{
	for (auto const & p : m_products)
		if (p.first->getName() == _productName)
			return p.first;
	return nullptr;
}

/*****************************************************************************/

int Menu::getProductWeight(std::string const & _productName) const
{
	for (auto const & p : m_products)
		if (p.first->getName() == _productName)
			return p.second;
	return -1;
}

/*****************************************************************************/

void Menu::addProduct(FoodProduct const & _product, int _weight)
{
	m_products.insert(std::make_pair(&_product, _weight));
}

/*****************************************************************************/

void Menu::removeProduct(std::string const & _productName)
{
	for (auto & p : m_products)
		if (p.first->getName() == _productName)
		{
			m_products.erase(p.first);
			return;
		}
}

/*****************************************************************************/

void Menu::forEachProduct(std::function<void(FoodProduct const&_p, int _w)> _f) const
{
	for (auto const & p : m_products)
		_f(*p.first, p.second);
}

/*****************************************************************************/

void Menu::changeProductWeight(std::string const & _productName, int _newWeight)
{
	for (auto & p : m_products)
		if (p.first->getName() == _productName)
		{
			p.second = _newWeight;
			return;
		}
}

/*****************************************************************************/
