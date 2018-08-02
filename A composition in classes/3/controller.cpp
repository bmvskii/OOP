// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "controller.hpp"
#include "messages.hpp"
#include "employee.hpp"
#include "task.hpp"

#include <algorithm>

/*****************************************************************************/

Controller::Controller() = default;

/*****************************************************************************/

Controller::~Controller() = default;

/*****************************************************************************/

void Controller::createEmployee(std::string const & _fullName,int _level)
{
	if (_fullName.empty())
		throw std::logic_error(Messages::EmptyEmployeeName);

	if (m_employers.find(_fullName) != m_employers.end())
		throw std::logic_error(Messages::EmployeeAlreadyExists);

	if (_level < 1 || _level > 5)
		throw std::logic_error(Messages::LevelOutOfRange);

	m_employers.insert(std::make_pair(_fullName, std::make_unique<Employee>(_fullName, _level)));
}

/*****************************************************************************/

void Controller::updateEmployeeLevel(std::string const & _fullName,int _newLevel)
{
	if (m_employers.find(_fullName) == m_employers.end()) 
		throw std::logic_error(Messages::EmployeeNotFound);

	if (_newLevel < 1 || _newLevel > 5)
		throw std::logic_error(Messages::LevelOutOfRange);
	
	m_employers.find(_fullName)->second->updateQualificationLevel(_newLevel);
}

/*****************************************************************************/

int Controller::getEmployeeLevel(std::string const & _fullName) const
{
	if (m_employers.find(_fullName) == m_employers.end())
		throw std::logic_error(Messages::EmployeeNotFound);

	return m_employers.find(_fullName)->second->getQualificationLevel();
}

/*****************************************************************************/

void Controller::createTask(std::string const & _taskTitle)
{
	if (_taskTitle.empty())
		throw std::logic_error(Messages::EmptyTaskTitle);

	if (m_tasks.find(_taskTitle) != m_tasks.end())
		throw std::logic_error(Messages::TaskAlreadyExists);

	m_tasks.insert(std::make_pair(_taskTitle, std::make_unique<Task>(_taskTitle)));
}

/*****************************************************************************/

void Controller::assignEmployeeToTask(std::string const & _taskTitle,std::string const & _employeeName,int _hours)
{
	if (m_tasks.find(_taskTitle) == m_tasks.end())
		throw std::logic_error(Messages::TaskNotFound);
	
	if (m_employers.find(_employeeName) == m_employers.end()) 
		throw std::logic_error(Messages::EmployeeNotFound);

	if (_hours < 1) 
		throw std::logic_error(Messages::NonPositiveHours);

	if (m_tasks.find(_taskTitle)->second->hasEmployee(_employeeName)) 
		throw std::logic_error(Messages::EmployeeAlreadyAllocated);

	m_employers.find(_employeeName)->second->addTask(*m_tasks.find(_taskTitle)->second);
	m_tasks.find(_taskTitle)->second->addTaskData(*m_employers.find(_employeeName)->second, _hours);
}

/*****************************************************************************/

void Controller::updateEmployeeTaskLoad(std::string const & _taskTitle,std::string const & _employeeName,int _hours)
{
	if (m_tasks.find(_taskTitle) == m_tasks.end()) 
		throw std::logic_error(Messages::TaskNotFound);

	if (m_employers.find(_employeeName) == m_employers.end()) 
		throw std::logic_error(Messages::EmployeeNotFound);

	if (_hours < 1)
		throw std::logic_error(Messages::NonPositiveHours);

	if (!m_tasks.find(_taskTitle)->second->hasEmployee(_employeeName)) 
		throw std::logic_error(Messages::EmployeeNotAllocated);
	
	m_tasks.find(_taskTitle)->second->updateEmployerTime(_employeeName, _hours);
}

/*****************************************************************************/

void Controller::unassignEmployeeFromTask(std::string const & _taskTitle,std::string const & _employeeName)
{
	if (m_tasks.find(_taskTitle) == m_tasks.end()) 
		throw std::logic_error(Messages::TaskNotFound);

	if (m_employers.find(_employeeName) == m_employers.end())
		throw std::logic_error(Messages::EmployeeNotFound);

	if (!m_tasks.find(_taskTitle)->second->hasEmployee(_employeeName)) 
		throw std::logic_error(Messages::EmployeeNotAllocated);

	m_tasks.find(_taskTitle)->second->removeEmployer(_employeeName);
	m_employers.find(_employeeName)->second->removeTask(_taskTitle);
}

