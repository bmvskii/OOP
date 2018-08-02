// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "controller.hpp"
#include "messages.hpp"
#include "asset.hpp"
#include "realestateasset.hpp"
#include "vehicleasset.hpp"
#include "owner.hpp"

/*****************************************************************************/

Controller::Controller() = default;

/*****************************************************************************/

Controller::~Controller() = default;

/*****************************************************************************/

void Controller::createOwner(std::string const & _fullName)
{
	if (_fullName.empty())
		throw std::logic_error(Messages::OwnerNameEmpty);

	if (m_owners.find(_fullName) != m_owners.end())
		throw std::logic_error(Messages::OwnerNameNotUnique);

	m_owners.insert(std::make_pair(_fullName,std::make_unique<Owner>(_fullName)));
}

/*****************************************************************************/

void Controller::addRealEstate(
	std::string const & _ownerFullName,
	std::string const & _assetName,
	double _baseCost,
	RealEstateState _initialState
)
{
	auto it = m_owners.find(_ownerFullName);
	if (it == m_owners.end())
		throw std::logic_error(Messages::OwnerUnknown);

	if (it->second->hasAsset(_assetName))
		throw std::logic_error(Messages::AssetNameNotUniqueWithinOwner);

	if (_baseCost < 0)
		throw std::logic_error(Messages::NegativeAssetBaseCost);

	if (_assetName.empty())
		throw std::logic_error(Messages::AssetNameEmpty);

	it->second->addAsset(_assetName, std::make_unique<RealEstateAsset>(_assetName, _baseCost, _initialState));
}

/*****************************************************************************/

void Controller::addVehicle(
	std::string const & _ownerFullName,
	std::string const & _assetName,
	double _baseCost,
	int _yearsInUse,
	bool _hadAccidents
)
{
	auto it = m_owners.find(_ownerFullName);
	if (it == m_owners.end())
		throw std::logic_error(Messages::OwnerUnknown);

	if (it->second->hasAsset(_assetName))
		throw std::logic_error(Messages::AssetNameNotUniqueWithinOwner);

	if (_baseCost < 0)
		throw std::logic_error(Messages::NegativeAssetBaseCost);

	if (_yearsInUse < 0)
		throw std::logic_error(Messages::NegativeVehicleUseYears);

	if (_assetName.empty())
		throw std::logic_error(Messages::AssetNameEmpty);

	it->second->addAsset(_assetName, std::make_unique<VehicleAsset>(_assetName, _baseCost, _yearsInUse, _hadAccidents));
}

/*****************************************************************************/

std::unordered_set<std::string> Controller::getOwnerAssetNames(std::string const & _ownerFullName) const
{
	std::unordered_set<std::string> result;

	auto it = m_owners.find(_ownerFullName);
	if (it == m_owners.end())
		throw std::logic_error(Messages::OwnerUnknown);

	it->second->forEachAsset(
		[&](Asset const & _asset)
	{
		result.insert(_asset.getName());
	}
	);

	return result;
}

/*****************************************************************************/

double Controller::getOwnerAssetsCurrentCost(std::string const & _ownerFullName) const
{
	double total = 0;
	
	auto it = m_owners.find(_ownerFullName);
	if (it == m_owners.end())
		throw std::logic_error(Messages::OwnerUnknown);
	
	it->second->forEachAsset(
		[&](Asset const & _asset)
	{
		total += _asset.getCost();
	}
	);

	return total;
}

/*****************************************************************************/

double Controller::getAssetBaseCost(std::string const & _ownerFullName, std::string const & _assetName) const
{
	auto it = m_owners.find(_ownerFullName);
	if (it == m_owners.end())
		throw std::logic_error(Messages::OwnerUnknown);

	if (!it->second->hasAsset(_assetName))
		throw std::logic_error(Messages::AssetUnknown);

	return it->second->getAsset(_assetName)->getStartCost();
}

/*****************************************************************************/

double Controller::getAssetCurrentCost(std::string const & _ownerFullName, std::string const & _assetName) const
{
	auto it = m_owners.find(_ownerFullName);
	if (it == m_owners.end())
		throw std::logic_error(Messages::OwnerUnknown);

	if (!it->second->hasAsset(_assetName))
		throw std::logic_error(Messages::AssetUnknown);

	return it->second->getAsset(_assetName)->getCost();
}

/*****************************************************************************/

void Controller::repair(std::string const & _ownerFullName, std::string const & _assetName)
{
	auto it = m_owners.find(_ownerFullName);
	if (it == m_owners.end())
		throw std::logic_error(Messages::OwnerUnknown);

	if (!it->second->hasAsset(_assetName))
		throw std::logic_error(Messages::AssetUnknown);

	it->second->getAsset(_assetName)->repair();
}

/*****************************************************************************/

void Controller::damage(std::string const & _ownerFullName, std::string const & _assetName)
{
	auto it = m_owners.find(_ownerFullName);
	if (it == m_owners.end())
		throw std::logic_error(Messages::OwnerUnknown);

	if (!it->second->hasAsset(_assetName))
		throw std::logic_error(Messages::AssetUnknown);

	it->second->getAsset(_assetName)->damage();
}

/*****************************************************************************/

RealEstateState Controller::getRealEstateState(std::string const & _ownerFullName, std::string const & _assetName) const
{
	auto it = m_owners.find(_ownerFullName);
	if (it == m_owners.end())
		throw std::logic_error(Messages::OwnerUnknown);

	if (!it->second->hasAsset(_assetName))
		throw std::logic_error(Messages::AssetUnknown);

	auto asset = dynamic_cast<RealEstateAsset *>(it->second->getAsset(_assetName));
	if (asset == nullptr)
		throw std::logic_error(Messages::NotRealEstateAsset);

	return asset->getState();
}

/*****************************************************************************/

int Controller::getVehicleYearsInUse(std::string const & _ownerFullName, std::string const & _assetName) const
{
	auto it = m_owners.find(_ownerFullName);
	if (it == m_owners.end())
		throw std::logic_error(Messages::OwnerUnknown);

	if (!it->second->hasAsset(_assetName))
		throw std::logic_error(Messages::AssetUnknown);

	auto asset = dynamic_cast<VehicleAsset *>(it->second->getAsset(_assetName));
	if (asset == nullptr)
		throw std::logic_error(Messages::NotVehicleAsset);

	return asset->getYears();
}

/*****************************************************************************/

bool Controller::isVehicleCrashed(std::string const & _ownerFullName, std::string const & _assetName) const
{
	auto it = m_owners.find(_ownerFullName);
	if (it == m_owners.end())
		throw std::logic_error(Messages::OwnerUnknown);

	auto asset = dynamic_cast<VehicleAsset *>(it->second->getAsset(_assetName));
	if (asset == nullptr)
		throw std::logic_error(Messages::NotVehicleAsset);

	return asset->isDamaged();
}

/*****************************************************************************/