// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "program.hpp"

Program::Program(
	std::string const & _name,
	std::string const & _creater,
	std::string	const & _version,
	int _year,ProgramCategory _category
)
	: m_name(_name),
	m_creater(_creater), 
	m_version(_version)
	, m_year(_year), m_category(_category)
{}