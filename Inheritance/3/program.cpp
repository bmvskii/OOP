// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "program.hpp"
#include "license.hpp"

Program::~Program() = default;

Program::Program(
	std::string const & _name,
	std::string const & _firmName
)
	: m_name(_name)
	, m_firmName(_firmName)
	, m_license(nullptr)
{}

void Program::addLicense(std::unique_ptr<License> _license)
{
	if (!hasLicense())
		m_license = std::move(_license);
}

void Program::use()
{
	m_license->use();
}