// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _LECTURE_HPP_
#define _LECTURE_HPP_

#include <string>
#include <vector>
#include <memory>

/*****************************************************************************/

class Topic;

typedef std::vector< std::string > FullTopicName;

/*****************************************************************************/


class Lecture
{

/*-----------------------------------------------------------------*/

public:

/*-----------------------------------------------------------------*/

	Lecture(std::string _instructorName, std::string _disciplineName);
	std::string const & getNameInstructor()const;
	std::string const & getNameDiscipline()const;
	void addMainTopic(std::string const & _mainTopicName);
	void addTopic(FullTopicName  const & _parentTopic, std::string  const & _NewTopic);
	std::vector<std::string> getNamesTopic(FullTopicName const & _parentTopic);
	void setTopicSlidesCount(FullTopicName const & _topic, int _slidesCount);
	void setMainTopicSlidesCount(int _slidesCount);
	int getTopicOwnSlidesCount(FullTopicName const & _topic) const;
	int getTopicTotalSlidesCount(FullTopicName const & _topic) const;
	int getCountSlides()const;
	bool findLecturesByKeyword(std::string const & _keyword) const;
	bool isDiscipline(std::string const & _disciplineName) const;
	std::string getInstructorDiscipline(std::string const & _instructorName) const;

/*-----------------------------------------------------------------*/

private:

/*-----------------------------------------------------------------*/

	std::string m_instructorName;
	std::string m_disciplineName;
	std::unique_ptr<Topic> m_mainTopic;

/*-----------------------------------------------------------------*/

};

inline std::string const & Lecture::getNameInstructor() const
{
	return m_instructorName;
}

inline std::string const & Lecture::getNameDiscipline() const
{
	return m_disciplineName;
}

inline bool Lecture::isDiscipline(std::string const & _disciplineName) const
{
	return m_disciplineName == _disciplineName;
}

inline std::string Lecture::getInstructorDiscipline(std::string const & _instructorName) const
{
	return (m_instructorName == _instructorName) ? m_disciplineName : "";
}

/*****************************************************************************/

#endif //  _LECTURE_HPP_