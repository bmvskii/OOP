// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _ACCOUNT_HPP_
#define _ACCOUNT_HPP_

/*****************************************************************************/

#include <string>

class Account
{

	/*-----------------------------------------------------------------*/
public:

	Account(
		std::string const & _fullOwnerName,
		double _startBalance
	);

	virtual ~Account() = default;

	virtual double getOverdraftLimit() const;

	void setID(int _ID);

	int getID() const;

	std::string const & getOwnerName() const;

	double getBalance() const;

	void setBalance(double _balance);

private:

	int m_ID;
	std::string m_fullOwnerName;
	double m_currentBalance;

	/*-----------------------------------------------------------------*/

};

/*****************************************************************************/

inline
int Account::getID() const
{
	return m_ID;
}

/*****************************************************************************/

inline
std::string const &
Account::getOwnerName() const
{
	return m_fullOwnerName;
}

/*****************************************************************************/

inline
double Account::getBalance() const
{
	return m_currentBalance;
}

/*****************************************************************************/

inline
void Account::setID(int _ID)
{
	m_ID = _ID;
}

/*****************************************************************************/

inline
void Account::setBalance(double _balance)
{
	m_currentBalance += _balance;
}

/*****************************************************************************/

#endif // _ACCOUNT_HPP_