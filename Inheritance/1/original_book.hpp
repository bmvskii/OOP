// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _ORIGINAL_BOOK_HPP_
#define _ORIGINAL_BOOK_HPP_

/*****************************************************************************/

#include "book.hpp"
#include <vector>

/*****************************************************************************/


class OriginalBook
	: public Book
{

	/*-----------------------------------------------------------------*/

public:

	OriginalBook(
		std::string const & _title,
		int _year,
		std::string const & _language,
		int _editionVersion,
		std::initializer_list<std::string> m_authors
	);

	~OriginalBook() = default;

	std::vector<std::string> & getAuthorsInfo() override;

	std::string const & getLanguageInfo() const override;

	int getEditionInfo() const override;

	std::string const & getLanguage() const;

	int getEditionVersion() const;

private:
	
	std::vector<std::string> m_authors;

	std::string m_language;

	int m_editionVersion;

	/*-----------------------------------------------------------------*/

};


/*****************************************************************************/

inline
std::string const & 
OriginalBook::getLanguage() const
{
	return m_language;
}

/*****************************************************************************/

inline
int OriginalBook::getEditionVersion() const
{
	return m_editionVersion;
}

/*****************************************************************************/

#endif // _ORIGINAL_BOOK_HPP_