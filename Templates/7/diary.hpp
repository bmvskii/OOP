// (C) 2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _DIARY_HPP_
#define _DIARY_HPP_

/*****************************************************************************/

#include "date.hpp"
#include "time.hpp"

#include <string>
#include <map>
#include <vector>

/*****************************************************************************/

class Diary
{

/*-----------------------------------------------------------------*/

public:

/*-----------------------------------------------------------------*/

	typedef std::map< Time, std::string > DayEntries;

	typedef std::map< Date, DayEntries > Entries;

	typedef Entries::const_iterator Iterator;

/*-----------------------------------------------------------------*/

public:

/*-----------------------------------------------------------------*/

	Diary(std::string const & _ownerName);

	~Diary() = default;

	Diary(Diary const & _d);

	Diary & operator = (Diary const & _d);

	Diary(Diary && _d) = delete;

	Diary & operator = (Diary && _d) = delete;

	std::string const & getOwnerName() const;

	int getDaysCount() const;

	int getEntriesCount(Date const & _date) const;

	bool hasEntries(Date const & _date) const;

	bool hasEntries(Time const & _time) const;

	bool hasEntry(Date const & _date, Time const & _time) const;

	void addEntry(Date const & _date, Time const & _time, std::string const & _entryName);

	void modifyEntry(Date const & _date, Time const & _time, std::string const & _newEntryName);

	std::string const & getEntry(Date const & _date, Time const & _time) const;

	void removeEntries(Date const & _date);

	void removeEntries(Time const & _time);

	void removeEntry(Date const & _date, Time const & _time);

	Iterator begin() const;

	Iterator end() const;

	friend std::ostream & operator << (std::ostream & _o, const Diary & _diary);
	
	/*-----------------------------------------------------------------*/

private:

/*-----------------------------------------------------------------*/

	std::string m_ownerName;

	Entries m_entries;

/*-----------------------------------------------------------------*/

};

/*****************************************************************************/

inline
std::string const &  Diary::getOwnerName() const
{
	return m_ownerName;
}

/*****************************************************************************/

inline
int Diary::getDaysCount() const
{
	return m_entries.size();
}

/*****************************************************************************/

inline Diary::Iterator Diary::begin() const
{
	return m_entries.begin();
}

/*****************************************************************************/

inline Diary::Iterator Diary::end() const
{
	return m_entries.end();
}

/*****************************************************************************/

#endif // _DIARY_HPP_
