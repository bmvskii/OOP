// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "regularemployee.hpp"

/*****************************************************************************/

RegularEmployee::RegularEmployee(
	std::string const & _fullName,
	double _salaryBonus,
	RegularEmployeeLevel _employeeLevel
)
	: Employee(_fullName,_salaryBonus)
	, m_employeeLevel(_employeeLevel)
{}

/*****************************************************************************/

double RegularEmployee::getSalary(double _baseSalary) const
{
	switch (m_employeeLevel)
	{
	case RegularEmployeeLevel::Junior: return _baseSalary * 0.5 + getSalaryBonus();
	case RegularEmployeeLevel::Middle: return _baseSalary + getSalaryBonus();
	case RegularEmployeeLevel::Senior: return _baseSalary * 1.2 + getSalaryBonus();
	case RegularEmployeeLevel::Lead: return _baseSalary * 1.5 + getSalaryBonus();
	default:
		break;
	}
}

/*****************************************************************************/

void RegularEmployee::increaseEmployeeLevel()
{
	switch (m_employeeLevel)
	{
	case RegularEmployeeLevel::Junior:
		m_employeeLevel = RegularEmployeeLevel::Middle;
		break;
	case RegularEmployeeLevel::Middle:
		m_employeeLevel = RegularEmployeeLevel::Senior;
		break;
	case RegularEmployeeLevel::Senior:
		m_employeeLevel = RegularEmployeeLevel::Lead;
		break;
	case RegularEmployeeLevel::Lead:
		break;
	default:
		break;
	}
}

/*****************************************************************************/