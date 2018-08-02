// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "controller.hpp"
#include "messages.hpp"
#include "foodproduct.hpp"
#include "menu.hpp"

#include <algorithm>

/*****************************************************************************/

Controller::Controller() = default;

/*****************************************************************************/

Controller::~Controller() = default;

/*****************************************************************************/

void Controller::createFoodProduct(std::string const & _productName, FoodComponents _components, double _energeticValue)
{
	if (_productName.empty())
		throw std::logic_error(Messages::EmptyProductName);

	if (m_products.find(_productName) != m_products.end())
		throw std::logic_error(Messages::ProductAlreadyExists);

	if (_energeticValue < 1)
		throw std::logic_error(Messages::NegativeEnergeticValue);

	m_products.insert(std::make_pair(_productName, std::make_unique<FoodProduct>(_productName, _components, _energeticValue)));
}

/*****************************************************************************/

FoodComponents Controller::getFoodProductComponents(std::string const & _productName) const
{
	if (m_products.find(_productName) == m_products.end())
		throw std::logic_error(Messages::ProductNotFound);

	return m_products.find(_productName)->second->getComponents();
}

/*****************************************************************************/

double Controller::getFoodProductEnergeticValue(std::string const & _productName) const
{
	if (m_products.find(_productName) == m_products.end())
		throw std::logic_error(Messages::ProductNotFound);

	return m_products.find(_productName)->second->getEnergyValue();
}

/*****************************************************************************/

void Controller::createMenu(std::string const & _menuName)
{
	if (_menuName.empty())
		throw std::logic_error(Messages::EmptyMenuTitle);

	if (m_menu.find(_menuName) != m_menu.end())
		throw std::logic_error(Messages::MenuAlreadyExists);

	m_menu.insert(std::make_pair(_menuName, std::make_unique<Menu>(_menuName)));
}

/*****************************************************************************/

void Controller::addProductToMenu(std::string const & _menuName, std::string const & _productName, int _weight)
{
	if (m_menu.find(_menuName) == m_menu.end())
		throw std::logic_error(Messages::MenuNotFound);

	if (m_products.find(_productName) == m_products.end())
		throw std::logic_error(Messages::ProductNotFound);

	if (m_menu.find(_menuName)->second->hasProduct(_productName))
		throw std::logic_error(Messages::ProductAlreadyIncluded);

	if (_weight < 1)
		throw std::logic_error(Messages::NonPositiveWeight);

	m_menu.find(_menuName)->second->addProduct(*m_products.find(_productName)->second.get(), _weight);
}

/*****************************************************************************/

void Controller::removeProductFromMenu(std::string const & _menuName, std::string const & _productName)
{
	if (m_menu.find(_menuName) == m_menu.end())
		throw std::logic_error(Messages::MenuNotFound);

	if (m_products.find(_productName) == m_products.end())
		throw std::logic_error(Messages::ProductNotFound);

	if (!m_menu.find(_menuName)->second->hasProduct(_productName))
		throw std::logic_error(Messages::ProductNotIncluded);

	m_menu.find(_menuName)->second->removeProduct(_productName);
}

/*****************************************************************************/

void Controller::updateProductWeightInMenu(std::string const & _menuName, std::string const & _productName, int _newWeight)
{
	if (m_menu.find(_menuName) == m_menu.end())
		throw std::logic_error(Messages::MenuNotFound);

	if (m_products.find(_productName) == m_products.end())
		throw std::logic_error(Messages::ProductNotFound);

	if (!m_menu.find(_menuName)->second->hasProduct(_productName))
		throw std::logic_error(Messages::ProductNotIncluded);
	
	if (_newWeight < 1)
		throw std::logic_error(Messages::NonPositiveWeight);

	m_menu.find(_menuName)->second->changeProductWeight(_productName, _newWeight);
}

/*****************************************************************************/

int Controller::getProductWeightInMenu(std::string const & _menuName, std::string const & _productName)
{
	if (m_menu.find(_menuName) == m_menu.end())
		throw std::logic_error(Messages::MenuNotFound);

	if (m_products.find(_productName) == m_products.end())
		throw std::logic_error(Messages::ProductNotFound);

	if (!m_menu.find(_menuName)->second->hasProduct(_productName))
		throw std::logic_error(Messages::ProductNotIncluded);

	return m_menu.find(_menuName)->second->getProductWeight(_productName);
}

/*****************************************************************************/

std::vector<std::string> Controller::getProductsInMenu(std::string const & _menuName) const
{
	if (m_menu.find(_menuName) == m_menu.end())
		throw std::logic_error(Messages::MenuNotFound);

	std::vector<std::string> products;

	m_menu.find(_menuName)->second->forEachProduct(
		[&](FoodProduct const & _p, int _w)
	{
		products.push_back(_p.getName());
	}
	);

	std::sort(products.begin(), products.end());

	return products;
}

/*****************************************************************************/

FoodComponents Controller::getTotalComponentsInMenu(std::string const & _menuName) const
{
	if (m_menu.find(_menuName) == m_menu.end())
		throw std::logic_error(Messages::MenuNotFound);

	double fat = 0.0, proteins = 0.0, carbo = 0.0;

	m_menu.find(_menuName)->second->forEachProduct(
		[&](FoodProduct const & _p, int _w)
	{
		fat += _p.getComponents().getFat() * (_w / 100);
		carbo += _p.getComponents().getCarbo() * (_w / 100);
		proteins += _p.getComponents().getProteins() * (_w / 100);
	});
		
	return FoodComponents(proteins,fat,carbo);
}

/*****************************************************************************/

double Controller::getMenuDailyEnergeticPercentage(std::string const & _menuName, double _dailyNorm) const
{
	if (m_menu.find(_menuName) == m_menu.end())
		throw std::logic_error(Messages::MenuNotFound);

	if (_dailyNorm < 1)
		throw std::logic_error(Messages::NegativeEnergeticValue);
	
	double total = 0.0;

	m_menu.find(_menuName)->second->forEachProduct(
		[&](FoodProduct const & _p, int _w)
	{
		total += _p.getEnergyValue() * (_w / 100);
	});

	total = (total / _dailyNorm) * 100;

	return total;
}

/*****************************************************************************/

std::string Controller::findProductWithMinimalFatWithEnergyOver(double _energeticValue) const
{
	if (_energeticValue < 0)
		throw std::logic_error(Messages::NegativeEnergeticValue);

	std::string minimalFat;
	double min = 100000000000000000;
	
	for (auto const & p : m_products)
		if (p.second->getEnergyValue() > _energeticValue && p.second->getComponents().getFat() < min)
		{
			min = p.second->getComponents().getFat();
			minimalFat = p.first;
		}

	return minimalFat;
}

/*****************************************************************************/

std::string Controller::findMenuWithBiggestWeight() const
{
	std::string biggestWeight;
	int max = 0;

	for (auto const & m : m_menu)
	{
		int total = 0;
		m.second->forEachProduct(
			[&](FoodProduct const & _p, int _w)
		{
			total += _w;
		});
		if (total > max)
		{
			max = total;
			biggestWeight = m.first;
		}
	}

	return biggestWeight;
}

/*****************************************************************************/