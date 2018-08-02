// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _PAYMENT_HPP_
#define _PAYMENT_HPP_

/*****************************************************************************/

#include <string>
#include "datetime.hpp"

class Organization;

/*****************************************************************************/

class Payment
{

/*-----------------------------------------------------------------*/

public:

/*-----------------------------------------------------------------*/

	Payment(
		Organization const & _sender,
		Organization const & _reciever,
		std::string const & _ID,
		std::string const & _purpose,
		DateTime const & _date,
		double _summary
	);

	~Payment() = default;

	std::string const & getID() const;

	std::string const & getPurpose() const;

	Organization const & getReceiver() const;

	Organization const & getSender() const;

	int getSummary() const;

	void changeSummary(double _newSumm);

	DateTime const & getDateTime() const;

/*-----------------------------------------------------------------*/

private:

/*-----------------------------------------------------------------*/
	
	Organization const * m_sender, * m_reciever;

	std::string m_ID;

	std::string m_purpose;

	DateTime m_date;

	double m_summary;

/*-----------------------------------------------------------------*/

};

/*****************************************************************************/

inline
std::string const & Payment::getID() const
{
	return m_ID;
}

/*****************************************************************************/

inline
std::string const & Payment::getPurpose() const
{
	return m_purpose;
}

/*****************************************************************************/

inline
Organization const & Payment::getReceiver() const
{
	return * m_reciever;
}

/*****************************************************************************/

inline
Organization const & Payment::getSender() const
{
	return *m_sender;
}

/*****************************************************************************/

inline
int Payment::getSummary() const
{
	return m_summary;
}

/*****************************************************************************/

inline
void Payment::changeSummary(double _newSumm)
{
	m_summary = _newSumm;
}

/*****************************************************************************/

inline
DateTime const & Payment::getDateTime() const
{
	return m_date;
}

/*****************************************************************************/

#endif // _PAYMENT_HPP_
