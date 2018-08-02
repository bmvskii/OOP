// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _CONTROLLER_HPP_
#define _CONTROLLER_HPP_

/*****************************************************************************/

#include "foodcomponents.hpp"

#include <vector>
#include <string>
#include <unordered_map>
#include <memory>

/*****************************************************************************/

class Menu;
class FoodProduct;

class Controller
{

/*-----------------------------------------------------------------*/

public:

/*-----------------------------------------------------------------*/

	Controller ();

	Controller ( const Controller & ) = delete;

	Controller & operator = ( const Controller & ) = delete;

	~ Controller ();

/*-----------------------------------------------------------------*/

	void createFoodProduct (
		std::string const & _productName, 
		FoodComponents _components,
		double _energeticValue
	);

	FoodComponents getFoodProductComponents ( std::string const & _productName ) const;

	double getFoodProductEnergeticValue ( std::string const & _productName ) const;

/*-----------------------------------------------------------------*/

	void createMenu ( std::string const & _menuName );

	void addProductToMenu (
		std::string const & _menuName,
		std::string const & _productName,
		int _weight
	);

	void removeProductFromMenu (
		std::string const & _menuName,
		std::string const & _productName
	);

	void updateProductWeightInMenu (
		std::string const & _menuName,
		std::string const & _productName,
		int _newWeight
	);

	int getProductWeightInMenu (
		std::string const & _menuName,
		std::string const & _productName
	);

	std::vector< std::string > getProductsInMenu ( std::string const & _menuName ) const;

/*-----------------------------------------------------------------*/

	FoodComponents getTotalComponentsInMenu ( std::string const & _menuName ) const;

	double getMenuDailyEnergeticPercentage ( 
		std::string const & _menuName, 
		double _dailyNorm = 2500.00
	) const;

	std::string findProductWithMinimalFatWithEnergyOver ( double _energeticValue ) const;

	std::string findMenuWithBiggestWeight () const;

/*-----------------------------------------------------------------*/

private:

/*-----------------------------------------------------------------*/

	std::unordered_map<std::string, std::unique_ptr<Menu> > m_menu;

	std::unordered_map<std::string, std::unique_ptr<FoodProduct>> m_products;

/*-----------------------------------------------------------------*/

};


/*****************************************************************************/

#endif //  _CONTROLLER_HPP_
