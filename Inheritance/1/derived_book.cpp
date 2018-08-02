// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "derived_book.hpp"
#include "messages.hpp"

/*****************************************************************************/

DerivedBook::DerivedBook(
	std::string const & _title,
	int _year,
	Book & _baseBook
)
	: Book(_title,_year)
	, m_baseBook(&_baseBook)
{}

/*****************************************************************************/

std::vector<std::string> &
DerivedBook::getBaseBookAuthors()
{
	return m_baseBook->getAuthorsInfo();
}

/*****************************************************************************/

std::string const & DerivedBook::getBaseBookLang() const
{
	return m_baseBook->getLanguageInfo();
}

/*****************************************************************************/

int DerivedBook::getBaseBookEdition() const
{
	return m_baseBook->getEditionInfo();
}

/*****************************************************************************/
