// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "employee.hpp"

/*****************************************************************************/

Employee::Employee(
	std::string const & _fullName,
	double _salaryBonus
)
	: m_fullName(_fullName)
	, m_salaryBonus(_salaryBonus)
{}

/*****************************************************************************/

Employee::~Employee() = default;

/*****************************************************************************/

void  Employee::setSalaryBonus(double _salaryBonus)
{
	m_salaryBonus = _salaryBonus;
}

void Employee::setManager(Manager & _manager)
{
	m_manager = &_manager;
}

/*****************************************************************************/

Manager const * Employee::getManager() const
{
	return m_manager;
}

/*****************************************************************************/

void Employee::unsetManager()
{
	m_manager = nullptr;
}

/*****************************************************************************/
