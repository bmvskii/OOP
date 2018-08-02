// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _EMPLOYEE_HPP_
#define _EMPLOYEE_HPP_

/*****************************************************************************/

#include <string>

class Manager;

class Employee
{
protected:
	Employee(
		std::string const & _fullName,
		double _salaryBonus = 0
	);

public:

	virtual ~Employee();

	virtual double getSalary(double _baseSalary) const = 0;

	std::string const & getName() const;

	double getSalaryBonus() const;

	void setSalaryBonus(double _salaryBonus);

	void setManager(Manager & _manager);

	void unsetManager();

	Manager const * getManager() const;

private:

	Manager * m_manager;
	std::string m_fullName;
	double m_salaryBonus;

};

/*****************************************************************************/

inline
std::string const & Employee::getName() const
{
	return m_fullName;
}

/*****************************************************************************/

inline
double Employee::getSalaryBonus() const
{
	return m_salaryBonus;
}

/*****************************************************************************/

#endif // _EMPLOYEE_HPP_