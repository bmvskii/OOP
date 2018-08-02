// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "translated_book.hpp"
#include "messages.hpp"

/*****************************************************************************/

TranslatedBook::TranslatedBook(
	std::string const & _title,
	int _year,
	std::string const & _lang,
	Book & _baseBook
)
	: DerivedBook(_title,_year,_baseBook)
	, m_lang(_lang)
{}

/*****************************************************************************/

std::vector<std::string>& TranslatedBook::getAuthorsInfo()
{
	return getBaseBookAuthors();
}

/*****************************************************************************/

std::string const & TranslatedBook::getLanguageInfo() const
{	
	return m_lang;
}

/*****************************************************************************/

int TranslatedBook::getEditionInfo() const
{
	return getBaseBookEdition();
}

/*****************************************************************************/