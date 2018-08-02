// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "user.hpp"
#include "messages.hpp"
#include "document.hpp"

User::User(std::string const & _Login,std::string const & _FullName)
{
	Login = _Login;
	FullName = _FullName;
}

bool User::hasDocumentRights(int _ID) const
{
	for (auto it = Documents.begin(); it != Documents.end(); ++it)
		if (it->first->getID() == _ID)
			return it->second != OwnershipRights::NoAccess;
	return false;
}

void User::changeDocumentRights(int _ID, OwnershipRights _r)
{
	for (auto it = Documents.begin(); it != Documents.end(); ++it)
		if (it->first->getID() == _ID)
		{
			it->second = _r;
			return;
		}
}

OwnershipRights User::getDocumentRights(int _ID) const
{
	for (auto it = Documents.begin(); it != Documents.end(); ++it)
		if (it->first->getID() == _ID)
			return it->second;
}
