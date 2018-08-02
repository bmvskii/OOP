// (C) 2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _INSTALL_REGISTRY_HPP_
#define _INSTALL_REGISTRY_HPP_

/*****************************************************************************/

#include "date.hpp"
#include "messages.hpp"

#include <string>
#include <unordered_map>
#include <set>

/*****************************************************************************/

class InstallRegistry
{

/*-----------------------------------------------------------------*/

public:

/*-----------------------------------------------------------------*/

	InstallRegistry(std::string const & _name);

	~InstallRegistry() = default;

	InstallRegistry(InstallRegistry const &) = delete;

	InstallRegistry(InstallRegistry const &&) = delete;

	InstallRegistry & operator =(InstallRegistry const &) = delete;

	InstallRegistry & operator =(InstallRegistry const &&) = delete;

	std::string const & getMachineName() const;

	void updateMachineName(std::string const & _newName);

	int getNumInstalledPrograms() const;

	bool isClean() const;

	bool isProgramInstalled(std::string const & _programName) const;

	Date getProgramInstallationDate(std::string const & _programName) const;

	void installProgram(std::string const & _programName, Date _registryDate);

	void updateProgram(std::string const & _programName, Date _newRegistryDate);

	void uninstallProgram(std::string const & _programName);

	void uninstallAll();

	std::set<std::string> fetchAllInstalledProgramNames() const;

	bool hasIdenticalPrograms(InstallRegistry const & _ir) const;

	std::set<std::string> getUniqueProgramsComparedTo(InstallRegistry const & _ir) const;

/*-----------------------------------------------------------------*/

private:

/*-----------------------------------------------------------------*/
	
	std::string m_name;

	std::unordered_map<std::string, Date> m_programs;

/*-----------------------------------------------------------------*/

};


/*****************************************************************************/

inline
std::string const & InstallRegistry::getMachineName() const
{
	return m_name;
}

/*****************************************************************************/

inline
void InstallRegistry::updateMachineName(std::string const & _newName)
{
	if (_newName.empty())
		throw std::logic_error(Messages::MachineNameEmpty);

	m_name = _newName;
}

/*****************************************************************************/

inline
int InstallRegistry::getNumInstalledPrograms() const
{
	return m_programs.size();
}

/*****************************************************************************/

inline
bool InstallRegistry::isClean() const
{
	return m_programs.size() == 0;
}

/*****************************************************************************/

inline
bool InstallRegistry::isProgramInstalled(std::string const & _programName) const
{
	if (_programName.empty())
		throw std::logic_error(Messages::ProgramNameEmpty);

	return m_programs.find(_programName) != m_programs.end();
}

/*****************************************************************************/

inline
Date InstallRegistry::getProgramInstallationDate(std::string const & _programName) const
{
	if (_programName.empty())
		throw std::logic_error(Messages::ProgramNameEmpty);

	if (m_programs.find(_programName) == m_programs.end())
		throw std::logic_error(Messages::ProgramNotInstalled);

	return m_programs.find(_programName)->second;
}

/*****************************************************************************/

inline
void InstallRegistry::uninstallProgram(std::string const & _programName)
{
	if (_programName.empty())
		throw std::logic_error(Messages::ProgramNameEmpty);

	if (m_programs.find(_programName) == m_programs.end())
		throw std::logic_error(Messages::ProgramNotInstalled);

	m_programs.erase(_programName);
}

/*****************************************************************************/

inline
void InstallRegistry::uninstallAll()
{
	m_programs.clear();
}

/*****************************************************************************/


#endif // _INSTALL_REGISTRY_HPP_
