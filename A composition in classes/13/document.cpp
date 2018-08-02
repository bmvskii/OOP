// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "document.hpp"

Document::Document(int _ID,std::string const & _name,std::string const & _path,OwnershipRights _rights
)
{
	ID = _ID;
	Name = _name;
	Path = _path;
	Rights = _rights;
}
