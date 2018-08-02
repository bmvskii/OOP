// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _USER_HPP_
#define _USER_HPP_

#include "ownershiprights.hpp"

#include <unordered_map>
#include <string>
#include <functional>

class Document;

class User
{
	std::string Login;
	std::string FullName;
	std::unordered_map<Document const *, OwnershipRights> Documents;

public:

	User(std::string const & _login,std::string const & _fullName);
	~User() = default;
	std::string const & getLogin() const
	{
		return Login;
	}
	std::string const & getFullName() const
	{
		return FullName;
	}
	void forEachDocument(std::function<void(Document const & _d, OwnershipRights _r)> _f)
	{
		for (auto const & d : Documents)
			_f(*d.first, d.second);
	}
	void addDocument(Document const & _d, OwnershipRights _r)
	{
		Documents.insert(std::make_pair(&_d, _r));
	}
	void changeDocumentRights(int _ID, OwnershipRights _r);
	bool hasDocumentRights(int _ID) const;
	OwnershipRights getDocumentRights(int _ID) const;
};

#endif // _USER_HPP_
