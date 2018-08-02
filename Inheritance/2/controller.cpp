// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "controller.hpp"
#include "messages.hpp"
#include "bank.hpp"
#include "account.hpp"
#include "overdraftaccount.hpp"

/*****************************************************************************/

Controller::Controller()
{
	m_bank = new Bank();
};

/*****************************************************************************/

Controller::~Controller()
{
	delete m_bank;
};

/*****************************************************************************/

int Controller::createAccount(std::string const & _ownerName, double _initialBalance)
{
	if (_ownerName.empty())
		throw std::logic_error(Messages::OwnerNameIsEmpty);

	if (_initialBalance < 0)
		throw std::logic_error(Messages::NegativeInitialBalance);

	if (m_bank->hasClient(_ownerName))
		throw std::logic_error(Messages::OwnerNameNotUnique);
	
	auto account = std::make_unique<Account>(_ownerName, _initialBalance);
	m_bank->addAccount(std::move(account));
	return m_bank->getCurrentID();
}

/*****************************************************************************/

int Controller::createOverdraftAccount(std::string const & _ownerName, double _initialBalance, double _overdraftLimit)
{
	if (_ownerName.empty())
		throw std::logic_error(Messages::OwnerNameIsEmpty);

	if (_initialBalance < 0)
		throw std::logic_error(Messages::NegativeInitialBalance);

	if (_overdraftLimit < 0)
		throw std::logic_error(Messages::NegativeOverdraft);

	if (m_bank->hasClient(_ownerName))
		throw std::logic_error(Messages::OwnerNameNotUnique);

	auto overdraftaccount = std::make_unique<OverdraftAccount>(_ownerName, _initialBalance, _overdraftLimit);
	m_bank->addAccount(std::move(overdraftaccount));
	return m_bank->getCurrentID();
}

/*****************************************************************************/

std::string const &
Controller::getAccountOwnerName(int _accountID) const
{
	if (!m_bank->hasID(_accountID))
		throw std::logic_error(Messages::UnknownAccountID);

	return m_bank->getAccount(_accountID)->getOwnerName();
}

/*****************************************************************************/

double Controller::getAccountBalance(int _accountID) const
{
	if (!m_bank->hasID(_accountID))
		throw std::logic_error(Messages::UnknownAccountID);

	return m_bank->getAccount(_accountID)->getBalance();
}

/*****************************************************************************/

bool Controller::isOverdraftAllowed(int _accountID) const
{
	if (!m_bank->hasID(_accountID))
		throw std::logic_error(Messages::UnknownAccountID);

	return m_bank->getAccount(_accountID)->getOverdraftLimit() != 0;
}

/*****************************************************************************/

double Controller::getOverdraftLimit(int _accountID) const
{
	if (!m_bank->hasID(_accountID))
		throw std::logic_error(Messages::UnknownAccountID);

	return m_bank->getAccount(_accountID)->getOverdraftLimit();
}

/*****************************************************************************/

void Controller::deposit(int _accountID, double _amount)
{
	if (!m_bank->hasID(_accountID))
		throw std::logic_error(Messages::UnknownAccountID);

	if (_amount <= 0)
		throw std::logic_error(Messages::NonPositiveDeposit);
	
	m_bank->getAccount(_accountID)->setBalance(_amount);
}

/*****************************************************************************/

void Controller::withdraw(int _accountID, double _amount)
{
	if (!m_bank->hasID(_accountID))
		throw std::logic_error(Messages::UnknownAccountID);

	if (_amount <= 0)
		throw std::logic_error(Messages::NonPositiveWithdrawal);

	auto account = m_bank->getAccount(_accountID);
	if (_amount > (account->getBalance() + account->getOverdraftLimit()))
		throw std::logic_error(Messages::WithdrawalLimitExceeded);

	account->setBalance(-_amount);
}

/*****************************************************************************/

void Controller::transfer(int _sourceAccountID, int _targetAccountID, double _amount)
{
	if (!m_bank->hasID(_sourceAccountID) || !m_bank->hasID(_targetAccountID))
		throw std::logic_error(Messages::UnknownAccountID);

	if (_amount <= 0)
		throw std::logic_error(Messages::NonPositiveTransfer);

	auto account = m_bank->getAccount(_sourceAccountID);
	if (_amount > (account->getBalance() + account->getOverdraftLimit()))
		throw std::logic_error(Messages::WithdrawalLimitExceeded);

	account->setBalance(-_amount);
	m_bank->getAccount(_targetAccountID)->setBalance(_amount);
}

/*****************************************************************************/

double Controller::getTotalBankBalance() const
{
	double total = 0.0;

	m_bank->forEachAccount(
		[&](Account const & _a)
	{
		total += _a.getBalance();
	}
	);

	return total;
}

/*****************************************************************************/

double Controller::getTotalBankDeposits() const
{
	double total = 0.0;

	m_bank->forEachAccount(
		[&](Account const & _a)
	{
		if (_a.getBalance() > 0)
			total += _a.getBalance();
	}
	);

	return total;
}

/*****************************************************************************/

double Controller::getTotalBankOverdrafts() const
{
	double total = 0.0;

	m_bank->forEachAccount(
		[&](Account const & _a)
	{
		if (_a.getBalance() < 0)
			total += std::abs(_a.getBalance());
	}
	);

	return total;
}

/*****************************************************************************/