// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "owner.hpp"
#include "asset.hpp"

/*****************************************************************************/

Owner::Owner(std::string const & _name)
	: m_name(_name)
{}

/*****************************************************************************/

Owner::~Owner() = default;

/*****************************************************************************/

void Owner::addAsset(
	std::string const & _assetName,
	std::unique_ptr<Asset> _asset
)
{
	m_assets.insert(std::make_pair(_assetName, std::move(_asset)));
}

/*****************************************************************************/

void Owner::forEachAsset(std::function<void(Asset const & _asset)>_func) const
{
	for (auto const & asset : m_assets)
		_func(*asset.second.get());
}

/*****************************************************************************/