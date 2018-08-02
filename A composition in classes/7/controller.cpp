// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "controller.hpp"
#include "messages.hpp"

#include <algorithm>
#include <set>

/*****************************************************************************/

Controller::Controller() = default;

/*****************************************************************************/

Controller::~Controller() = default;

/*****************************************************************************/

void Controller::addParticipant(const std::string & _fullName, const std::string & _email)
{
	if (_fullName.empty())
		throw std::logic_error(Messages::EmptyParticipantName);

	if (_email.empty())
		throw std::logic_error(Messages::EmptyParticipantEmail);

	if (m_participants.find(_fullName) != m_participants.end())
		throw std::logic_error(Messages::DuplicateParticipant);

	for (auto it = m_participants.begin(); it != m_participants.end(); ++it)
		if (it->second->getEmail() == _email)
			throw std::logic_error(Messages::DuplicateEmail);

	m_participants.insert(std::make_pair(_fullName, std::make_unique<Participant>(_fullName, _email)));
}

/*****************************************************************************/

const std::string & Controller::getParticipantEmail(const std::string & _fullName) const
{
	if (m_participants.find(_fullName) == m_participants.end())
		throw std::logic_error(Messages::ParticipantCannotBeFound);

	return m_participants.find(_fullName)->second->getEmail();
}

/*****************************************************************************/

void Controller::addMeeting(int _meetingId, const std::string & _name, const DateTime & _startTime)
{
	if (_name.empty())
		throw std::logic_error(Messages::EmptyMeetingName);

	DateTime currentDate;
	if (_startTime < currentDate)
		throw std::logic_error(Messages::InvalidMeetingTime);

	if (m_meetings.find(_meetingId) != m_meetings.end())
		throw std::logic_error(Messages::DuplicateMeeting);

	m_meetings.insert(std::make_pair(_meetingId, std::make_unique<Meeting>(_meetingId, _name, _startTime)));
}

/*****************************************************************************/

const std::string & Controller::getMeetingName(int _meetingId) const
{
	if (m_meetings.find(_meetingId) == m_meetings.end())
		throw std::logic_error(Messages::MeetingCannotBeFound);

	return m_meetings.find(_meetingId)->second->getName();
}

/*****************************************************************************/

const DateTime & Controller::getMeetingStartTime(int _meetingId) const
{
	if (m_meetings.find(_meetingId) == m_meetings.end())
		throw std::logic_error(Messages::MeetingCannotBeFound);

	return m_meetings.find(_meetingId)->second->getStartTime();
}

/*****************************************************************************/

void Controller::addMeetingParticipant(int _meetingId, const std::string & _participantName)
{
	if (m_meetings.find(_meetingId) == m_meetings.end())
		throw std::logic_error(Messages::MeetingCannotBeFound);

	if (m_participants.find(_participantName) == m_participants.end())
		throw std::logic_error(Messages::ParticipantCannotBeFound);

	m_meetings.find(_meetingId)->second->addMember(*m_participants.find(_participantName)->second.get());
}

/*****************************************************************************/

void Controller::removeMeetingParticipant(int _meetingId, const std::string & _participantName)
{
	if (m_meetings.find(_meetingId) == m_meetings.end())
		throw std::logic_error(Messages::MeetingCannotBeFound);

	if (m_participants.find(_participantName) == m_participants.end())
		throw std::logic_error(Messages::ParticipantCannotBeFound);

	if (!m_meetings.find(_meetingId)->second->hasMember(_participantName))
		throw std::logic_error(Messages::ParticipantNotPartOfMeeting);

	m_meetings.find(_meetingId)->second->removeMember(_participantName);
}

/*****************************************************************************/

void Controller::setMeetingModerator(int _meetingId, const std::string & _participantName)
{
	if (m_meetings.find(_meetingId) == m_meetings.end())
		throw std::logic_error(Messages::MeetingCannotBeFound);

	if (m_participants.find(_participantName) == m_participants.end())
		throw std::logic_error(Messages::ParticipantCannotBeFound);

	if (!m_meetings.find(_meetingId)->second->hasMember(_participantName))
		throw std::logic_error(Messages::ModeratorIsNotParticipant);

	m_meetings.find(_meetingId)->second->addModerator(*m_participants.find(_participantName)->second.get());
}

/*****************************************************************************/

