// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "controller.hpp"
#include "messages.hpp"
#include "book.hpp"
#include "derived_book.hpp"
#include "original_book.hpp"
#include "translated_book.hpp"
#include "revised_book.hpp"
#include <algorithm>

typedef Controller::BookKey BookKey;

/*****************************************************************************/

Controller::Controller() = default;

/*****************************************************************************/

Controller::~Controller() = default;

/*****************************************************************************/

void Controller::addOriginalBook(
	BookKey const & _key,
	std::initializer_list<std::string> _authors,
	const char * _language,
	int _publicationYear
)
{
	if (_key.m_edition < 1)
		throw std::logic_error(Messages::NonPositiveEdition);

	if (_key.m_title.empty())
		throw std::logic_error(Messages::EmptyTitle);

	if (_authors.size() == 0)
		throw std::logic_error(Messages::EmptyAuthorsList);

	std::vector<std::string> temp(_authors);
	int nCount;
		for (int i = 0; i < temp.size() - 1; i++)
		{
			nCount = 0;
			for (int j = i + 1; j < temp.size(); j++)
				if (temp[i] == temp[j])
					nCount++;
				
			if (nCount > 0)
				throw std::logic_error(Messages::DuplicateAuthor);
		}

	std::string s(_language);
	if (s.size() > 2 || s.size() < 2)
		throw std::logic_error(Messages::LanguageCodeNot2Chars);

	auto it = m_books.find(_key);
	if (it != m_books.end())
		throw std::logic_error(Messages::NonUniqueTitle);

	m_books.insert(std::make_pair(_key, std::make_unique<OriginalBook>(
		_key.m_title,
		_publicationYear,
		_language,
		_key.m_edition,
		_authors
		)));

	m_booksLog.insert(std::make_pair(_key.m_title, _key));
	m_orderLog.insert(std::make_pair(_key, nOrderCount++));
}

/*****************************************************************************/

void Controller::addTranslation(
	std::string const & _translatedTitle,
	BookKey const & _originalKey,
	const char * _translatedLanguage, 
	int _translationYear
)
{
	if (_translatedTitle.empty())
		throw std::logic_error(Messages::EmptyTitle);

	BookKey translatedKey(_translatedTitle, _originalKey.m_edition);
	auto it1 = m_books.find(translatedKey);
	if (it1 != m_books.end())
		throw std::logic_error(Messages::NonUniqueTitle);
	
	std::string s(_translatedLanguage);
	if (s.size() > 2 || s.size() < 2)
		throw std::logic_error(Messages::LanguageCodeNot2Chars);

	auto it2 = m_books.find(_originalKey);
	if (it2 == m_books.end())
		throw std::logic_error(Messages::BookNotFound);

	if (it2->second->getLanguageInfo() == _translatedLanguage)
		throw std::logic_error(Messages::TranslatedToSameLanguage);

	if (it2->second->getPublishingYear() > _translationYear && !hasDerived(_originalKey))
		throw std::logic_error(Messages::DerivedBeforeOriginal);

	m_books.insert(std::make_pair(translatedKey, std::make_unique<TranslatedBook>(
		_translatedTitle,
		_translationYear,
		_translatedLanguage,
		*it2->second.get()
	)));

	m_booksLog.insert(std::make_pair(_translatedTitle, translatedKey));
	m_orderLog.insert(std::make_pair(translatedKey, nOrderCount++));
}

/*****************************************************************************/

void Controller::addRevised(
	BookKey const & _revisedKey,
	BookKey const & _originalKey,
	int _revisionYear
)
{
	if (_revisedKey.m_title.empty())
		throw std::logic_error(Messages::EmptyTitle);

	auto it1 = m_books.find(_revisedKey);
	if (it1 != m_books.end())
		throw std::logic_error(Messages::NonUniqueTitle);

	auto it2 = m_books.find(_originalKey);
	if (it2 == m_books.end())
		throw std::logic_error(Messages::BookNotFound);

	if (it2->second->getEditionInfo() > _revisedKey.m_edition)
		throw std::logic_error(Messages::RevisedEditionLessEqu);

	if (it2->second->getPublishingYear() > _revisionYear && !!hasDerived(_originalKey))
		throw std::logic_error(Messages::DerivedBeforeOriginal);

	m_books.insert(std::make_pair(_revisedKey, std::make_unique<RevisedBook>(
		_revisedKey.m_title,
		_revisionYear,
		_revisedKey.m_edition,
		*it2->second.get()
		)));


	m_booksLog.insert(std::make_pair(_revisedKey.m_title, _revisedKey));
	m_orderLog.insert(std::make_pair(_revisedKey, nOrderCount++));
}

