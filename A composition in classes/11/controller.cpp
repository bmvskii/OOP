// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "controller.hpp"
#include "messages.hpp"
#include <algorithm>
#include <iostream>

/*****************************************************************************/

void Controller::createProgram(
	std::string const & _name,
	std::string const & _manufacturer,
	std::string const & _version,
	int _releaseYear, ProgramCategory _category)
{
	if (_name.empty())
		throw std::logic_error(Messages::EmptyProgramName);

	if (_version.empty())
		throw std::logic_error(Messages::EmptyVersion);

	if (_manufacturer.empty())
		throw std::logic_error(Messages::EmptyManufacturer);

	auto it = m_apps.find(std::make_pair(_name,_version));
	if (it != m_apps.end())
			throw std::logic_error(Messages::VersionDuplication);

	auto program = std::make_unique<Program>(_name, _manufacturer, _version, _releaseYear, _category);
	m_apps.insert(std::make_pair(std::make_pair(_name,_version),std::move(program)));
}

/*****************************************************************************/

std::string const & Controller::getProgramManufacturer(
	std::string const & _name,
	std::string const & _version
) const
{
	auto it = m_apps.find(std::make_pair(_name, _version));
	if (it == m_apps.end())
		throw std::logic_error(Messages::ProgramNotFound);

	return it->second->getCreater();
}

/*****************************************************************************/

int Controller::getProgramReleaseYear(std::string const & _name,std::string const & _version) const
{
	auto it = m_apps.find(std::make_pair(_name, _version));
	if (it == m_apps.end())
		throw std::logic_error(Messages::ProgramNotFound);

	return it->second->getYear();
}

/*****************************************************************************/

ProgramCategory Controller::getProgramCategory(std::string const & _name,std::string const & _version) const
{
	auto it = m_apps.find(std::make_pair(_name, _version));
	if (it == m_apps.end())
		throw std::logic_error(Messages::ProgramNotFound);
	return it->second->getCategory();
}

/*****************************************************************************/

void Controller::createAccount(std::string const & _login,std::string const & _fullName)
{
	if (_login.empty())
		throw std::logic_error(Messages::EmptyLogin);

	if (_fullName.empty())
		throw std::logic_error(Messages::EmptyFullName);

	auto it = m_accounts.find(_login);
	if (it != m_accounts.end())
		throw std::logic_error(Messages::LoginShouldBeUnique);

	m_accounts.insert(std::make_pair(_login, std::make_unique<UserAccount>(_login, _fullName)));
}

/*****************************************************************************/

std::string const & Controller::getAccountFullName(std::string const & _login) const
{
	auto it = m_accounts.find(_login);
	if (it == m_accounts.end())
		throw std::logic_error(Messages::AccountNotFound);

	return it->second->getName();
}

/*****************************************************************************/

std::string Controller::getAccountPreferredBrowserName(std::string const & _login) const
{
	auto it = m_accounts.find(_login);
	if (it == m_accounts.end())
		throw std::logic_error(Messages::AccountNotFound);

	return it->second->hasBrowser() ? it->second->getBrowserName() : ""; 
}

/*****************************************************************************/

std::string Controller::getAccountPreferredOfficeToolName(std::string const & _login) const
{
	auto it = m_accounts.find(_login);
	if (it == m_accounts.end())
		throw std::logic_error(Messages::AccountNotFound);

	return it->second->hasOfficeProgram() ? it->second->getOfficeProgramName() : "";
}

/*****************************************************************************/

void Controller::setAccountPreferredBrowser(std::string const & _login,	std::string const & _programName,std::string const & _programVersion)
{
	auto it1 = m_accounts.find(_login);
	if (it1 == m_accounts.end())
		throw std::logic_error(Messages::AccountNotFound);

	auto it2 = m_apps.find(std::make_pair(_programName, _programVersion));
	if (it2 == m_apps.end())
		throw std::logic_error(Messages::ProgramNotFound);

	if (it2->second->getCategory() != ProgramCategory::Browser)
		throw std::logic_error(Messages::ProgramCategoryMismatch);

	it1->second->addBrowser(*it2->second);
}

/*****************************************************************************/

void Controller::setAccountPreferredOfficeTool(
	std::string const & _login,
	std::string const & _programName,
	std::string const & _programVersion
)
{
	auto it1 = m_accounts.find(_login);
	if (it1 == m_accounts.end())
		throw std::logic_error(Messages::AccountNotFound);

	auto it2 = m_apps.find(std::make_pair(_programName,_programVersion));
	if (it2 == m_apps.end())
		throw std::logic_error(Messages::ProgramNotFound);
	if (it2->second->getCategory() != ProgramCategory::Office)

		throw std::logic_error(Messages::ProgramCategoryMismatch);
	it1->second->addOfficeProgram(*it2->second);
}

/*****************************************************************************/

std::vector<std::string> 
Controller::getUsersPreferringBrowser(std::string const & _browserName) const
{
	std::vector<std::string> result;
	for (auto it = m_accounts.begin(); it != m_accounts.end(); ++it)
		if (it->second->getBrowserName() == _browserName)
			result.push_back(it->second->getLogin());

	std::sort(result.begin(),result.end());
	return result;
}

/*****************************************************************************/

int Controller::getUsersCountWithBrowsersAndOffice(
	std::string const & _browserName,
	std::string const & _officeToolName
) const
{
	int users = 0;
	for (auto it = m_accounts.begin(); it != m_accounts.end(); ++it)
		if (it->second->getBrowserName() == _browserName && it->second->getOfficeProgramName() == _officeToolName)
			users++;

	return users;
}

/*****************************************************************************/

std::vector<std::string> Controller::getUsersPreferringOlderOfficeVersion() const
{
	std::vector<std::string> result;
	for (auto it1 = m_apps.begin(); it1 != m_apps.end(); ++it1)
	{
		for (auto it2 = m_accounts.begin(); it2 != m_accounts.end(); ++it2)
		{
			auto it = m_apps.find(std::make_pair(it2->second->getOfficeProgramName(), it2->second->getOfficeProgramVersion()));
			if (it->first.first == it1->first.first && it->first.second < it1->first.second)
				result.push_back(it2->second->getLogin());
		}
	}

	std::sort(result.begin(), result.end());
	return result;
}

/*****************************************************************************/

std::vector<std::pair<std::string, std::string>> Controller::getProgramsWithoutPreferences() const
{
	std::vector<std::pair<std::string, std::string> > result;
	bool isUsed;
	for (auto it1 = m_apps.begin(); it1 != m_apps.end(); ++it1)
	{
		isUsed = false;
		for (auto it2 = m_accounts.begin(); it2 != m_accounts.end(); ++it2)
		{
			if (it1->first.first == it2->second->getBrowserName() &&
				it1->first.second == it2->second->getBrowserVersion() ||
				it1->first.first == it2->second->getOfficeProgramName()
				&& it1->first.second == it2->second->getOfficeProgramVersion())
			{
				isUsed = true;
			}

		}
		if (isUsed == false)
			result.push_back(std::make_pair(it1->first.first, it1->first.second));
	}
	std::sort(
		result.begin(),
		result.end(),
		[](std::pair<std::string, std::string> const & _left,
		   std::pair<std::string, std::string> const & _right)
	{
		if (_left.first < _right.first)
			return true;
		else if (_left.first == _right.first && _left.second < _right.second)
			return true;
		else
			return false;
	}
	);
	return result;
}

/*****************************************************************************/