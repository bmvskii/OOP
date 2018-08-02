// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "book.hpp"
#include "messages.hpp"

/*****************************************************************************/

Book::Book(
	std::string const & _title,
	int _year
)
	: m_title(_title)
	, m_publishingYear(_year)
{}

/*****************************************************************************/