std::string Controller::getMeetingModeratorName(int _meetingId) const
{
	if (m_meetings.find(_meetingId) == m_meetings.end())
		throw std::logic_error(Messages::MeetingCannotBeFound);

	return  m_meetings.find(_meetingId)->second->hasModerator() 
		  ? m_meetings.find(_meetingId)->second->getModeratorName()
		  : "";
}

/*****************************************************************************/

std::vector<std::string> Controller::getMeetingParticipants(int _meetingId) const
{
	if (m_meetings.find(_meetingId) == m_meetings.end())
		throw std::logic_error(Messages::MeetingCannotBeFound);

	std::vector<std::string> members;

	m_meetings.find(_meetingId)->second->forEachMember(
		[&](Participant const & _p)
	{
		members.push_back(_p.getName());
	}
	);

	std::sort(members.begin(), members.end());

	return members;
}

/*****************************************************************************/

void Controller::validateMeceting(int _meetingId) const
{
	if (m_meetings.find(_meetingId) == m_meetings.end())
		throw std::logic_error(Messages::MeetingCannotBeFound);

	if (m_meetings.find(_meetingId)->second->getMembersCount() < 2)
		throw std::logic_error(Messages::NotEnoughParticipants);
}

/*****************************************************************************/

void Controller::addMeetingAgendaRow(int _meetingId, const std::string & _agendaRow)
{
	if (m_meetings.find(_meetingId) == m_meetings.end())
		throw std::logic_error(Messages::MeetingCannotBeFound);

	if (_agendaRow.empty())
		throw std::logic_error(Messages::EmptyMeetingAgendaRow);

	m_meetings.find(_meetingId)->second->addIssue(_agendaRow);
}

/*****************************************************************************/

std::vector<std::string> Controller::getMeetingAgenda(int _meetingId) const
{
	if (m_meetings.find(_meetingId) == m_meetings.end())
		throw std::logic_error(Messages::MeetingCannotBeFound);

	std::vector<std::string> issues;

	m_meetings.find(_meetingId)->second->forEachIssue(
		[&](std::string const & _issues)
	{
		issues.push_back(_issues);
	}
	);

	return issues;
}

/*****************************************************************************/

std::string Controller::getMostFrequentModeratorName() const
{
	std::map<std::string, int> moderators;
	std::map<int, std::string, std::greater<int>> temp;

	for (auto it = m_meetings.begin(); it != m_meetings.end(); ++it)
		if (moderators.find(getMeetingModeratorName(it->first)) != moderators.end())
			moderators.find(getMeetingModeratorName(it->first))->second++;
		else
			moderators.insert(std::make_pair((getMeetingModeratorName(it->first)), 0));

	for (auto m : moderators)
		temp.insert(std::make_pair(m.second, m.first));

	return temp.begin()->second;
}

/*****************************************************************************/

std::string Controller::getMeetingWithLongestAgenda() const
{
	std::string meetingName;
	int max = 0;
	for (auto it = m_meetings.begin(); it != m_meetings.end(); ++it)
		if (it->second->getIssuesCount() > max)
		{
			max = it->second->getIssuesCount();
			meetingName = it->second->getName();
		}

	return meetingName;
}

/*****************************************************************************/

std::map<std::string, std::vector<std::string>> Controller::getOverlaps() const
{
	std::map<std::string, std::vector<std::string>> overlaps;
	std::vector<std::pair<std::string, DateTime>> meeting;
	std::set<std::string> temp;

	for (auto it1 = m_participants.begin(); it1 != m_participants.end(); ++it1)
	{
		for (auto it2 = m_meetings.begin(); it2 != m_meetings.end(); ++it2)
			if (it2->second->hasMember(it1->first))
				meeting.push_back(std::make_pair(it2->second->getName(), it2->second->getStartTime()));
				
		for (int i = 0; i < meeting.size() - 1; i++)
			for (int j = i + 1; j < meeting.size(); j++)
				if (meeting[i].second == meeting[j].second)
				{
					temp.insert(meeting[i].first);
					temp.insert(meeting[j].first);
				}

		if (temp.size() >= 2)
		{
			std::vector<std::string> overlap;
			for (auto s : temp)
				overlap.push_back(s);
			overlaps.insert(std::make_pair(it1->first, overlap));
		}
		temp.clear();
		meeting.clear();	
	};

	return overlaps;
}

/*****************************************************************************/