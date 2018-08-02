// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _TASK_HPP_
#define _TASK_HPP_

#include <string>
#include <unordered_map>
#include <functional>

class Employee;
class Task
{
public:

	Task(std::string const & _tastName);
	
	~Task();

	std::string const & getTaskName() const;

	bool hasEmployee(std::string const & _eName) const;

	void removeEmployer(std::string const & _e);

	void updateEmployerTime(std::string const & _e, int _newTime);

	void forEachEmployee(std::function<void(Employee const & _e)> _f);

	int getEmployeeHours(std::string const & _e) const;

	void addTaskData(Employee &, int _hours);

private:

	std::string m_name;

	std::unordered_map<std::string, std::pair<int, Employee const*>> m_employers;
};

#endif //  _TASK_HPP_