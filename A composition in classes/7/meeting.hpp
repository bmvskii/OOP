// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _MEETING_HPP_
#define _MEETING_HPP_

/*****************************************************************************/

#include "datetime.hpp"

#include <memory>
#include <map>
#include <vector>
#include <string>
#include <functional>

/*****************************************************************************/

class Participant;

/*****************************************************************************/


class Meeting
{

/*-----------------------------------------------------------------*/

public:

/*-----------------------------------------------------------------*/

	Meeting(
		int _ID,
		std::string const & _name,
		DateTime const & _startTime
	);

	~Meeting() = default;

	int getID() const;

	std::string const & getName() const;

	void changeName(std::string const & _newName);

	DateTime const & getStartTime() const;

	void changeStartTime(DateTime const & _newDate);

	void addMember(Participant const & _mem);

	void addModerator(Participant const & _mod);

	void addIssue(std::string const & _issue);

	bool hasMember(std::string const & _name) const;

	bool hasIssue(std::string const & _issue) const;

	void removeMember(std::string const & _name);

	bool hasModerator() const;

	void forEachMember(std::function<void(Participant const & _p)> _f);

	void forEachIssue(std::function<void(std::string const & _i)> _f);

	std::string const & getModeratorName() const;

	int getIssuesCount() const;

	int getMembersCount() const;

/*-----------------------------------------------------------------*/

private:

/*-----------------------------------------------------------------*/
	
	int m_ID;

	std::string m_name;

	DateTime m_startTime;

	std::map<std::string, Participant const *> m_members;

	Participant const * m_moderator;

	std::vector<std::string> m_issues;

/*-----------------------------------------------------------------*/ 

};

/*****************************************************************************/

inline
void Meeting::addIssue(std::string const & _issue)
{
	m_issues.push_back(_issue);
}

/*****************************************************************************/

inline
bool Meeting::hasMember(std::string const & _name) const
{
	return m_members.find(_name) != m_members.end();
}

/*****************************************************************************/

inline
bool Meeting::hasIssue(std::string const & _issue) const
{
	for (int i = 0; i < m_issues.size(); i++)
		if (m_issues[i] == _issue)
			return true;
	return false;
}

/*****************************************************************************/

inline
bool Meeting::hasModerator() const
{
	return m_moderator != nullptr;
}

/*****************************************************************************/

inline
int Meeting::getID() const
{
	return m_ID;
}

/*****************************************************************************/

inline
std::string const & Meeting::getName() const
{
	return m_name;
}

/*****************************************************************************/

inline
void Meeting::changeName(std::string const & _newName)
{
	m_name = _newName;
}

/*****************************************************************************/

inline
DateTime const & Meeting::getStartTime() const
{
	return m_startTime;
}

/*****************************************************************************/

inline
void Meeting::changeStartTime(DateTime const & _newDate)
{
	m_startTime = _newDate;
}

/*****************************************************************************/

inline
void Meeting::removeMember(std::string const & _name)
{
	m_members.erase(_name);
}

/*****************************************************************************/

inline
int Meeting::getIssuesCount() const
{
	return m_issues.size();
}

/*****************************************************************************/

inline
int Meeting::getMembersCount() const
{
	return m_members.size();
}

/*****************************************************************************/

#endif // _MEETING_HPP_
