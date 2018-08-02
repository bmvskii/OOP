// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "triangle.hpp"

/*****************************************************************************/

Triangle::Triangle(
	double _x1, double _y1,
	double _x2, double _y2,
	double _x3, double _y3
)
	: m_p1(_x1,_y1)
	, m_p2(_x2,_y2)
	, m_p3(_x3,_y3)
{}

/*****************************************************************************/

Triangle::Triangle(
	Point _p1,
	Point _p2,
	Point _p3
)
	: m_p1(_p1)
	, m_p2(_p2)
	, m_p3(_p3)
{}

/*****************************************************************************/
