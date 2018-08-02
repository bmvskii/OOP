// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "topic.hpp"
#include "messages.hpp"

Topic::Topic(std::string _name):name(_name)
{}

void Topic::addTopic(FullTopicName const & _parentTopic, std::string  const & _NewTopic)
{
	if (_parentTopic.size() == 1) {
		if (m_topic.count(_NewTopic) == 1) {
			throw std::logic_error(Messages::SubtopicExists);
		}
		m_topic.insert(std::make_pair(_NewTopic, new Topic(_NewTopic)));
	}
	else {
		auto & topic = m_topic.find(_parentTopic[1]);
		for (int i = 1; i < (int)_parentTopic.size(); i++) {
			if (m_topic.count(_NewTopic) == 1) {
				throw std::logic_error(Messages::SubtopicExists);
			}
			topic = m_topic.find(_parentTopic[i]);
			if (i == (_parentTopic.size() - 1)) {
				topic->second->m_topic.insert(std::make_pair(_NewTopic, new Topic(_NewTopic)));
			}
		}
	}
}

std::vector<std::string> Topic::getNamesTopic(FullTopicName const & _parentTopic)
{
	std::vector<std::string> names;
	if (_parentTopic.size() > 1) {
		auto & pTopic = m_topic.find(_parentTopic[1]);
		for (int i = 1; i < (int)_parentTopic.size(); i++) {
			pTopic = m_topic.find(_parentTopic[i]);
			if (i == (_parentTopic.size() - 1)) {
				for (auto const & topic : pTopic->second->m_topic) {
					names.push_back(topic.first);
				}
			}
		}
	}
	else if (_parentTopic.size() == 1) {
		if (!m_topic.empty()) {
			for (auto const & topic : m_topic) {
				names.push_back(topic.first);
			}
		}
	}
	return names;
}

void Topic::setTopicSlidesCount(FullTopicName const & _topic, int _slidesCount)
{
	if (!m_topic.empty()) {
		auto & pTopic = m_topic.find(_topic[1]);
		for (int i = 1; i < (int)_topic.size(); i++) {
			pTopic = m_topic.find(_topic[i]);
			if (i == (_topic.size() - 1)) {
				pTopic->second->countSlides = _slidesCount;
			}
		}
	}
}

void Topic::addCountSlides(int _slidesCount)
{
	countSlides = _slidesCount;
}

int Topic::getTopicOwnSlidesCount(FullTopicName const & _topic) const
{
	int count = 0;
	if (!m_topic.empty()) {
		if (_topic.size() == 1) {
			count = countSlides;
		}
		else {
			auto & pTopic = m_topic.find(_topic[1]);
			for (int i = 1; i < (int)_topic.size(); i++) {
				pTopic = m_topic.find(_topic[i]);
				if (i == (_topic.size() - 1)) {
					count = pTopic->second->countSlides;
				}
			}
		}
	}
	return count;
}

int Topic::getTopicTotalSlidesCount(FullTopicName const & _topic) const
{
	int count = 0;
	if (!m_topic.empty()) {
		if (_topic.size() == 1) {
			count = countSlides;
			for (auto const & topic : m_topic) {
				count += topic.second->countSlides;
			}
		}
		else {
			auto & pTopic = m_topic.find(_topic[0]);
			for (int i = 0; i < (int)_topic.size(); i++) {
				pTopic = m_topic.find(_topic[i]);
				if (i == (_topic.size() - 1)) {
					count = pTopic->second->countSlides;
					for (auto const & topic : pTopic->second->m_topic) {
						count += topic.second->countSlides;
					}
				}
			}
		}
	}
	return count;
}

bool Topic::findLecturesByKeyword(std::string const & _keyword) const
{
	std::size_t found = name.find(_keyword);
	if (found != std::string::npos) {
		return true;
	}
	if (!m_topic.empty()) {

		for (auto const & topic : m_topic) {
			for (auto const & topicNew : topic.second->m_topic) {
				std::size_t found = topicNew.first.find(_keyword);
				if (found != std::string::npos) {
					return true;
				}
			}
			std::size_t found = topic.first.find(_keyword);
			if (found != std::string::npos) {
				return true;
			}
		}
	}
	return false;
}



