// (C) 2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "diary.hpp"
#include "messages.hpp"


Diary::Diary(Diary const & _d) 
{
	if (this == &_d)
		return;

	m_ownerName = _d.m_ownerName;
	m_entries = _d.m_entries;
}

Diary & Diary::operator = (Diary const & _d)
{
	if (this == &_d)
		return *this;

	m_entries = _d.m_entries;
	m_ownerName = _d.m_ownerName;

	return *this;
}

/*****************************************************************************/

int Diary::getEntriesCount(Date const & _date) const
{
	return m_entries.find(_date) == m_entries.end() ? 0 : m_entries.find(_date)->second.size();
}

/*****************************************************************************/

bool Diary::hasEntries(Date const & _date) const
{
	return !m_entries.find(_date)->second.empty();
}

/*****************************************************************************/

bool Diary::hasEntries(Time const & _time) const
{
	for (auto e : m_entries)
		if (e.second.find(_time) != e.second.end())
			return true;
	return false;
}

/*****************************************************************************/

bool Diary::hasEntry(Date const & _date, Time const & _time) const
{
	return m_entries.find(_date)->second.find(_time) != m_entries.find(_date)->second.end();
}

/*****************************************************************************/

void Diary::addEntry(Date const & _date, Time const & _time, std::string const & _entryName)
{
	if (_entryName.empty())
		throw std::logic_error(Messages::EmptyEntryText);

	std::map<Time, std::string> time;
	time.insert(std::make_pair(_time, _entryName));

	if (m_entries.find(_date) != m_entries.end())
	{
		std::vector<Time> temp;
		auto cont = m_entries.find(_date)->second;
		for (auto e : cont)
			temp.push_back(e.first);

		if (temp.back() >= _time)
			throw std::logic_error(Messages::InvalidEntryTime);

		m_entries.find(_date)->second.insert(std::make_pair(_time, _entryName));
	}
	
	m_entries.insert(std::make_pair(_date, time));
}

/*****************************************************************************/

void Diary::modifyEntry(Date const & _date, Time const & _time, std::string const & _newEntryName)
{
	if (_newEntryName.empty())
		throw std::logic_error(Messages::EmptyEntryText);

	if (m_entries.find(_date) == m_entries.end())
		throw std::logic_error(Messages::EntryDoesNotExist);
	else if (m_entries.find(_date)->second.find(_time) == m_entries.find(_date)->second.end())
		throw std::logic_error(Messages::EntryDoesNotExist);

	m_entries.find(_date)->second.find(_time)->second = _newEntryName;
}

/*****************************************************************************/

std::string const & Diary::getEntry(Date const & _date, Time const & _time) const
{
	if (m_entries.find(_date) == m_entries.end())
		throw std::logic_error(Messages::EntryDoesNotExist);
	else if (m_entries.find(_date)->second.find(_time) == m_entries.find(_date)->second.end())
		throw std::logic_error(Messages::EntryDoesNotExist);

	return m_entries.find(_date)->second.find(_time)->second;
}

/*****************************************************************************/

void Diary::removeEntries(Date const & _date)
{
	if (m_entries.find(_date) == m_entries.end())
		throw std::logic_error(Messages::EntryDoesNotExist);

	m_entries.erase(_date);
}

/*****************************************************************************/

void Diary::removeEntries(Time const & _time)
{
	auto copy = m_entries;
	for (auto e : copy)
		if (e.second.find(_time) != e.second.end())
			m_entries.find(e.first)->second.erase(_time);
}

/*****************************************************************************/

void Diary::removeEntry(Date const & _date, Time const & _time)
{
	if (m_entries.find(_date) == m_entries.end())
		throw std::logic_error(Messages::EntryDoesNotExist);
	else if (m_entries.find(_date)->second.find(_time) == m_entries.find(_date)->second.end())
		throw std::logic_error(Messages::EntryDoesNotExist);

	m_entries.find(_date)->second.erase(_time);
}

/*****************************************************************************/

std::ostream & operator<<(std::ostream & _o, const Diary & _diary)
{
	_o << "Owner: " << _diary.getOwnerName() << std::endl;
	if (_diary.m_entries.empty())
		_o << "No entries" << std::endl;
	else
		for (auto e : _diary.m_entries)
		{
			_o << "Date: " << e.first << std::endl;
			for (auto en : e.second)
				_o << "    " << en.first << ": " << en.second << std::endl;
		}
	return _o;
}

/*****************************************************************************/

Diary::Diary(std::string const & _ownerName)
	: m_ownerName(_ownerName)
{
	if (m_ownerName.empty())
		throw std::logic_error(Messages::EmptyOwnerName);
}

/*****************************************************************************/