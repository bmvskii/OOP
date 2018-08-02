// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "tvchannel.hpp"
#include "messages.hpp"

/*****************************************************************************/

void TVChannel::removeProgram(Program const & _p)
{
	for (int i = 0; i < 7; i++)
		for (auto it = m_programs[i].begin(); it != m_programs[i].end(); it++)
			if (it->get()->getName() == _p.getName())
			{
				m_programs[i].erase(it);
				break;
			}
}

/*****************************************************************************/

bool TVChannel::hasProgram(Program const & _p)
{
	for (int i = 0; i < 7; i++)
		for (auto it = m_programs[i].begin(); it != m_programs[i].end(); it++)
			if (it->get()->getName() == _p.getName())
				return true;
	return false;
}

/*****************************************************************************/

void TVChannel::forEachDay(std::function<void(Day _d, std::vector<std::unique_ptr<Program>> const & _p)> _f) const
{
	for (int i = 0; i < 7; i++)
	{
		auto const & p = m_programs[i];
		_f(static_cast<Day>(i), p);
	}
}

/*****************************************************************************/

void TVChannel::forEachProgram(std::function<void(Day _d,Program const&_p)> _f) const
{
	for (int i = 0; i < 7; i++)
		for (auto const & p : m_programs[i])
			_f(static_cast<Day>(i), *p.get());
}

/*****************************************************************************/

TVChannel::TVChannel(std::string const & _name)
	: m_name(_name)
{}

/*****************************************************************************/

std::pair<Day, Time> const & TVChannel::getLastTime() const
{
	std::pair<Day, Time> p;
	for (int i = 0; i < 7; i++)
		if (m_programs[i].empty())
			continue;
		else
		{
			p = std::make_pair(static_cast<Day>(i), m_programs[i].back()->getStartTime());
			break;
		}

	return p;
}

/*****************************************************************************/

bool TVChannel::hasProgramOnDay(Day _d) const
{
	if (!m_programs[static_cast<int>(_d)].empty())
		return true;
	return false;
}

/*****************************************************************************/

Day TVChannel::getProgramDay(Program const & _p) const
{
	for (int i = 0; i < 7; i++)
		for (auto const & p : m_programs[i])
			if (p->getName() == _p.getName())
				return static_cast<Day>(i);
}

/*****************************************************************************/   