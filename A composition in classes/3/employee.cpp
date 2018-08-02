// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "employee.hpp"
#include "messages.hpp"
#include "task.hpp"

/*****************************************************************************/

Employee::Employee(std::string const & _fullName,int _qualificationLevel)
	: m_name(_fullName), m_level(_qualificationLevel)
{}

/*****************************************************************************/

Employee::~Employee() = default;

/*****************************************************************************/

void Employee::addTask(Task & _t)
{
	m_tasks.insert(std::make_pair(_t.getTaskName(), &_t));
}

/*****************************************************************************/

std::string const & 
Employee::getName() const
{
	return m_name;
}

/*****************************************************************************/

int Employee::getQualificationLevel() const
{
	return m_level;
}

/*****************************************************************************/

void Employee::updateQualificationLevel(int _l)
{
	m_level = _l;
}

/*****************************************************************************/

void Employee::removeTask(std::string const & _t)
{
	m_tasks.erase(_t);
}

/*****************************************************************************/

void Employee::forEachTask(std::function<void(Task const & _t)> _f)
{
	for (auto const & t : m_tasks)
		_f(*t.second);
}

/*****************************************************************************/