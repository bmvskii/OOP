// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _REVISED_BOOK_HPP_
#define _REVISED_BOOK_HPP_

/*****************************************************************************/

#include "derived_book.hpp"

/*****************************************************************************/

class OriginalBook;

class RevisedBook
	: public DerivedBook
{

	/*-----------------------------------------------------------------*/

public:

	RevisedBook(
		std::string const & _title,
		int _year,
		int _editionVersion,
		Book & _baseBook
	);

	~RevisedBook() = default;

	std::vector<std::string> & getAuthorsInfo() override;

	std::string const & getLanguageInfo() const override;

	int getEditionInfo() const override;

private:

	int m_editionVersion;

	/*-----------------------------------------------------------------*/

};


/*****************************************************************************/

#endif // _REVISED_BOOK_HPP_