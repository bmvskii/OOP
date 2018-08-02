// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _OWNER_HPP_
#define _OWNER_HPP_

/*****************************************************************************/

#include <string>
#include <memory>
#include <unordered_map>
#include <functional>

class Asset;
class Owner
{

	/*-----------------------------------------------------------------*/

public:

	Owner(std::string const & _name);

	~Owner();

	void addAsset(
		std::string const & _assetName,
		std::unique_ptr<Asset> _asset
	);

	std::string const & getName() const;

	bool hasAsset(std::string const & _assetName) const;

	void forEachAsset(std::function<void(Asset const & _asset)>_func) const;

	Asset * getAsset(std::string const & _assetName) const;

private:

	std::string m_name;

	std::unordered_map<std::string, std::unique_ptr<Asset> > m_assets;

	/*-----------------------------------------------------------------*/
};

/*****************************************************************************/

inline
bool Owner::hasAsset(std::string const & _assetName) const
{
	return m_assets.find(_assetName) != m_assets.end();
}

/*****************************************************************************/

inline
std::string const &
Owner::getName() const
{
	return m_name;
}

/*****************************************************************************/

inline
Asset * Owner::getAsset(std::string const & _assetName) const
{
	return m_assets.find(_assetName)->second.get();
}

/*****************************************************************************/

#endif // _OWNER_HPP_