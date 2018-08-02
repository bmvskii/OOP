// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "original_book.hpp"
#include "messages.hpp"

/*****************************************************************************/

OriginalBook::OriginalBook(
	std::string const & _title,
	int _year,
	std::string const & _language,
	int _editionVersion,
	std::initializer_list<std::string> _authors
)
	: Book(_title,_year)
	, m_language(_language)
	, m_editionVersion(_editionVersion)
	, m_authors(_authors)
{}

/*****************************************************************************/

std::vector<std::string> & OriginalBook::getAuthorsInfo()
{
	return m_authors;
}

/*****************************************************************************/

std::string const & OriginalBook::getLanguageInfo() const
{
	return m_language;
}

/*****************************************************************************/

int OriginalBook::getEditionInfo() const
{
	return m_editionVersion;
}

/*****************************************************************************/