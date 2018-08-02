// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "lecture.hpp"
#include "topic.hpp"

Lecture::Lecture(std::string _instructorName, std::string _disciplineName)
	:m_disciplineName(_disciplineName), m_instructorName(_instructorName)
{}

void Lecture::addTopic(FullTopicName const & _parentTopic, std::string const & _NewTopic)
{
	m_mainTopic->addTopic(_parentTopic, _NewTopic);
}

std::vector<std::string> Lecture::getNamesTopic(FullTopicName const & _parentTopic)
{
	return m_mainTopic->getNamesTopic(_parentTopic);
}

void Lecture::setTopicSlidesCount(FullTopicName const & _topic, int _slidesCount)
{
	m_mainTopic->setTopicSlidesCount(_topic, _slidesCount);
}

void Lecture::setMainTopicSlidesCount(int _slidesCount)
{
	m_mainTopic->addCountSlides(_slidesCount);
}

int Lecture::getTopicOwnSlidesCount(FullTopicName const & _topic) const
{
	return m_mainTopic->getTopicOwnSlidesCount(_topic);
}

int Lecture::getTopicTotalSlidesCount(FullTopicName const & _topic) const
{
	return m_mainTopic->getTopicTotalSlidesCount(_topic);
}

int Lecture::getCountSlides() const
{
	return m_mainTopic->getCountSlides();
}

bool Lecture::findLecturesByKeyword(std::string const & _keyword) const
{
	return m_mainTopic->findLecturesByKeyword(_keyword);
}

void Lecture::addMainTopic(std::string const & _mainTopicName)
{
	m_mainTopic.reset(new Topic(_mainTopicName));
}

