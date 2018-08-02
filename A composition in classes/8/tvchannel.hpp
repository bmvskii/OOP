// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _TVCHANNEL_HPP_
#define _TVCHANNEL_HPP_

/*****************************************************************************/

#include "day.hpp"
#include "time.hpp"
#include "program.hpp"

#include <string>
#include <memory>
#include <vector>
#include <functional>

class Program;

/*****************************************************************************/

class TVChannel
{

/*-----------------------------------------------------------------*/

public:

/*-----------------------------------------------------------------*/

	TVChannel(std::string const & _name);

	~TVChannel() = default;

	std::string const & getName() const;

	void addProgram(Day _d, std::unique_ptr<Program> _p);

	Day getProgramDay(Program const & _p) const;

	void removeProgram(Program const & _p);

	bool hasProgram(Program const & _p);

	void forEachDay(std::function<void(Day _d, std::vector<std::unique_ptr<Program>> const & _p)> _f) const;

	void forEachProgram(std::function<void(Day _d, Program const & _p)> _f) const;

	int getProgramCount() const;

	std::pair<Day, Time> const & getLastTime() const;

	bool hasProgramOnDay(Day _d) const;

/*-----------------------------------------------------------------*/

private:

/*-----------------------------------------------------------------*/

	std::string m_name;

	std::vector<std::unique_ptr<Program>> m_programs[7];

/*-----------------------------------------------------------------*/

};

/*****************************************************************************/

inline
std::string const & TVChannel::getName() const
{
	return m_name;
}

/*****************************************************************************/

inline
void TVChannel::addProgram(Day _d, std::unique_ptr<Program> _p)
{
	m_programs[static_cast<int>(_d)].push_back(std::move(_p));
}

/*****************************************************************************/

inline
int TVChannel::getProgramCount() const
{
	int total = 0;
	for (int i = 0; i < 7; i++)
		total += m_programs[i].size();
	return total;
}

/*****************************************************************************/

#endif // _TVCHANNEL_HPP_
