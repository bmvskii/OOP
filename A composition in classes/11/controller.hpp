// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _CONTROLLER_HPP_
#define _CONTROLLER_HPP_

/*****************************************************************************/

#include "programcategory.hpp"
#include "useraccount.hpp"
#include "program.hpp"

#include <vector>
#include <string>
#include <set>
#include <map>
#include <unordered_map>
#include <memory>

/*****************************************************************************/

class Controller
{

	/*-----------------------------------------------------------------*/

public:

	Controller::Controller() = default;

	Controller::~Controller() = default;

	/*-----------------------------------------------------------------*/

	Controller(const Controller &) = delete;

	Controller & operator = (const Controller &) = delete;

	/*-----------------------------------------------------------------*/

	struct hasher
	{
		size_t operator()(std::pair<std::string, std::string> const & _p) const
		{
			std::hash<std::string> m_hasher;
			return m_hasher(_p.first) + m_hasher(_p.second);
		}
	};

	void createProgram(
		std::string const & _name
		, std::string const & _manufacturer
		, std::string const & _version
		, int _releaseYear
		, ProgramCategory _category
	);

	std::string const & getProgramManufacturer(std::string const & _name, std::string const & _version) const;

	int getProgramReleaseYear(std::string const & _name, std::string const & _version) const;

	ProgramCategory getProgramCategory(std::string const & _name, std::string const & _version) const;

	/*-----------------------------------------------------------------*/

	void createAccount(std::string const & _login, std::string const & _fullName);

	std::string const & getAccountFullName(std::string const & _login) const;

	std::string getAccountPreferredBrowserName(std::string const & _login) const;

	std::string getAccountPreferredOfficeToolName(std::string const & _login) const;

	/*-----------------------------------------------------------------*/

	void setAccountPreferredBrowser(
		std::string const & _login
		, std::string const & _programName
		, std::string const & _programVersion
	);

	void setAccountPreferredOfficeTool(
		std::string const & _login
		, std::string const & _programName
		, std::string const & _programVersion
	);

	/*-----------------------------------------------------------------*/

	std::vector< std::string > getUsersPreferringBrowser(std::string const & _browserName) const;

	int getUsersCountWithBrowsersAndOffice(
		std::string const & _browserName
		, std::string const & _officeToolName
	) const;

	std::vector< std::string > getUsersPreferringOlderOfficeVersion() const;

	std::vector< std::pair< std::string, std::string > > getProgramsWithoutPreferences() const;

	/*-----------------------------------------------------------------*/

private:

	/*-----------------------------------------------------------------*/

	std::unordered_map<std::pair<std::string, std::string> ,std::unique_ptr<Program>, hasher> m_apps;

	std::map<std::string, std::unique_ptr<UserAccount> > m_accounts;

	/*-----------------------------------------------------------------*/

};


/*****************************************************************************/

#endif //  _CONTROLLER_HPP_