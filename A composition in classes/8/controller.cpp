// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "controller.hpp"
#include "messages.hpp"
#include "program.hpp"
#include "tvchannel.hpp"

#include <algorithm>
#include <iostream>
#include <set>

/*****************************************************************************/

Controller::Controller() = default;

/*****************************************************************************/

Controller::~Controller() = default;

/*****************************************************************************/

void Controller::addChannel(const std::string & _channelName)
{
	if (_channelName.empty())
		throw std::logic_error(Messages::EmptyChannelName);

	if (m_channels.find(_channelName) != m_channels.end())
		throw std::logic_error(Messages::DuplicateChannel);

	m_channels.insert(std::make_pair(_channelName, std::make_unique<TVChannel>(_channelName)));
}

/*****************************************************************************/

void Controller::addProgram(
	const std::string & _channelName,
	Day _day,
	const std::string & _programName,
	Time _startTime,
	Genre _genre,
	int _rating
)
{
	if (m_channels.find(_channelName) == m_channels.end())
		throw std::logic_error(Messages::ChannelCannotBeFound);

	switch (_day)
	{
	case Day::Monday: break;
	case Day::Tuesday: break;
	case Day::Wednesday: break;
	case Day::Thursday: break;
	case Day::Friday: break;
	case Day::Saturday: break;
	case Day::Sunday: break;
	default:
		throw std::logic_error(Messages::InvalidDayIndex);
	}

	if (_programName.empty())
		throw std::logic_error(Messages::EmptyProgramName);

	if (m_channels.find(_channelName)->second->getProgramCount() != 0)
	{
		auto pair = m_channels.find(_channelName)->second->getLastTime();
		if (pair.first > _day || (pair.first == _day && pair.second >= _startTime))
			throw std::logic_error(Messages::InvalidProgramTime);
	}
	
	if (_rating < 1 || _rating > 5)
		throw std::logic_error(Messages::InvalidRatingValue);

	m_channels.find(_channelName)->second->addProgram(_day, std::make_unique<Program>(
		_programName,
		_startTime,
		_genre,
		_rating
		));
}

/*****************************************************************************/

std::vector<std::string> Controller::getPrograms(const std::string & _channelName, Day _day) const
{
	if (m_channels.find(_channelName) == m_channels.end())
		throw std::logic_error(Messages::ChannelCannotBeFound);
	
	switch (_day)
	{
	case Day::Monday: break;
	case Day::Tuesday: break;
	case Day::Wednesday: break;
	case Day::Thursday: break;
	case Day::Friday: break;
	case Day::Saturday: break;
	case Day::Sunday: break;
	default:
		throw std::logic_error(Messages::InvalidDayIndex);
	}

	std::vector<std::string> programs;

	m_channels.find(_channelName)->second->forEachProgram(
		[&](Day _d, Program const & _p)
	{
		if (_d == _day) programs.push_back(_p.getName());
	}
	);

	return programs;
}

/*****************************************************************************/

std::vector<std::vector<std::string>> Controller::getPrograms(const std::string & _channelName) const
{
	if (m_channels.find(_channelName) == m_channels.end())
		throw std::logic_error(Messages::ChannelCannotBeFound);

	std::vector<std::vector<std::string>> programs;
	std::vector<std::string> temp;
	for (int i = 0; i < 7; i++) programs.push_back(temp);

	Day current = Day::Monday;
	
	if (m_channels.find(_channelName)->second->getProgramCount() != 0)
		m_channels.find(_channelName)->second->forEachDay(
			[&](Day _d, std::vector<std::unique_ptr<Program>> const & _p)
	{
		if (!_p.empty())
		{
			for (auto const & p : _p)
				programs[static_cast<int>(_d)].push_back(p->getName());
		}
		else {
			switch (current)
			{
			case Day::Monday: current = Day::Tuesday; break;
			case Day::Tuesday: current = Day::Wednesday; break;
			case Day::Wednesday: current = Day::Thursday; break;
			case Day::Thursday: current = Day::Friday; break;
			case Day::Friday: current = Day::Saturday; break;
			case Day::Saturday: current = Day::Sunday; break;
			case Day::Sunday: break;
			default: break;
			}
		}
	});

	return programs;
}

/*****************************************************************************/

