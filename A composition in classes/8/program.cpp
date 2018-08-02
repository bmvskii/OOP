// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "program.hpp"

/*****************************************************************************/

Program::Program(
	std::string const & _name,
	Time const & _time,
	Genre _genre,
	int _rate
)
	: m_name(_name)
	, m_startTime(_time)
	, m_genre(_genre)
	, m_rate(_rate)
{}

/*****************************************************************************/