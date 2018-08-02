// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "controller.hpp"
#include "messages.hpp"
#include "employee.hpp"
#include "regularemployee.hpp"
#include "manager.hpp"

#include <algorithm>
#include <iostream>
/*****************************************************************************/

Controller::Controller() = default;

/*****************************************************************************/

Controller::~Controller() = default;

/*****************************************************************************/

void Controller::createManager(std::string const & _fullName)
{
	auto it = m_employers.find(_fullName);

	if (it != m_employers.end())
		throw std::logic_error(Messages::EmployeeFullNameNonUnique);

	if (_fullName.empty())
		throw std::logic_error(Messages::EmployeeFullNameEmpty);

	m_employers.insert(std::make_pair(_fullName, std::make_unique<Manager>(_fullName, 0.0)));
}

/*****************************************************************************/

void Controller::createRegular(
	std::string const & _fullName,
	RegularEmployeeLevel _startingLevel
)
{
	auto it = m_employers.find(_fullName);

	if (it != m_employers.end())
		throw std::logic_error(Messages::EmployeeFullNameNonUnique);

	if (_fullName.empty())
		throw std::logic_error(Messages::EmployeeFullNameEmpty);

	m_employers.insert(std::make_pair(_fullName, 
		std::make_unique<RegularEmployee>(
			_fullName,
			0.0,
			_startingLevel
		)
	));
}

/*****************************************************************************/

bool Controller::isKnownEmployee(std::string const & _fullName) const
{
	return m_employers.find(_fullName) != m_employers.end();
}

/*****************************************************************************/

RegularEmployeeLevel 
Controller::getRegularEmployeeLevel(std::string const & _fullName) const
{
	auto it = m_employers.find(_fullName);

	if (it == m_employers.end())
		throw std::logic_error(Messages::UnregisteredEmployeeName);

	auto pRE = dynamic_cast<RegularEmployee *>(it->second.get());

	if (pRE == nullptr)
		throw std::logic_error(Messages::NotARegular);

	return pRE->getEmployeeLevel();
}

/*****************************************************************************/

double Controller::getEmployeeSalary(
	std::string const & _fullName,
	double _baseSalary
)
{
	auto it = m_employers.find(_fullName);

	if (it == m_employers.end())
		throw std::logic_error(Messages::UnregisteredEmployeeName);

	if (_baseSalary < 0)
		throw std::logic_error(Messages::NegativeBaseSalary);
	
	return it->second->getSalary(_baseSalary);
}

/*****************************************************************************/

double Controller::getTotalSalary(double _baseSalary) const
{
	if (_baseSalary < 0)
		throw std::logic_error(Messages::NegativeBaseSalary);

	double totalSalary = 0.0;

	for (auto it = m_employers.begin(); it != m_employers.end(); ++it)
		totalSalary += it->second->getSalary(_baseSalary);
	
	return totalSalary;
}

/*****************************************************************************/

void Controller::changeBonus(
	std::string const & _fullName,
	double _newBonus
)
{
	auto it = m_employers.find(_fullName);

	if (it == m_employers.end())
		throw std::logic_error(Messages::UnregisteredEmployeeName);

	if (_newBonus < 0)
		throw std::logic_error(Messages::NegativeBonusAmount);

	it->second->setSalaryBonus(_newBonus);
}

/*****************************************************************************/

double Controller::getEmployeeBonus(std::string const & _fullName) const
{
	auto it = m_employers.find(_fullName);

	if (it == m_employers.end())
		throw std::logic_error(Messages::UnregisteredEmployeeName);

	return it->second->getSalaryBonus();
}

/*****************************************************************************/

std::string Controller::getEmployeeManager(std::string const & _fullName) const
{
	auto it = m_employers.find(_fullName);
	if (it == m_employers.end())
		throw std::logic_error(Messages::UnregisteredEmployeeName);

	for (auto & pEmployee : m_employers)
	{
		auto pM = dynamic_cast<Manager *>(pEmployee.second.get());
		if (pM)
			if (pM->hasEmployer(_fullName))
				return pM->getName();
	}

	return "";
}

/*****************************************************************************/

std::unordered_set<std::string>
Controller::getManagerSubordinates(std::string const & _fullName) const
{
	auto it = m_employers.find(_fullName);

	if (it == m_employers.end())
		throw std::logic_error(Messages::UnregisteredEmployeeName);

	auto pM = dynamic_cast<Manager *>(it->second.get());

	if (pM == nullptr)
		throw std::logic_error(Messages::NotAManager);
	
	std::unordered_set<std::string> result;

	pM->forEachEmployers(
		[&](Employee const & _e)
	{
		result.insert(_e.getName());
	}
	);

	return result;
}

/*****************************************************************************/

void Controller::assignManager(
	std::string const & _employeeFullName,
	std::string const & _managerFullName
)
{

	//---------------------------------------------------------------
	auto it1 = m_employers.find(_employeeFullName);
	if (it1 == m_employers.end())
		throw std::logic_error(Messages::UnregisteredEmployeeName);

	//---------------------------------------------------------------

	auto it2 = m_employers.find(_managerFullName);
	if (it2 == m_employers.end())
		throw std::logic_error(Messages::UnregisteredEmployeeName);

	auto pM = dynamic_cast<Manager *>(it2->second.get());
	if (pM == nullptr)
		throw std::logic_error(Messages::NotAManager);

	//---------------------------------------------------------------
	if (pM->hasEmployer(_employeeFullName))
		throw std::logic_error(Messages::SubordinateAlreadyAdded);

	if (it1->second->getManager())
	{
			auto it = m_employers.find(it1->second->getManager()->getName());
			auto temp = dynamic_cast<Manager *>(it->second.get());
			temp->removeEmployee(it1->second->getName());
	}

	pM->addEmployee(*it1->second);
	it1->second->setManager(*pM);

	//---------------------------------------------------------------
}

/*****************************************************************************/

void Controller::deassignManager(std::string const & _employeeFullName)
{
	auto it = m_employers.find(_employeeFullName);
	if (it == m_employers.end())
		throw std::logic_error(Messages::UnregisteredEmployeeName);

	if (it->second->getManager() == nullptr)
		throw std::logic_error(Messages::EmployeeHasNoManager);

	auto tempIt = m_employers.find(it->second->getManager()->getName());
	auto temp = dynamic_cast<Manager *>(tempIt->second.get());

	temp->removeEmployee(it->second->getName());
	it->second->unsetManager();
}

/*****************************************************************************/

void Controller::promote(std::string const & _employeeFullName)
{
	auto it = m_employers.find(_employeeFullName);
	if (it == m_employers.end())
		throw std::logic_error(Messages::UnregisteredEmployeeName);

	auto pRE = dynamic_cast<RegularEmployee *>(it->second.get());
	if (pRE == nullptr)
		throw std::logic_error(Messages::CannotPromoteManagers);

	pRE->increaseEmployeeLevel();
}

/*****************************************************************************/

void Controller::fire(std::string const & _employeeFullName)
{
	auto it = m_employers.find(_employeeFullName);
	if (it == m_employers.end())
		throw std::logic_error(Messages::UnregisteredEmployeeName);
	
	auto pE = dynamic_cast<Manager *>(it->second.get());
	if (pE && pE->hasEmployers())
		throw std::logic_error(Messages::CannotFireAssignedManager);

	if (it->second->getManager())
	{
		auto tempIt = m_employers.find(it->second->getManager()->getName());
		auto temp = dynamic_cast<Manager *>(tempIt->second.get());

		temp->removeEmployee(it->second->getName());
		it->second->unsetManager();
	}

	m_employers.erase(it);
}

/*****************************************************************************/