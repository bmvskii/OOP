// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _RECTANGLE_HPP_
#define _RECTANGLE_HPP_

/*****************************************************************************/

#include "point.hpp"

/*****************************************************************************/


class Rectangle
{

//*-----------------------------------------------------------------*/

public:

	Rectangle(
		const Point & _point1,
		const Point & _point2
	);

	Rectangle(
		const Point & _point1,
		int _width,
		int _height
	);

	~Rectangle() = default;

	Point getTopLeft() const;

	Point getTopRight() const;

	Point getBottomLeft() const;

	Point getBottomRight() const;

	int getWidth() const;

	int getHeight() const;

	int getPerimeter() const;

	int getArea() const;

	bool operator == (const Rectangle & _r) const;

	bool operator != (const Rectangle & _r) const;

	bool contains(Point _p) const;

	bool contains(Point _p1, Point _p2) const;

	bool intersects(const Rectangle & _r) const;

	bool covers(const Rectangle & _r) const;

private:

	Point m_leftUp, m_rightDown;

	int m_width, m_heigth;

/*------------------------------------------------------------------*/

};

/*****************************************************************************/

inline Point Rectangle::getTopLeft() const 
{
	return m_leftUp;
}

/*****************************************************************************/

inline Point Rectangle::getTopRight() const
{
	return Point(m_rightDown.m_x, m_leftUp.m_y);
}

/*****************************************************************************/

inline Point Rectangle::getBottomLeft() const
{
	return Point(m_leftUp.m_x, m_rightDown.m_y);
}

/*****************************************************************************/

inline Point Rectangle::getBottomRight() const
{
	return m_rightDown;
}

/*****************************************************************************/

inline int Rectangle::getWidth() const
{
	return m_width;
}

/*****************************************************************************/

inline int Rectangle::getHeight() const
{
	return m_heigth;
}

/*****************************************************************************/

inline int Rectangle::getPerimeter() const
{
	return m_heigth * 2 + m_width * 2;
}

/*****************************************************************************/

inline int Rectangle::getArea() const
{
	return m_heigth * m_width;
}

/*****************************************************************************/

inline bool Rectangle::operator == (const Rectangle & _r) const
{
	return m_leftUp == _r.m_leftUp && m_rightDown == _r.m_rightDown;
}

/*****************************************************************************/

inline bool Rectangle::operator != (const Rectangle & _r) const
{
	return !(*this == _r);
}

/*****************************************************************************/

#endif //  _RECTANGLE_HPP_
