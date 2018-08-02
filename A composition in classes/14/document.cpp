// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "document.hpp"

Document::Document(
	std::string const & _Name,
	std::string const & _Standard
)
	: Name(_Name)
	, Standard(_Standard)
{}

std::string const & Document::getName() const
{
	return Name;
}

std::string const & Document::getStandart() const
{
	return Standard;
}