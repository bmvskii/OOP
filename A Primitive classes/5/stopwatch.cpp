// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "stopwatch.hpp"

#include <stdexcept>

/*****************************************************************************/

Stopwatch::Stopwatch(clock_t _begin)
{
	m_begin = 0;
	m_now = _begin;
	m_paused = true;
}

/*****************************************************************************/

void Stopwatch::pause()
{
	if (m_paused)
	{
		throw std::logic_error("Stopwatch is paused already");
	}
	else
	{
		m_paused = true;
	}

	clock_t finish = clock();
	m_now = finish;
}

/*****************************************************************************/

void Stopwatch::reset()
{
	m_now = 0;
	m_begin = 0;
	m_paused = true;
}

/*****************************************************************************/

void Stopwatch::resume()
{
	if (!m_paused)
	{
		throw std::logic_error("Stopwatch is not paused");
	}
	else
	{
		m_paused = false;
	}
		
	if (m_now == 0)
	{
		m_begin = clock();
	}
}

/*****************************************************************************/

bool Stopwatch::isPaused() const
{
	return m_paused;
}

/*****************************************************************************/

clock_t Stopwatch::getElapsed() const
{
	clock_t finish = clock();

	if (m_now && !m_begin)
	{
		return m_now;
	}
	if (m_now && !m_paused)
	{
		return finish - m_now;
	}
	if (m_now) 
	{
		return m_now - m_begin;
	}
	if (m_paused && !m_now)
	{
		return 0;
	}	
	return finish - m_begin;
}

/*****************************************************************************/

Stopwatch Stopwatch::operator +(int  _s)
{
	return Stopwatch(_s + m_now);
}

/*****************************************************************************/

void Stopwatch::operator +=(int  _s)
{
	m_now += _s;
}

/*****************************************************************************/

Stopwatch Stopwatch::operator -(int _s)
{
	return Stopwatch(m_now - _s);
}

/*****************************************************************************/

void Stopwatch::operator -=(int _s)
{
	m_now -= _s;
}

/*****************************************************************************/

int Stopwatch::getElapsedMinutes() const
{
	clock_t t = getElapsed();
	return (t - (getElapsedHours() * H)) / M;
}

/*****************************************************************************/

int Stopwatch::getElapsedSeconds() const
{
	clock_t t = getElapsed();

	return (t - (getElapsedHours() * H) - (getElapsedMinutes() * M)) / S;
}

/*****************************************************************************/

int Stopwatch::getElapsedHours() const
{
	clock_t t = getElapsed();
	return t / H;
}

/*****************************************************************************/

void Stopwatch::display(std::ostream & _s)
{
	_s << getElapsedHours() << ":" << getElapsedMinutes() << ":" << getElapsedSeconds();
}

/*****************************************************************************/