// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _DERIVED_BOOK_HPP_
#define _DERIVED_BOOK_HPP_

/*****************************************************************************/

#include "book.hpp"
#include <string>
#include <memory>

/*****************************************************************************/

class DerivedBook
	: public Book
{

	/*-----------------------------------------------------------------*/

protected:

	DerivedBook(
		std::string const & _title,
		int _year,
		Book & _baseBook
	);

public:

	~DerivedBook() = default;

	Book const * getBaseBook() const;

	std::vector<std::string> & getAuthorsInfo() = 0;

	std::string const & getLanguageInfo() const = 0;

	int getEditionInfo() const = 0;

	std::vector<std::string> & getBaseBookAuthors();

	std::string const & getBaseBookLang() const;

	int getBaseBookEdition() const;

private:

	Book * m_baseBook;

	/*-----------------------------------------------------------------*/

};

/*****************************************************************************/

inline
Book const * DerivedBook::getBaseBook() const
{
	return m_baseBook;
}

/*****************************************************************************/

#endif // _DERIVED_BOOK_HPP_