// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _PARTICIPANT_HPP_
#define _PARTICIPANT_HPP_

/*****************************************************************************/

#include <string>

/*****************************************************************************/


class Participant
{

/*-----------------------------------------------------------------*/

public:

/*-----------------------------------------------------------------*/

	Participant(
		std::string const & _name,
		std::string const & _email
	);

	~Participant() = default;

	std::string const & getName() const;

	std::string const & getEmail() const;

/*-----------------------------------------------------------------*/

private:

/*-----------------------------------------------------------------*/

	std::string m_name;

	std::string m_email;

/*-----------------------------------------------------------------*/  

};

/*****************************************************************************/

inline
std::string const & Participant::getName() const
{
	return m_name;
}

/*****************************************************************************/

inline
std::string const & Participant::getEmail() const
{
	return m_email;
}

/*****************************************************************************/

#endif // _PARTICIPANT_HPP_
