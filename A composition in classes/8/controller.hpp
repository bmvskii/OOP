// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _CONTROLLER_HPP_
#define _CONTROLLER_HPP_

/*****************************************************************************/

#include "day.hpp"
#include "time.hpp"
#include "genre.hpp"

#include <vector>
#include <string>
#include <unordered_map>
#include <memory>

/*****************************************************************************/

class TVChannel;

class Controller
{

/*-----------------------------------------------------------------*/

public:

/*-----------------------------------------------------------------*/

	Controller ();

	~Controller ();

	Controller ( const Controller & ) = delete;

	Controller & operator = ( const Controller & ) = delete;

/*-----------------------------------------------------------------*/

	void addChannel ( const std::string & _channelName );

/*-----------------------------------------------------------------*/

	void addProgram (
			const std::string & _channelName
		,	Day _day
		,	const std::string & _programName
		,	Time _startTime
		,	Genre _genre
		,	int _rating
	);

	std::vector< std::string > getPrograms (
			const std::string & _channelName
		,	Day _day
	) const;

	std::vector< std::vector< std::string > > getPrograms ( const std::string & _channelName ) const;

/*-----------------------------------------------------------------*/

	std::vector< std::string > getAllSportPrograms () const;

	std::string getChannelWithHighestAverageRating () const;

	std::string getLongestProgram () const;

	// NOTE: First - channel name, second - program name
	std::pair< std::string, std::string > getBestProgramChoiceFor ( Day _day, int _hour ) const;

/*-----------------------------------------------------------------*/

private:

/*-----------------------------------------------------------------*/
	
	std::unordered_map<std::string, std::unique_ptr<TVChannel> > m_channels;

/*-----------------------------------------------------------------*/ 

};

/*****************************************************************************/

#endif // _CONTROLLER_HPP_
