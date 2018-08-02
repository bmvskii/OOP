// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _MENU_HPP_
#define _MENU_HPP_

/*****************************************************************************/

#include <string>
#include <unordered_map>
#include <functional>
/*****************************************************************************/

class FoodProduct;

/*****************************************************************************/

class Menu
{

/*-----------------------------------------------------------------*/

public:

/*-----------------------------------------------------------------*/

	Menu(std::string const & _name);

	~Menu() = default;

	std::string const & getName() const;

	bool hasProduct(std::string const & _productName) const;

	FoodProduct const * getProduct(std::string const & _productName) const;

	int getProductWeight(std::string const & _productName) const;

	void changeProductWeight(std::string const & _productName, int _newWeight);

	void addProduct(FoodProduct const & _product, int _weight);

	void removeProduct(std::string const & _productName);

	void forEachProduct(std::function<void(FoodProduct const & _p, int _w)> _f) const;

/*-----------------------------------------------------------------*/

private:

/*-----------------------------------------------------------------*/

	std::string m_name;

	std::unordered_map<FoodProduct const *, int> m_products;

/*-----------------------------------------------------------------*/

};

/*****************************************************************************/

inline
std::string const & Menu::getName() const
{
	return m_name;
}

/*****************************************************************************/

#endif //  _MENU_HPP_
