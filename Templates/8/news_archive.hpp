// (C) 2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _NEWS_ARCHIVE_HPP_
#define _NEWS_ARCHIVE_HPP_

/*****************************************************************************/

#include "datetime.hpp"
#include "messages.hpp"
#include <string>
#include <functional>
#include <map>
#include <algorithm>
#include <vector>
#include <map>

//---------------------------------------------------------------------------

class NewsArchive
{

public:
	//---------------------------------------------------------------------------
	struct Unit
	{
		std::string m_title;
		std::string m_text;

		Unit() = default;
		Unit(std::string _title, std::string _text)
		{
			m_title = _title;
			m_text = _text;
		}

		bool operator < (Unit _new) const
		{
			return m_title < _new.m_title;
		}
	};

	//---------------------------------------------------------------------------
public:
	typedef std::function< void(DateTime, const std::string &, const std::string &) > EntryHandler;

	NewsArchive() = default;

	int getEntriesCount() const;

	bool hasEntry(DateTime const & _date) const;
	
	bool hasEntry(std::string const & _title) const;
	
	std::string const & getEntryTitle(DateTime const & _date) const; 
	
	std::string const & getEntryText(DateTime const & _date) const;
	
	std::string const & getEntryText(std::string const & _title) const;
	
	DateTime const & getEntryDate(std::string const & _title) const; 
	
	void forEachEntry(EntryHandler _function) const; 
	
	void addEntry(DateTime const & _date, std::string const & _title,std::string const & _text); 
	
	void removeEntry(std::string const & _title); 
	
	void modifyEntryTitle(DateTime const & _date,std::string const & _newT);
	
	void modifyEntryText(DateTime  const & _date, std::string const & _newT);
	
	void modifyEntryText(std::string const & _title,std::string const & _newT);
	
	void removeEntry(DateTime const & _date); 
	
	std::vector<std::string> const getEntryTitlesWithTextContains(std::string const & _frag) const;
private:

	std::map<DateTime, Unit> m_news;
	std::map<std::string, DateTime> m_journal;
};

//-----------------------------------------------------------------------
//возвращает количество записей
inline int NewsArchive::getEntriesCount() const
{
	return m_news.size();
}

//-----------------------------------------------------------------------
//проверяет запись по времени
inline bool NewsArchive::hasEntry(DateTime const & _date) const
{
	return m_news.find(_date) != m_news.end();
}

//-----------------------------------------------------------------------
//проверяет запись по заголовку
inline bool NewsArchive::hasEntry(std::string const & _title) const
{
	return m_journal.find(_title) != m_journal.end();
}

//-----------------------------------------------------------------------
//получение заголовка записи по времени
inline std::string const & NewsArchive::getEntryTitle(DateTime const & _date) const
{
	if (!hasEntry(_date))
		throw std::logic_error(Messages::EntryDoesNotExist);

	return m_news.find(_date)->second.m_title;
}

//-----------------------------------------------------------------------
//получение текста по времени
inline std::string const & NewsArchive::getEntryText(DateTime const & _date) const
{
	if (!hasEntry(_date))
		throw std::logic_error(Messages::EntryDoesNotExist);

	return m_news.find(_date)->second.m_text;
}

//-----------------------------------------------------------------------
//получение текста по заголовку
inline std::string const & NewsArchive::getEntryText(std::string const & _title) const
{
	if (!hasEntry(_title))
		throw std::logic_error(Messages::EntryDoesNotExist);

	return m_news.find(m_journal.find(_title)->second)->second.m_text;
}

//-----------------------------------------------------------------------
//получение даты по заголовку
inline DateTime const & NewsArchive::getEntryDate(std::string const & _title) const
{
	if (!hasEntry(_title))
		throw std::logic_error(Messages::EntryDoesNotExist);

	return m_journal.find(_title)->second;
}

//-----------------------------------------------------------------------
//метод для прохода по записям
inline void NewsArchive::forEachEntry(NewsArchive::EntryHandler _f) const
{
	for (auto n : m_news)
		_f(n.first, n.second.m_title, n.second.m_text);
}

//-----------------------------------------------------------------------

#endif // _NEWS_ARCHIVE_HPP_