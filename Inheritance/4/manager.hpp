// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _MANAGER_HPP_
#define _MANAGER_HPP_

/*****************************************************************************/

#include "employee.hpp"
#include <functional>

/*****************************************************************************/

#include <unordered_map>

class Manager
	: public Employee
{
public:
	
	Manager(
		std::string const & _fullName,
		double _salaryBonus
	);

	~Manager() = default;

	double getSalary(double _baseSalary) const override;

	void addEmployee(Employee & _employee);

	void forEachEmployers(std::function<void(Employee & _e)> _f) const;

	bool hasEmployers() const;

	bool hasEmployer(std::string const & _e) const;

	void showEmployers() const;

	void removeEmployee(std::string const & _e);

private:

	Manager * m_manager;
	std::unordered_map<std::string,Employee *> m_employers;
};

/*****************************************************************************/

inline
bool Manager::hasEmployers() const
{
	return !m_employers.empty();
}

/*****************************************************************************/

inline
bool Manager::hasEmployer(std::string const & _e) const
{
	return m_employers.find(_e) != m_employers.end();
}

/*****************************************************************************/

#endif // _MANAGER_HPP_