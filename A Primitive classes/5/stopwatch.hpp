// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _STOPWATCH_HPP_
#define _STOPWATCH_HPP_

/*****************************************************************************/

#include <ctime>
#include <iostream>
#include <time.h>

/*****************************************************************************/


class Stopwatch
{

/*-----------------------------------------------------------------*/
public:
	Stopwatch(clock_t _begin = 0);
	~Stopwatch() = default;
	void pause();
	void reset();
	void resume();
	bool isPaused() const;
	void display(std::ostream & _s);
	clock_t getElapsed() const;
	Stopwatch operator +(int _s);
	void operator +=(int _s);
	Stopwatch operator -(int _s);
	void operator -=(int  _s);
	int getElapsedMinutes() const;
	int getElapsedSeconds() const;
	int getElapsedHours() const;

private:

	const int H = 3600000, M = 60000, S = 1000;

	clock_t m_begin;
	clock_t m_now;

	bool m_paused;
	
/*------------------------------------------------------------------*/

};

/*****************************************************************************/

#endif //  _STOPWATCH_HPP_