/*****************************************************************************/

const char * Controller::getBookLanguage(BookKey const & _key) const
{
	auto it = m_books.find(_key);
	if (it == m_books.end())
		throw std::logic_error(Messages::BookNotFound);

	return it->second->getLanguageInfo().c_str();
}

/*****************************************************************************/

int Controller::getBookPublicationYear(BookKey const & _key) const
{
	auto it = m_books.find(_key);
	if (it == m_books.end())
		throw std::logic_error(Messages::BookNotFound);
	return it->second->getPublishingYear();
}

/*****************************************************************************/

std::vector<std::string> Controller::getBookAuthors(BookKey const & _key) const
{
	auto it = m_books.find(_key);
	if (it == m_books.end())
		throw std::logic_error(Messages::BookNotFound);
	return it->second->getAuthorsInfo();
}

/*****************************************************************************/

std::vector<BookKey> Controller::findBookEditions(std::string const & _title) const
{
	auto it = m_booksLog.find(_title);
	if (it == m_booksLog.end())
		throw std::logic_error(Messages::BookNotFound);

	std::vector<BookKey> result;
	std::map<int, BookKey> temp;

	for (auto const & book : m_books)
		if (book.first.m_title == _title)
			if (it->second.m_edition != book.second->getEditionInfo() || it->second == book.first)
				temp.insert(std::make_pair(m_orderLog.find(book.first)->second, book.first));
 
	for (auto const & p : temp)
		result.push_back(p.second);

	return result;
}

/*****************************************************************************/

int Controller::getBookLatestEdition(std::string const & _title)
{
	auto it = m_booksLog.find(_title);
	if (it == m_booksLog.end())
		throw std::logic_error(Messages::BookNotFound);

	int latestEdition = 0;
	for (auto const & book : m_books)
		if (book.first.m_title == _title)
			if (book.first.m_edition > latestEdition)
				latestEdition = book.first.m_edition;
	return latestEdition;
}

/*****************************************************************************/

std::vector<BookKey> Controller::findBookTranslations(BookKey const & _key) const
{

	auto it = m_books.find(_key);
	if (it == m_books.end())
		throw std::logic_error(Messages::BookNotFound);

	std::vector<BookKey> result;
	std::map<int, BookKey> temp;

	for (auto const & book : m_books)
		if (book.first.m_edition == it->first.m_edition)
		{
			auto b = dynamic_cast<TranslatedBook *>(book.second.get());
			if (b)
				if (b->getBaseBook()->getTitle() == it->second->getTitle())
					if (b->getLanguageInfo() != it->second->getLanguageInfo())
						temp.insert(std::make_pair(m_orderLog.find(book.first)->second, book.first));
		}

	for (auto const & p : temp)
		result.push_back(p.second);

	return result;
}

/*****************************************************************************/

BookKey Controller::getOriginalBook(BookKey const & _derivedBook) const
{
	auto it = m_books.find(_derivedBook);
	if (it == m_books.end())
		throw std::logic_error(Messages::BookNotFound);

	auto book = dynamic_cast<DerivedBook *>(it->second.get());
	if (!book)
		throw std::logic_error(Messages::NotADerivedBook);
	
	return BookKey(book->getBaseBook()->getTitle(), book->getBaseBook()->getEditionInfo());
}

/*****************************************************************************/

bool Controller::hasDerived(BookKey const & _key) const
{
	auto it = m_books.find(_key);
	for (auto const & book : m_books)
		if (it->first.m_edition == book.first.m_edition)
			if (it->second->getLanguageInfo() != book.second->getLanguageInfo())
				return true;
		else if (it->first.m_title == book.first.m_title)
			if (it->second->getEditionInfo() != book.second->getEditionInfo())
				return true;
	return false;
}

/*****************************************************************************/