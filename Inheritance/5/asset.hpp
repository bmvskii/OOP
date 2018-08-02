// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _ASSET_HPP_
#define _ASSET_HPP_

#include <string>

/*****************************************************************************/


class Asset
{

	/*-----------------------------------------------------------------*/
protected:

	Asset(
		std::string const & _name,
		double _cost
	);

public:

	virtual ~Asset() = default;

	virtual double getCost() const = 0;

	virtual void damage() = 0;

	virtual void repair() = 0;

	double getStartCost() const;

	std::string const & getName() const;

private:

	double m_cost;

	std::string m_name;

	/*-----------------------------------------------------------------*/

};

/*****************************************************************************/

inline
double Asset::getStartCost() const
{
	return m_cost;
}

/*****************************************************************************/

inline
std::string const &
Asset::getName() const
{
	return m_name;
}

/*****************************************************************************/


#endif // _ASSET_HPP_