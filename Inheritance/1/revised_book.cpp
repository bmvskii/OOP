// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "revised_book.hpp"
#include "messages.hpp"

/*****************************************************************************/

RevisedBook::RevisedBook(
	std::string const & _title,
	int _year,
	int _editionVersion,
	Book & _baseBook
)
	: DerivedBook(_title,_year, _baseBook)
	, m_editionVersion(_editionVersion)
{}

/*****************************************************************************/

std::vector<std::string>& RevisedBook::getAuthorsInfo()
{
	return getBaseBookAuthors();
}

/*****************************************************************************/

std::string const & RevisedBook::getLanguageInfo() const
{
	return getBaseBookLang();
}

/*****************************************************************************/

int RevisedBook::getEditionInfo() const
{
	return m_editionVersion;
}

/*****************************************************************************/