// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _EMPLOYEE_HPP_
#define _EMPLOYEE_HPP_

/*****************************************************************************/

#include <string>
#include <unordered_map>
#include <functional>

/*****************************************************************************/

class Task;
class Employee
{
public:

	Employee(
		std::string const & _fullName,
		int _qualificationLevel
	);
	
	~Employee();
	
	std::string const & getName() const;
	
	int getQualificationLevel() const;
	
	void updateQualificationLevel(int _l);
	
	void removeTask(std::string const & _t);
	
	void forEachTask(std::function<void(Task const & _t)> _f);

	void addTask(Task & _t);

private:

	std::string m_name;
	
	int m_level;

	std::unordered_map<std::string, Task const *> m_tasks;
};

/*****************************************************************************/

#endif //  _EMPLOYEE_HPP_