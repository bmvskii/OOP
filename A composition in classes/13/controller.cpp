// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "controller.hpp"
#include "messages.hpp"
#include "user.hpp"
#include "document.hpp"

Controller::Controller() = default;

Controller::~Controller() = default;

void Controller::addUser(std::string const & _login, std::string const & _fullName)
{
	if (_login.empty()) throw std::logic_error(Messages::UserLoginIsEmpty);
	if (_fullName.empty()) throw std::logic_error(Messages::UserFullNameEmpty);
	if (m_users.find(_login) != m_users.end()) throw std::logic_error(Messages::UserLoginAlreadyExists);
		
	m_users.insert(std::make_pair(_login,std::make_unique<User>(_login, _fullName)));
}

std::string const & Controller::getUserFullName(std::string const & _login) const
{
	if (m_users.find(_login) == m_users.end()) throw std::logic_error(Messages::UserLoginDoesNotExist);

	return m_users.find(_login)->second->getFullName();
}

void Controller::addDocument(int _documentID,std::string const & _name,std::string const & _path,OwnershipRights _defaultRight)
{
	if (m_documents.find(_documentID) != m_documents.end()) throw std::logic_error(Messages::DocumentAlreadyExists);
	if (_name.empty()) throw std::logic_error(Messages::DocumentNameIsEmpty);
	if (_path.empty()) throw std::logic_error(Messages::DocumentPathIsEmpty);

	m_documents.insert(std::make_pair(_documentID, std::make_unique<Document>(_documentID, _name, _path, _defaultRight)));
}

std::string const & Controller::getDocumentName(int _documentID) const
{
	if (m_documents.find(_documentID) == m_documents.end()) throw std::logic_error(Messages::DocumentDoesNotExist);

	return m_documents.find(_documentID)->second->getName();
}

std::string const & Controller::getDocumentPath(int _documentID) const
{
	if (m_documents.find(_documentID) == m_documents.end()) throw std::logic_error(Messages::DocumentDoesNotExist);

	return m_documents.find(_documentID)->second->getPath();
}

OwnershipRights Controller::getDocumentDefaultRights(int _documentID) const
{
	if (m_documents.find(_documentID) == m_documents.end()) throw std::logic_error(Messages::DocumentDoesNotExist);

	return m_documents.find(_documentID)->second->getRights();
}

void Controller::addDocumentRightsForUser(std::string const & _userLogin, int _documentID, OwnershipRights _rights)
{
	if (m_documents.find(_documentID) == m_documents.end()) throw std::logic_error(Messages::DocumentDoesNotExist);
	if (m_users.find(_userLogin) == m_users.end()) throw std::logic_error(Messages::UserLoginDoesNotExist);
	if (m_users.find(_userLogin)->second->hasDocumentRights(m_documents.find(_documentID)->second->getID())) throw std::logic_error(Messages::DocumentRightsAlreadyDefined);

	m_users.find(_userLogin)->second->addDocument(*m_documents.find(_documentID)->second.get(), _rights);
}

void Controller::changeDocumentRightsForUser(std::string const & _userLogin, int _documentID, OwnershipRights _rights)
{
	if (m_documents.find(_documentID) == m_documents.end()) throw std::logic_error(Messages::DocumentDoesNotExist);
	if (m_users.find(_userLogin) == m_users.end()) throw std::logic_error(Messages::UserLoginDoesNotExist);
	if (!m_users.find(_userLogin)->second->hasDocumentRights(m_documents.find(_documentID)->second->getID())) throw std::logic_error(Messages::DocumentRightsUndefined);

	m_users.find(_userLogin)->second->changeDocumentRights(m_documents.find(_documentID)->second->getID(), _rights);
}

void Controller::eraseDocumentRightsForUser(std::string const & _userLogin, int _documentID)
{
	if (m_documents.find(_documentID) == m_documents.end()) throw std::logic_error(Messages::DocumentDoesNotExist);
	if (m_users.find(_userLogin) == m_users.end()) throw std::logic_error(Messages::UserLoginDoesNotExist);
	if (!m_users.find(_userLogin)->second->hasDocumentRights(m_documents.find(_documentID)->second->getID())) throw std::logic_error(Messages::DocumentRightsUndefined);

	m_users.find(_userLogin)->second->changeDocumentRights(m_documents.find(_documentID)->second->getID(),m_documents.find(_documentID)->second->getRights());
}

OwnershipRights Controller::getDocumentRightsForUser(std::string const & _userLogin, int _documentID) const
{
	if (m_documents.find(_documentID) == m_documents.end()) throw std::logic_error(Messages::DocumentDoesNotExist);
	if (m_users.find(_userLogin) == m_users.end()) throw std::logic_error(Messages::UserLoginDoesNotExist);

	OwnershipRights result;
	m_users.find(_userLogin)->second->forEachDocument([&](Document const & _d, OwnershipRights _r)
	{
		if (_d.getID() == _documentID)
		{
			result = _r;
			return;
		}}
	);
	return result;
}

Controller::AllRights Controller::getUserPermissionsReport() const
{
	AllRights result;
	for (auto it1 = m_users.begin(); it1 != m_users.end(); it1++)
	{
		std::unordered_map<int, OwnershipRights> temp;
		for (auto it2 = m_documents.begin(); it2 != m_documents.end(); it2++)
		{
			if (it1->second->hasDocumentRights(it2->second->getID()))
			{
				temp.insert(std::make_pair(it2->second->getID(), it1->second->getDocumentRights(it2->second->getID())));
			}
			else
			{
				temp.insert(std::make_pair(it2->second->getID(), it2->second->getRights()));
			}
		}
		result.insert(std::make_pair(it1->first, temp));
	}
	return result;
}

Controller::DocumentsInfo Controller::getDocumentsNotHavingPermittedUsers() const
{
	DocumentsInfo result;
	for (auto it1 = m_documents.begin(); it1 != m_documents.end(); it1++)
	{
		bool flag = false;
		for (auto it2 = m_users.begin(); it2 != m_users.end(); it2++)
		{
			if (it2->second->hasDocumentRights(it1->second->getID()))
			{
				flag = true;

			}
		}
		if (flag == false)
		{
			result.insert(std::make_pair(it1->second->getID(), it1->second->getName()));
		}
	}
	return result;
}

std::unordered_set<std::string> Controller::getUsersNotHavingPermittedDocuments() const
{
	std::unordered_set<std::string> result;
	for (auto it1 = m_users.begin(); it1 != m_users.end(); ++it1) 
	{
		bool flag = false;
		for (auto it2 = m_documents.begin(); it2 != m_documents.end(); ++it2)
		{
			if (it1->second->hasDocumentRights(it2->second->getID()))
			{
				flag = true;
			}
		}
			
		if (flag == false)
		{
			result.insert(it1->first);
		}
	}
	return result;
}

Controller::DocumentsInfo Controller::getDocumentsHavingMultipleWriteUsers() const
{
	DocumentsInfo result;
	for (auto it1 = m_documents.begin(); it1 != m_documents.end(); it1++)
	{
		int k = 0;
		for (auto it2 = m_users.begin(); it2 != m_users.end(); it2++)
		{
			if (it2->second->getDocumentRights(it1->second->getID()) == OwnershipRights::ReadAndWrite || it1->second->getRights() == OwnershipRights::ReadAndWrite)
			{
				k++;
			}
		}
		if (k > 1)
		{
			result.insert(std::make_pair(it1->second->getID(), it1->second->getName()));
		}
	}
	return result;
}