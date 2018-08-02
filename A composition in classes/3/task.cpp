// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "task.hpp"
#include "messages.hpp"
#include "employee.hpp"
#include <iostream>

/*****************************************************************************/

Task::Task(std::string const & _tastName)
	: m_name(_tastName)
{}

/*****************************************************************************/

Task::~Task() = default;

/*****************************************************************************/

void Task::addTaskData(Employee & _e, int _h)
{
	m_employers.insert(std::make_pair(_e.getName(), std::make_pair(_h, &_e)));
}

/*****************************************************************************/

std::string const & 
Task::getTaskName() const
{
	return m_name;
}

/*****************************************************************************/

bool Task::hasEmployee(std::string const & _eName) const
{
	return m_employers.find(_eName) != m_employers.end();
}

/*****************************************************************************/

void Task::removeEmployer(std::string const & _e)
{
	m_employers.erase(_e);
}

/*****************************************************************************/

void Task::updateEmployerTime(std::string const & _e, int _newTime)
{
	auto it = m_employers.find(_e);
	it->second.first = _newTime;
}

/*****************************************************************************/

void Task::forEachEmployee(std::function<void(Employee const & _e)> _f)
{
	for (auto const & e : m_employers)
		_f(*e.second.second);
}

/*****************************************************************************/

int Task::getEmployeeHours(std::string const & _e) const
{
	return hasEmployee(_e) ? m_employers.find(_e)->second.first : 0;
}

/*****************************************************************************/