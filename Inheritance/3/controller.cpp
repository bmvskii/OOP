// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "controller.hpp"
#include "messages.hpp"
#include "program.hpp"
#include "license.hpp"
#include "perpetuallicense.hpp"
#include "tokenbasedlicense.hpp"
#include "timebasedlicense.hpp"

Controller::Controller() = default;

Controller::~Controller() = default;

void Controller::createProgram(
	std::string const & _name,
	std::string const & _vendorName
)
{
	if (_name.empty())
		throw std::logic_error(Messages::ProgramNameEmpty);

	if (_vendorName.empty())
		throw std::logic_error(Messages::VendorNameEmpty);

	auto it = m_apps.find(_name);
	if (it != m_apps.end())
		throw std::logic_error(Messages::ProgramNameNotUnique);

	m_apps.insert(std::make_pair(_name, std::make_unique<Program>(_name, _vendorName)));
}

std::string const &
Controller::getProgramVendor(std::string const & _programName) const
{
	auto it = m_apps.find(_programName);
	if (it == m_apps.end())
		throw std::logic_error(Messages::ProgramNotRegistered);

	return it->second->getFirmName();
}

void Controller::createPerpetualLicense(
	std::string const & _programName,
	Date _issued
)
{
	auto it = m_apps.find(_programName);
	if (it == m_apps.end())
		throw std::logic_error(Messages::ProgramNotRegistered);

	if (it->second->hasLicense())
		throw std::logic_error(Messages::DuplicateLicense);

	auto license = std::make_unique<PerpetualLicense>(_issued);
	it->second->addLicense(std::move(license));
}

void Controller::createTimeBasedLicense(
	std::string const & _programName,
	Date _issued,
	Date _expires
)
{
	auto it = m_apps.find(_programName);
	if (it == m_apps.end())
		throw std::logic_error(Messages::ProgramNotRegistered);

	if (it->second->hasLicense())
		throw std::logic_error(Messages::DuplicateLicense);

	if (_issued > _expires)
		throw std::logic_error(Messages::ExpiryEarlierThanIssue);

	auto license = std::make_unique<TimeBasedLicense>(_issued, _expires);
	it->second->addLicense(std::move(license));
}

void Controller::createTokenBasedLicense(
	std::string const & _programName,
	Date _issued,
	int _nTokens
)
{
	auto it = m_apps.find(_programName);
	if (it == m_apps.end())
		throw std::logic_error(Messages::ProgramNotRegistered);

	if (_nTokens < 1)
		throw std::logic_error(Messages::NonPositiveTokens);

	if (it->second->hasLicense())
		throw std::logic_error(Messages::DuplicateLicense);

	auto license = std::make_unique<TokenBasedLicense>(_issued, _nTokens);
	it->second->addLicense(std::move(license));
}

LicenseType Controller::getProgramLicenseType(const std::string & _programName) const
{
	auto it = m_apps.find(_programName);
	if (it == m_apps.end())
		throw std::logic_error(Messages::ProgramNotRegistered);

	return it->second->hasLicense() ? it->second->getLicense()->getType() : LicenseType::Undefined;
}

Date Controller::getProgramLicenseIssueDate(const std::string & _programName) const
{
	auto it = m_apps.find(_programName);
	if (it == m_apps.end())
		throw std::logic_error(Messages::ProgramNotRegistered);

	if (!it->second->hasLicense())
		throw std::logic_error(Messages::ProgramHasNoLicense);
	return it->second->getLicense()->getBirthDate();
}

bool Controller::canUse(std::string const & _programName, Date _date) const
{
	auto it = m_apps.find(_programName);
	if (it == m_apps.end())
		throw std::logic_error(Messages::ProgramNotRegistered);

	if (!it->second->hasLicense())
		throw std::logic_error(Messages::ProgramHasNoLicense);

	return it->second->getLicense()->isAvailable(_date);
}

void Controller::trackUse(std::string const & _programName, Date _date)
{
	auto it = m_apps.find(_programName);
	if (it == m_apps.end())
		throw std::logic_error(Messages::ProgramNotRegistered);

	if (!it->second->hasLicense())
		throw std::logic_error(Messages::ProgramHasNoLicense);

	if (!it->second->getLicense()->isAvailable(_date))
		throw std::logic_error(Messages::NoValidLicense);

	it->second->use();
}

void Controller::prolongLicense(std::string const & _programName, Date _newExpires)
{
	auto it = m_apps.find(_programName);
	if (it == m_apps.end())
		throw std::logic_error(Messages::ProgramNotRegistered);

	if (!it->second->hasLicense())
		throw std::logic_error(Messages::ProgramHasNoLicense);

	if (it->second->getLicense()->getType() != LicenseType::TimeBased)
		throw std::logic_error(Messages::TimeBasedLicenseExpected);

	TimeBasedLicense * license = dynamic_cast<TimeBasedLicense *>(it->second->getLicense());
	if (license->getEndDate() > _newExpires)
		throw std::logic_error(Messages::ProlongingToEarlierDate);

	license->continuate(_newExpires);
}

Date Controller::getLicenseExpiryDate(std::string const & _programName) const
{
	auto it = m_apps.find(_programName);
	if (it == m_apps.end())
		throw std::logic_error(Messages::ProgramNotRegistered);

	if (!it->second->hasLicense())
		throw std::logic_error(Messages::ProgramHasNoLicense);

	if (it->second->getLicense()->getType() != LicenseType::TimeBased)
		throw std::logic_error(Messages::TimeBasedLicenseExpected);

	TimeBasedLicense * license = dynamic_cast<TimeBasedLicense *>(it->second->getLicense());
	return license->getEndDate();
}

int Controller::getLicenseTokensLeft(std::string const & _programName) const
{
	auto it = m_apps.find(_programName);
	if (it == m_apps.end())
		throw std::logic_error(Messages::ProgramNotRegistered);

	if (!it->second->hasLicense())
		throw std::logic_error(Messages::ProgramHasNoLicense);

	if (it->second->getLicense()->getType() != LicenseType::TokenBased)
		throw std::logic_error(Messages::TokenBasedLicenseExpected);

	TokenBasedLicense * license = dynamic_cast<TokenBasedLicense *>(it->second->getLicense());
	return license->getDays();
}

void Controller::addLicenseTokens(std::string const & _programName, int _nTokens)
{
	auto it = m_apps.find(_programName);
	if (it == m_apps.end())
		throw std::logic_error(Messages::ProgramNotRegistered);

	if (!it->second->hasLicense())
		throw std::logic_error(Messages::ProgramHasNoLicense);

	if (_nTokens < 1)
		throw std::logic_error(Messages::NonPositiveTokens);

	if (it->second->getLicense()->getType() != LicenseType::TokenBased)
		throw std::logic_error(Messages::TokenBasedLicenseExpected);

	TokenBasedLicense * license = dynamic_cast<TokenBasedLicense *>(it->second->getLicense());
	license->updateDays(_nTokens);
}