// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "payment.hpp"

/*****************************************************************************/

// TODO implement your methods here

/*****************************************************************************/

Payment::Payment(
	Organization const & _sender,
	Organization const & _reciever,
	std::string const & _ID,
	std::string const & _purpose,
	DateTime const & _date,
	double _summary
)
	: m_sender(&_sender)
	, m_reciever(&_reciever)
	, m_ID(_ID)
	, m_purpose(_purpose)
	, m_date(_date)
	, m_summary(_summary)
{}

/*****************************************************************************/
