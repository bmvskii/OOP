// (C) 2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "news_archive.hpp"

//-----------------------------------------------------------------------
//добавление записи
void NewsArchive::addEntry(DateTime const & _date,std::string const & _title,std::string const & text)
{
	if (_title.empty())
		throw std::logic_error(Messages::EmptyEntryTitle);
		
	if (text.empty())
		throw std::logic_error(Messages::EmptyEntryText);
		
	if (hasEntry(_date) || hasEntry(_title))
		throw std::logic_error(Messages::DuplicatedEntry);
	
	m_news.insert(std::make_pair(_date, Unit(_title,text)));
	m_journal.insert(std::make_pair(_title,_date));
}

//-----------------------------------------------------------------------
//изменение заголовка по дате
void NewsArchive::modifyEntryTitle(DateTime const & _date,std::string const & _newT)
{
	if (_newT.empty())
		throw std::logic_error(Messages::EmptyEntryTitle);
		
	if (!hasEntry(_date))
		throw std::logic_error(Messages::EntryDoesNotExist);
		
	m_journal.erase(m_news.find(_date)->second.m_title);
	
	m_news.find(_date)->second.m_title = _newT;
	
	m_journal.insert(std::make_pair(_newT, _date));
}

//-----------------------------------------------------------------------
//изменение содержимого записи по дате
void NewsArchive::modifyEntryText(DateTime const & _date, std::string const & _newT)
{
	if (_newT.empty())
		throw std::logic_error(Messages::EmptyEntryText);
	
	if (!hasEntry(_date))
		throw std::logic_error(Messages::EntryDoesNotExist);
		
	m_news.find(_date)->second.m_text = _newT;
}

//-----------------------------------------------------------------------
//изменение содержимого по заголовку
void NewsArchive::modifyEntryText(std::string const & _title,std::string const & _newT)
{
	if (_newT.empty())
		throw std::logic_error(Messages::EmptyEntryText);
	
	if (!hasEntry(_title))
		throw std::logic_error(Messages::EntryDoesNotExist);
		
	m_news.find(m_journal.find(_title)->second)->second.m_text = _newT;
}

//-----------------------------------------------------------------------
//удаление записи по дате
void NewsArchive::removeEntry(DateTime const & _date)
{
	if (!hasEntry(_date))
		throw std::logic_error(Messages::EntryDoesNotExist);
		
	m_journal.erase(m_journal.find(m_news.find(_date)->second.m_title));
	m_news.erase(m_news.find(_date)->first);
}

//-----------------------------------------------------------------------
//удаление записи по заголовку
void NewsArchive::removeEntry(std::string const & _title)
{
	if (!hasEntry(_title))
		throw std::logic_error(Messages::EntryDoesNotExist);
		
	m_news.erase(m_journal.find(_title)->second);
	m_journal.erase(m_journal.find(_title));
}

//-----------------------------------------------------------------------
//возврат массива со строками которые содержат фрагменты
std::vector<std::string> const NewsArchive::getEntryTitlesWithTextContains(std::string const & _frag) const
{
	std::vector<std::string> titlesWithText;

	int k;
	for (auto i = m_news.begin(); i != m_news.end(); ++i)
	{
		k = 0;
		for (int j = 0; j < i->second.m_text.size(); j++)
		{
			if (_frag[k] == i->second.m_text[j]) k++;
			else k = 0;
			if (k == _frag.size())break;
		}

		if (k == _frag.size() || _frag.empty())
			titlesWithText.push_back(i->second.m_title);
	}

	return titlesWithText;
}

//-----------------------------------------------------------------------