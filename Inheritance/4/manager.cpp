// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "manager.hpp"
#include "messages.hpp"
#include <algorithm>
#include <iostream>

/*****************************************************************************/

Manager::Manager(
	std::string const & _fullName,
	double _salaryBonus
)
	: Employee(_fullName,_salaryBonus)
{}

/*****************************************************************************/

double Manager::getSalary(double _baseSalary) const
{
	double totalSalary = 0.0;
	
	for (auto it = m_employers.begin(); it != m_employers.end(); ++it)
		totalSalary += it->second->getSalary(_baseSalary) - it->second->getSalaryBonus();

	return hasEmployers() ? (2*totalSalary) / m_employers.size() + getSalaryBonus() : 0.0;
}

/*****************************************************************************/

void Manager::addEmployee(Employee & _employee)
{
	m_employers.insert(std::make_pair(_employee.getName(), &_employee));
}

/*****************************************************************************/

void Manager::forEachEmployers(std::function<void(Employee & _e)> _f) const
{
	for (auto const & p : m_employers)
		_f(*p.second);
}

/*****************************************************************************/

void Manager::showEmployers() const
{
	std::cout << "MANAGER : " << getName() << std::endl;
	for (auto const & _e : m_employers)
		std::cout << _e.second->getName() << std::endl;
	std::cout << "-----------" << std::endl;
}

/*****************************************************************************/

void Manager::removeEmployee(std::string const & _e)
{
	auto it = m_employers.find(_e);
	m_employers.erase(it);
}

/*****************************************************************************/