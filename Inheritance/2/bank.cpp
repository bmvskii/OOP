// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "bank.hpp"
#include "account.hpp"

/*****************************************************************************/

Bank::Bank() = default;

/*****************************************************************************/

Bank::~Bank() = default;

/*****************************************************************************/

void Bank::addAccount(std::unique_ptr<Account> _account)
{
	m_currentID++;
	m_clients.insert(_account->getOwnerName());
	_account->setID(m_currentID);
	m_IDs.insert(std::make_pair(m_currentID, std::move(_account)));
}

/*****************************************************************************/

void Bank::forEachAccount(std::function<void(Account const & _acc)> funct) const
{
	for (auto const & acc : m_IDs)
		funct(*acc.second);
}

/*****************************************************************************/