// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _PROGRAM_HPP_
#define _PROGRAM_HPP_

/*****************************************************************************/

class License;

/*****************************************************************************/

#include <string>
#include <memory>

class Program
{

	/*-----------------------------------------------------------------*/
public:
	Program(
		std::string const & _name,
		std::string const & _firmName
	);

	~Program();

	std::string const & getName() const;
	
	std::string const & getFirmName() const;

	void addLicense(std::unique_ptr<License> _license);
	
	bool hasLicense() const;

	License * getLicense() const;

	void use();

private:

	const std::string m_name;
	const std::string m_firmName;

	std::unique_ptr<License> m_license;
	/*-----------------------------------------------------------------*/

};

inline std::string const & Program::getName() const
{
	return m_name;
}

inline std::string const & Program::getFirmName() const
{
	return m_firmName;
}

inline bool Program::hasLicense() const
{
	return m_license != nullptr;
}

inline License * Program::getLicense() const
{
	return m_license.get();
}

#endif // _PROGRAM_HPP_