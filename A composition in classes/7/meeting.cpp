// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "meeting.hpp"
#include "messages.hpp"
#include "participant.hpp"

/*****************************************************************************/

void Meeting::forEachMember(std::function<void(Participant const & _p)> _f)
{
	for (auto m : m_members)
		_f(*m.second);
}

/*****************************************************************************/

void Meeting::forEachIssue(std::function<void(std::string const&_i)> _f)
{
	for (auto i : m_issues)
		_f(i);
}

/*****************************************************************************/

std::string const & Meeting::getModeratorName() const
{
	return m_moderator->getName();
}

/*****************************************************************************/

Meeting::Meeting(
	int _ID,
	std::string const & _name,
	DateTime const & _startTime
)
	: m_ID(_ID)
	, m_name(_name)
	, m_startTime(_startTime)
	, m_moderator(nullptr)
{}

/*****************************************************************************/

void Meeting::addMember(Participant const & _mem)
{
	m_members.insert(std::make_pair(_mem.getName(), &_mem));
}

/*****************************************************************************/

void Meeting::addModerator(Participant const & _mod)
{
	m_moderator = &_mod;
}

/*****************************************************************************/
