// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _PROGRAM_HPP_
#define _PROGRAM_HPP_

#include <string>
#include "programcategory.hpp"


class Program
{

	/*-----------------------------------------------------------------*/

public:

	/*-----------------------------------------------------------------*/

	Program(
		std::string const & _name, 
		std::string const & _manufacturer,
		std::string	const & _version,
		int _releaseYear,ProgramCategory _category
	);

	~Program() = default;

	std::string const & getName() const;

	std::string const & getVersion() const;

	std::string const & getCreater() const;

	int getYear() const;

	ProgramCategory getCategory() const;

 	/*-----------------------------------------------------------------*/

private:

	/*-----------------------------------------------------------------*/

	const int m_year;

	const std::string m_name;

	const std::string m_creater;

	ProgramCategory m_category;

	const std::string m_version;

	/*-----------------------------------------------------------------*/

};

inline std::string const & Program::getName() const
{
	return m_name;
}

inline std::string const & Program::getVersion() const
{
	return m_version;
}

inline std::string const & Program::getCreater() const
{
	return m_creater;
}

inline int Program::getYear() const
{
	return m_year;
}

inline ProgramCategory Program::getCategory() const
{
	return m_category;
}

#endif // _PROGRAM_HPP_