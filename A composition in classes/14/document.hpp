// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _DOCUMENT_HPP_
#define _DOCUMENT_HPP_

/*****************************************************************************/

#include <string>

class Document
{
	std::string Name;
	std::string Standard;

public:

	Document(std::string const & _Name,std::string const & _standard);
	~Document() = default;
	std::string const & getName() const;
	std::string const & getStandart() const;

};

#endif // _DOCUMENT_HPP_
