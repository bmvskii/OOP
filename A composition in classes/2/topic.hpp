// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _TOPIC_HPP_
#define _TOPIC_HPP_

#include <string>
#include <vector>
#include <map>
#include <memory>

/*****************************************************************************/

typedef std::vector< std::string > FullTopicName;

class Topic
{

/*-----------------------------------------------------------------*/

public:

/*-----------------------------------------------------------------*/

	Topic(std::string _name);
	void addTopic(FullTopicName  const & _parentTopic, std::string  const & _NewTopic);
	int getCountSlides()const;
	std::vector<std::string> getNamesTopic(FullTopicName const & _parentTopic);
	void setTopicSlidesCount(FullTopicName const & _topic, int _slidesCount);
	void addCountSlides(int _slidesCount);
	int getTopicOwnSlidesCount(FullTopicName const & _topic) const;
	int getTopicTotalSlidesCount(FullTopicName const & _topic) const;
	bool findLecturesByKeyword(std::string const & _keyword) const;

/*-----------------------------------------------------------------*/

private:

/*-----------------------------------------------------------------*/

	std::string name;
	int countSlides;
	std::map<std::string, std::unique_ptr<Topic>> m_topic;

/*-----------------------------------------------------------------*/

};

inline int Topic::getCountSlides() const
{
	return countSlides;
}

/*****************************************************************************/

#endif //  _TOPIC_HPP_
