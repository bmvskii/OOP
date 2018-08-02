// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _BANK_HPP_
#define _BANK_HPP_

/*****************************************************************************/

#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <string>
#include <functional>

class Account;

/*****************************************************************************/

class Bank
{

	/*-----------------------------------------------------------------*/
public:

	Bank();

	~Bank();

	void addAccount(std::unique_ptr<Account> _account);

	bool hasClient(std::string const & _fullOwnerName) const;

	bool hasID(int _ID) const;

	Account * getAccount(int _ID) const;

	int getCurrentID() const;

	void forEachAccount(std::function<void(Account const & _acc)> funct) const;

private:

	int m_currentID;

	std::unordered_map<int, std::unique_ptr<Account> > m_IDs;

	std::unordered_set<std::string> m_clients;

	/*-----------------------------------------------------------------*/
};

/*****************************************************************************/

inline
bool Bank::hasClient(std::string const & _fullOwnerName) const 
{
	return m_clients.find(_fullOwnerName) != m_clients.end();
}

/*****************************************************************************/

inline
bool Bank::hasID(int _ID) const
{
	return m_IDs.find(_ID) != m_IDs.end();
}

/*****************************************************************************/

inline
Account *
Bank::getAccount(int _ID) const
{
	return m_IDs.find(_ID)->second.get();
}

/*****************************************************************************/

inline
int Bank::getCurrentID() const
{
	return m_currentID;
}

/*****************************************************************************/

#endif // _BANK_HPP_