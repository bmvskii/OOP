// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _REGULAREMPLOYEE_HPP_
#define _REGULAREMPLOYEE_HPP_

/*****************************************************************************/

#include "employee.hpp"
#include "regularemployeelevel.hpp"

/*****************************************************************************/

class Manager;

class RegularEmployee
	: public Employee
{

public:

	RegularEmployee(
		std::string const & _fullName,
		double _salaryBonus,
		RegularEmployeeLevel _employeeLevel
	);

	~RegularEmployee() = default;

	double getSalary(double _baseSalary) const override;

	RegularEmployeeLevel getEmployeeLevel() const;

	void increaseEmployeeLevel();

private:
	
	RegularEmployeeLevel m_employeeLevel;
};

/*****************************************************************************/

inline
RegularEmployeeLevel RegularEmployee::getEmployeeLevel() const
{
	return m_employeeLevel;
}

/*****************************************************************************/

#endif // _REGULAREMPLOYEE_HPP_