/*****************************************************************************/

std::vector<std::string> Controller::getTaskEmployees(std::string const & _taskTitle) const
{
	if (m_tasks.find(_taskTitle) == m_tasks.end())
		throw std::logic_error(Messages::TaskNotFound);

	std::vector<std::string> result;
	m_tasks.find(_taskTitle)->second->forEachEmployee(
		[&](Employee const & _e)
	{
		result.push_back(_e.getName());
	}
	);
	std::sort(result.begin(), result.end());

	return result;
}

/*****************************************************************************/

std::vector<std::string> Controller::getEmployeeTasks(std::string const & _employeeName) const
{
	if (m_employers.find(_employeeName) == m_employers.end()) 
		throw std::logic_error(Messages::EmployeeNotFound);

	std::vector<std::string> result;
	m_employers.find(_employeeName)->second->forEachTask(
		[&](Task const & _task)
	{
		result.push_back(_task.getTaskName());
	}
	);
	std::sort(result.begin(), result.end());

	return result;
}

/*****************************************************************************/

int Controller::getEmployeeAllocationInTask(std::string const & _taskTitle,std::string const & _employeeName) const
{
	if (m_employers.find(_employeeName) == m_employers.end()) 
		throw std::logic_error(Messages::EmployeeNotFound);

	if (m_tasks.find(_taskTitle) == m_tasks.end()) 
		throw std::logic_error(Messages::TaskNotFound);

	return m_tasks.find(_taskTitle)->second->getEmployeeHours(_employeeName);
}

/*****************************************************************************/

int Controller::getTaskTotalHours(std::string const & _taskTitle) const
{
	if (m_tasks.find(_taskTitle) == m_tasks.end()) 
		throw std::logic_error(Messages::TaskNotFound);

	int total = 0;
	m_tasks.find(_taskTitle)->second->forEachEmployee(
		[&](Employee const & _e)
	{
		total += m_tasks.find(_taskTitle)->second->getEmployeeHours(_e.getName());
	});

	return total;
}

/*****************************************************************************/

std::vector<std::string> Controller::getEmployeesWithLoadOver(int _hours) const
{
	std::vector<std::string> result;
	
	int time;
	for (auto const & pEmployee : m_employers)
	{
		time = 0;
		pEmployee.second->forEachTask(
			[&](Task const & _task)
		{
			time += _task.getEmployeeHours(pEmployee.first);
		}
		);

		if (time > _hours)
		{
			result.push_back(pEmployee.first);
		}
	}
	std::sort(result.begin(), result.end());

	return result;
}

/*****************************************************************************/

double Controller::calculateTaskCost(std::string const & _taskTitle,double _baseHourCost) const
{
	if (m_tasks.find(_taskTitle) == m_tasks.end())
		throw std::logic_error(Messages::TaskNotFound);

	if (_baseHourCost < 0) 
		throw std::logic_error(Messages::NegativeHourCost);

	double result = 0.0;
	m_tasks.find(_taskTitle)->second->forEachEmployee(
		[&](Employee const & _e)
	{
		result += _e.getQualificationLevel() * m_tasks.find(_taskTitle)->second->getEmployeeHours(_e.getName()) * _baseHourCost;
	}
	);

	return result;
}

/*****************************************************************************/

double Controller::predictEmployeePayment(std::string const & _employeeName,double _baseHourCost) const
{
	if (m_employers.find(_employeeName) == m_employers.end())
		throw std::logic_error(Messages::EmployeeNotFound);

	if (_baseHourCost < 0) 
		throw std::logic_error(Messages::NegativeHourCost);

	double result = 0.0;
	m_employers.find(_employeeName)->second->forEachTask(
		[&](Task const & _task)
	{
		result += _task.getEmployeeHours(_employeeName) * m_employers.find(_employeeName)->second->getQualificationLevel() * _baseHourCost;
	}
	);
	return result;
}

/*****************************************************************************/
