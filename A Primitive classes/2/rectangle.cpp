// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "rectangle.hpp"

#include <stdexcept>

/*****************************************************************************/

Rectangle::Rectangle(
	const Point & _point1,
	const Point & _point2
)
	: m_leftUp(_point1)
	, m_rightDown(_point2)
{
	if (m_leftUp.m_x > m_rightDown.m_x ||
		m_leftUp.m_y > m_rightDown.m_y)
		throw std::logic_error("Invalid rectangle coordinates");

	m_heigth = m_rightDown.m_y - m_leftUp.m_y;
	m_width = m_rightDown.m_x - m_leftUp.m_x;
}

/*****************************************************************************/

Rectangle::Rectangle(
	const Point & _point1,
	int _width,
	int _height
)
	: m_leftUp(_point1)
	, m_heigth(_height)
	, m_width(_width)
{
	if (_height < 1 || _width < 1)
		throw std::logic_error("Invalid rectangle coordinates");

	m_rightDown.m_x = m_leftUp.m_x + m_width;
	m_rightDown.m_y = m_leftUp.m_y + m_heigth;
}

/*****************************************************************************/

bool Rectangle::contains(Point _p) const
{
	if (_p.m_x <= m_rightDown.m_x && _p.m_x >= m_leftUp.m_x &&
		_p.m_y <= m_rightDown.m_y && _p.m_y >= m_leftUp.m_y)
		return true;
	return false;
}

/*****************************************************************************/

bool Rectangle::contains(Point _p1, Point _p2) const
{
	if (_p1.m_x <= m_rightDown.m_x && _p1.m_x >= m_leftUp.m_x &&
		_p1.m_y <= m_rightDown.m_y && _p1.m_y >= m_leftUp.m_y &&
		_p2.m_x <= m_rightDown.m_x && _p2.m_x >= m_leftUp.m_x &&
		_p2.m_y <= m_rightDown.m_y && _p2.m_y >= m_leftUp.m_y)
		return true;
	return false;
}

/*****************************************************************************/

bool Rectangle::intersects(const Rectangle & _r) const
{
	if (contains(_r.getTopLeft()) || contains(_r.getTopRight()) ||
		contains(_r.getBottomLeft()) || contains(_r.getBottomRight()))
		return true;
	return false;
}

/*****************************************************************************/

bool Rectangle::covers(const Rectangle & _r) const
{
	if (getTopLeft().m_x < _r.getTopLeft().m_x && getTopLeft().m_y < _r.getTopLeft().m_y &&
		getTopRight().m_x > _r.getTopRight().m_x && getTopRight().m_y < _r.getTopRight().m_y &&
		getBottomLeft().m_x < _r.getBottomLeft().m_x && getBottomLeft().m_y > _r.getBottomLeft().m_y &&
		getBottomRight().m_x > _r.getBottomRight().m_x && getBottomRight().m_y > _r.getBottomRight().m_y)
		return true;
	return false;
}

/*****************************************************************************/