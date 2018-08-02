// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _BOOK_HPP_
#define _BOOK_HPP_

/*****************************************************************************/

#include <string>
#include <vector>
#include <initializer_list>

class Book
{

	/*-----------------------------------------------------------------*/

protected:

	Book(
		std::string const & _title,
		int _year
	);

public:

	virtual ~Book() = default;

	std::string const & getTitle() const;

	int getPublishingYear() const;

	virtual	std::vector<std::string> & getAuthorsInfo() = 0;

	virtual std::string const & getLanguageInfo() const = 0;

	virtual int getEditionInfo() const = 0;

private:

	const std::string m_title;

	int m_publishingYear;

	/*-----------------------------------------------------------------*/

};

/*****************************************************************************/

inline
std::string const & 
Book::getTitle() const
{
	return m_title;
}

/*****************************************************************************/

inline
int Book::getPublishingYear() const
{
	return m_publishingYear;
}

/*****************************************************************************/

#endif // _BOOK_HPP_