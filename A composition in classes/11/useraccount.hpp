// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _USERACCOUNT_HPP_
#define _USERACCOUNT_HPP_

class Program;

#include <string>
#include <memory>

class UserAccount
{

	/*-----------------------------------------------------------------*/

public:
	UserAccount(std::string const & _login,std::string const & _name);
	~UserAccount() = default;

	std::string const & getLogin() const;

	std::string const & getName() const;

	bool hasOfficeProgram() const;

	std::string const & getBrowserVersion() const;

	std::string const & getBrowserName() const;

	void addOfficeProgram(Program const & _officep);

	std::string const & getOfficeProgramName() const;

	std::string const & getOfficeProgramVersion() const;

	void addBrowser(Program const & _browser);

	bool hasBrowser() const;
	
private:
	Program const * m_browser;

	Program const * m_officeProgram;

	std::string m_login;

	std::string m_name;

	/*-----------------------------------------------------------------*/
};


inline std::string const & UserAccount::getLogin() const
{
	return m_login;
}

inline std::string const & UserAccount::getName() const
{
	return m_name;
}

inline bool UserAccount::hasBrowser() const
{
	return m_browser != nullptr;
}

inline bool UserAccount::hasOfficeProgram() const
{
	return m_officeProgram != nullptr;
}

#endif // _USERACCOUNT_HPP_