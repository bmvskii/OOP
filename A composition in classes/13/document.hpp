// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _DOCUMENT_HPP_
#define _DOCUMENT_HPP_

#include <string>
#include "ownershiprights.hpp"

class Document
{
	int ID;
	std::string Name;
	std::string Path;
	OwnershipRights Rights;

public:

	Document(int _ID,std::string const & _name,std::string const & _path,OwnershipRights _rights);
	~Document() = default;
	int getID() const 
	{
		return ID;
	}
	std::string const & getName() const
	{
		return Name;
	}
	std::string const & getPath() const 
	{
		return Path;
	}
	OwnershipRights getRights() const 
	{
		return Rights;
	}
};

#endif // _DOCUMENT_HPP_
