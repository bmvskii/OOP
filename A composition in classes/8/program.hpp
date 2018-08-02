// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _PROGRAM_HPP_
#define _PROGRAM_HPP_

/*****************************************************************************/

#include "genre.hpp"
#include "time.hpp"

#include <string>

/*****************************************************************************/

class Program
{

/*-----------------------------------------------------------------*/

public:

/*-----------------------------------------------------------------*/

	Program(
		std::string const & _name,
		Time const & _time,
		Genre _genre,
		int _rate
	);
	 
	~Program() = default;

	std::string const & getName() const;

	Time const & getStartTime() const;

	Genre getGenre() const;

	int getRate() const;

	void changeRate(int _newRate);

/*-----------------------------------------------------------------*/

private:

/*-----------------------------------------------------------------*/

	std::string m_name;

	Time m_startTime;

	Genre m_genre;

	int m_rate;

/*-----------------------------------------------------------------*/   

};

/*****************************************************************************/

inline
std::string const & Program::getName() const
{
	return m_name;
}

/*****************************************************************************/

inline
Time const &  Program::getStartTime() const
{
	return m_startTime;
}

/*****************************************************************************/

inline
Genre  Program::getGenre() const
{
	return m_genre;
}

/*****************************************************************************/

inline
int  Program::getRate() const
{
	return m_rate;
}

/*****************************************************************************/

inline
void  Program::changeRate(int _newRate)
{
	m_rate = _newRate;
}

/*****************************************************************************/

#endif // _PROGRAM_HPP_