std::vector<std::string> Controller::getAllSportPrograms() const
{
	std::vector<std::string> sportPrograms;
	std::set<std::string> temp;

	for (auto const & c : m_channels)
		c.second->forEachProgram(
			[&](Day _d, Program const & _p) 
	{
		if (_p.getGenre() == Genre::Sport)
			temp.insert(_p.getName());
	});
	
	for (auto s : temp)
		sportPrograms.push_back(s);
	
	return sportPrograms;
}

/*****************************************************************************/

std::string Controller::getChannelWithHighestAverageRating() const
{
	std::string channel;
	double maxRate = 0;
	double totalRate;

	for (auto const & c : m_channels)
	{
		totalRate = 0;
		c.second->forEachProgram(
			[&](Day _d, Program const & _p)
		{
			totalRate += _p.getRate();
		});
		totalRate /= c.second->getProgramCount();
		if (totalRate > maxRate)
		{
			maxRate = totalRate;
			channel = c.first;
		}
	}

	return channel;
}

/*****************************************************************************/

std::string Controller::getLongestProgram() const
{
	std::string longestProgram;
	int max = 0;

	for (auto const & c : m_channels)
	{
		c.second->forEachDay(
			[&](Day _d, std::vector<std::unique_ptr<Program>> const & _p)
		{
			for (int i = 0; i < _p.size(); i++)
			{
				int lhs, rhs;
				if (i == _p.size() - 1)
				{
					lhs = _p[i].get()->getStartTime().getHours() * 10000 + _p[i].get()->getStartTime().getMinutes() * 100 + _p[i].get()->getStartTime().getSeconds();
					rhs = _p[0].get()->getStartTime().getHours() * 10000 + _p[0].get()->getStartTime().getMinutes() * 100 + _p[0].get()->getStartTime().getSeconds();
				}
				else
				{
					lhs = _p[i].get()->getStartTime().getHours() * 10000 + _p[i].get()->getStartTime().getMinutes() * 100 + _p[i].get()->getStartTime().getSeconds();
					rhs = _p[i + 1].get()->getStartTime().getHours() * 10000 + _p[i + 1].get()->getStartTime().getMinutes() * 100 + _p[i + 1].get()->getStartTime().getSeconds();
				}
				
				int result = rhs < lhs ? rhs += 240000, rhs - lhs : rhs - lhs;
				if (result > max)
				{
					max = result;
					longestProgram = _p[i].get()->getName();
				}

			}
		});
	}

	return longestProgram;
}

/*****************************************************************************/

std::pair<std::string, std::string> Controller::getBestProgramChoiceFor(Day _day, int _hour) const
{
	switch (_day)
	{
	case Day::Monday: break;
	case Day::Tuesday: break;
	case Day::Wednesday: break;
	case Day::Thursday: break;
	case Day::Friday: break;
	case Day::Saturday: break;
	case Day::Sunday: break;
	default:
		throw std::logic_error(Messages::InvalidDayIndex);
	}

	if (_hour < 0 || _hour > 23)
		throw std::logic_error(Messages::InvalidDateTime);
	
	std::pair<std::string, std::string> result;
	std::vector<std::pair<std::pair<TVChannel const *, Program const *>, int>> channelsAndPrograms;

	int difference = 10001;
	double maxRate = 0;
	int rhs = _hour * 10000;
	for (auto const & c : m_channels)
	{
		c.second->forEachDay(
			[&](Day _d, std::vector<std::unique_ptr<Program>> const & _p)
		{
			if (_d == _day)
				for (auto const & p : _p)
				{
					int lhs = p.get()->getStartTime().getHours() * 10000 + p.get()->getStartTime().getMinutes() * 100 + p.get()->getStartTime().getSeconds();
					if (std::abs(lhs - rhs) <= 10000)
						channelsAndPrograms.push_back(std::make_pair(std::make_pair(c.second.get(), p.get()), p->getRate()));
				}
		});
	}

	for (int i = 0; i < channelsAndPrograms.size(); i++)
	{
		if (maxRate < channelsAndPrograms[i].second)
		{	
			result = std::make_pair(channelsAndPrograms[i].first.first->getName(), channelsAndPrograms[i].first.second->getName());
			maxRate = channelsAndPrograms[i].second;
		}
	}

	return result;
}

/*****************************************************************************/