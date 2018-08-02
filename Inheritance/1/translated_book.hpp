// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _TRANSLATED_BOOK_HPP_
#define _TRANSLATED_BOOK_HPP_

/*****************************************************************************/

#include "derived_book.hpp"

/*****************************************************************************/


class TranslatedBook
	: public DerivedBook
{

	/*-----------------------------------------------------------------*/

public:

	TranslatedBook(
		std::string const & _title,
		int _year,
		std::string const & _lang,
		Book & _baseBook
	);

	~TranslatedBook() = default;

	std::vector<std::string> & getAuthorsInfo() override;

	std::string const & getLanguageInfo() const override;

	int getEditionInfo() const override;

private:

	const std::string m_lang;

	/*-----------------------------------------------------------------*/

};


/*****************************************************************************/


#endif // _TRANSLATED_BOOK_HPP_