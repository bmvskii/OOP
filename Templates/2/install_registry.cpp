// (C) 2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "install_registry.hpp"
#include "messages.hpp"

/*****************************************************************************/

InstallRegistry::InstallRegistry(std::string const & _name)
	: m_name(_name)
{
	if (_name.empty())
		throw std::logic_error(Messages::MachineNameEmpty);
}

/*****************************************************************************/

std::set<std::string> InstallRegistry::fetchAllInstalledProgramNames() const
{
	std::set<std::string> result;

	for (auto const & p : m_programs)
		result.insert(p.first);

	return result;
}

/*****************************************************************************/

bool InstallRegistry::hasIdenticalPrograms(InstallRegistry const & _ir) const
{
	if (m_programs.size() != _ir.m_programs.size())
		return false;

	for (auto const & p : m_programs)
		if (_ir.m_programs.find(p.first) == _ir.m_programs.end())
			return false;

	return true;
}

/*****************************************************************************/

std::set<std::string> InstallRegistry::getUniqueProgramsComparedTo(InstallRegistry const & _ir) const
{
	std::set<std::string> result;

	for (auto const & p : m_programs)
		if (_ir.m_programs.find(p.first) == _ir.m_programs.end())
			result.insert(p.first);

	return result;
}

/*****************************************************************************/

void InstallRegistry::installProgram(std::string const & _programName, Date _registryDate)
{
	if (_programName.empty())
		throw std::logic_error(Messages::ProgramNameEmpty);

	if (m_programs.find(_programName) != m_programs.end())
		throw std::logic_error(Messages::ProgramAlreadyInstalled);

	if (_registryDate > Date())
		throw std::logic_error(Messages::InstallationDateInFuture);

	m_programs.insert(std::make_pair(_programName,_registryDate));
}

/*****************************************************************************/

void InstallRegistry::updateProgram(std::string const & _programName, Date _newRegistryDate)
{

	if (_programName.empty())
		throw std::logic_error(Messages::ProgramNameEmpty);

	if (m_programs.find(_programName) == m_programs.end())
		throw std::logic_error(Messages::ProgramNotInstalled);

	if (_newRegistryDate > Date())
		throw std::logic_error(Messages::UpdateDateInFuture);

	if (_newRegistryDate < m_programs.find(_programName)->second)
		throw std::logic_error(Messages::UpdateDateEarlierThanPreviousVersion);

	m_programs.find(_programName)->second = _newRegistryDate;
}

/*****************************************************************************/