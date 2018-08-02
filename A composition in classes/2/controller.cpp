// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "controller.hpp"
#include "messages.hpp"

#include "lecture.hpp"
#include "topic.hpp"

Controller::Controller() = default;

Controller::~Controller() = default;

void Controller::createLecture(std::string const & _instructorName, std::string const & _disciplineName, std::string const & _mainTopicName)
{
	if (_instructorName.empty()) {
		throw std::logic_error(Messages::InstructorNameEmpty);
	}
	if (_disciplineName.empty()) {
		throw std::logic_error(Messages::DisciplineNameEmpty);
	}
	if (_mainTopicName.empty()) {
		throw std::logic_error(Messages::TopicNameEmpty);
	}
	if (m_lecture.count(_mainTopicName) == 1) {
		throw std::logic_error(Messages::MainTopicDuplication);
	}
	std::unique_ptr<Lecture> lecture(new Lecture(_instructorName, _disciplineName));
	lecture->addMainTopic(_mainTopicName);
	m_lecture.insert(std::make_pair(_mainTopicName, std::move(lecture)));

}

std::string const & Controller::getLectureInstructorName(std::string const & _mainTopicName) const
{
	auto const & it = m_lecture.find(_mainTopicName);
	if (it == m_lecture.end()) {
		throw std::logic_error(Messages::MainTopicUnknown);
	}
	return it->second->getNameInstructor();
}

std::string const & Controller::getLectureDisciplineName(std::string const & _mainTopicName) const
{
	auto const & it = m_lecture.find(_mainTopicName);
	if (it == m_lecture.end()) {
		throw std::logic_error(Messages::MainTopicUnknown);
	}
	return it->second->getNameDiscipline();
}

void Controller::addTopic(FullTopicName const & _parentTopic, std::string const & _newTopicName)
{
	if (m_lecture.count(_parentTopic[0]) == 0) {
		throw std::logic_error(Messages::TopicUnknown);
	}
	if (_newTopicName.empty()) {
		throw std::logic_error(Messages::TopicNameEmpty);
	}
	m_lecture.find(_parentTopic[0])->second->addTopic(_parentTopic, _newTopicName);
}

std::vector<std::string> Controller::getSubtopicNames(FullTopicName const & _parentTopic) const
{
	if (m_lecture.count(_parentTopic[0]) == 0) {
		throw std::logic_error(Messages::TopicUnknown);
	}
	std::vector<std::string> names = m_lecture.find(_parentTopic[0])->second->getNamesTopic(_parentTopic);
	std::sort(names.begin(), names.end());
	return names;
}

void Controller::setTopicSlidesCount(FullTopicName const & _topic, int _slidesCount)
{
	if (_topic.size() == 1) {
		m_lecture[_topic[0]]->setMainTopicSlidesCount(_slidesCount);
	}
	else m_lecture[_topic[0]]->setTopicSlidesCount(_topic, _slidesCount);
}

int Controller::getTopicOwnSlidesCount(FullTopicName const & _topic) const
{
	if (m_lecture.count(_topic[0]) == 0) {
		throw std::logic_error(Messages::TopicUnknown);
	}
	return m_lecture.find(_topic[0])->second->getTopicOwnSlidesCount(_topic);
}

int Controller::getTopicTotalSlidesCount(FullTopicName const & _topic) const
{
	if (m_lecture.count(_topic[0]) == 0) {
		throw std::logic_error(Messages::TopicUnknown);
	}
	return m_lecture.find(_topic[0])->second->getTopicTotalSlidesCount(_topic);
}

std::string Controller::findLargestLecture() const
{
	std::pair<std::string, int> largestLecture;
	if (m_lecture.empty()) {
		largestLecture = std::make_pair("", 0);
	}
	else {
		largestLecture = std::make_pair(m_lecture.begin()->first, m_lecture.begin()->second->getCountSlides());
		for (auto const & lecture : m_lecture) {
			if (largestLecture.second < lecture.second->getCountSlides()) {
				largestLecture.first = lecture.first;
				largestLecture.second = lecture.second->getCountSlides();
			}
		}
	}
	return largestLecture.first;
}

std::vector<std::string> Controller::detectEmptyLectures() const
{
	std::vector<std::string> emptyLectures;
	for (auto const & lecture : m_lecture) {
		if (lecture.second->getCountSlides() == 0) {
			emptyLectures.push_back(lecture.first);
		}
	}
	std::sort(emptyLectures.begin(), emptyLectures.end());
	return emptyLectures;
}

std::vector<std::string> Controller::findLecturesByKeyword(std::string const & _keyword) const
{
	if (_keyword.empty()) {
		throw std::logic_error(Messages::KeywordEmpty);
	}
	std::vector<std::string> emptyLectures;
	for (auto const & lecture : m_lecture) {
		if (lecture.second->findLecturesByKeyword(_keyword)) {
			emptyLectures.push_back(lecture.first);
		}
	}
	std::sort(emptyLectures.begin(), emptyLectures.end());
	return emptyLectures;
}

int Controller::getLecturesCountForDiscipline(std::string const & _disciplineName) const
{
	if (_disciplineName.empty()) {
		throw std::logic_error(Messages::DisciplineNameEmpty);
	
	}
	int count = 0;
	for (auto const & lecture : m_lecture) {
		if (lecture.second->isDiscipline(_disciplineName)) {
			count++;
		}
	}
	return count;
}

std::vector<std::string> Controller::getInstructorDisciplines(std::string const & _instructorName) const
{
	if (_instructorName.empty()) {
		throw std::logic_error(Messages::InstructorNameEmpty);
	}
	std::set<std::string> setNames;
	for (auto const & lecture : m_lecture) {
		std::string const & str = lecture.second->getInstructorDiscipline(_instructorName);
		if (str != "") {
			setNames.insert(str);
		}
	}
	std::vector<std::string> vecNames(setNames.begin(), setNames.end());
	return vecNames;
}
