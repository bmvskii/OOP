// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "useraccount.hpp"
#include "program.hpp"

UserAccount::UserAccount(
	std::string const & _login,
	std::string const & _name
)
	: m_login(_login)
	, m_name(_name)
{}

std::string const & UserAccount::getBrowserVersion() const
{
	return m_browser->getVersion();
}


std::string const & UserAccount::getBrowserName() const
{
	return m_browser->getName();
}

std::string const & UserAccount::getOfficeProgramName() const
{
	return m_officeProgram->getName();
}

void UserAccount::addOfficeProgram(Program const & _officep)
{
	m_officeProgram = &_officep;
}

std::string const & UserAccount::getOfficeProgramVersion() const
{
	return m_officeProgram->getVersion();
}

void UserAccount::addBrowser(Program const & _browser)
{
	m_browser = &_browser;
}