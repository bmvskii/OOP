// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _TRIANGLE_HPP_
#define _TRIANGLE_HPP_

/*****************************************************************************/

#include "point.hpp"

/*****************************************************************************/


class Triangle
{

/*-----------------------------------------------------------------*/
public:

	Triangle(
		double _x1, double _y1,
		double _x2, double _y2,
		double _x3, double _y3
	);

	Triangle(
		Point _p1,
		Point _p2,
		Point _p3
	);

	~Triangle() = default;

	Point getPoint1() const;
	
	Point getPoint2() const;
		
	Point getPoint3() const;

	double getSide12Length() const;

	double getSide23Length() const;
	
	double getSide13Length() const;

	double getPerimeter() const;

	double getArea() const;

	bool operator == (const Triangle & _tr) const;

	bool operator != (const Triangle & _tr) const;

	double getAngle1() const; 
	
	double getAngle2() const;
	
	double getAngle3() const;

	bool isRectangular() const;

	bool isIsosceles() const;

	bool isEquilateral() const;

private:

	Point m_p1, m_p2, m_p3;

/*------------------------------------------------------------------*/

};

/*****************************************************************************/

inline Point Triangle::getPoint1() const
{
	return m_p1;
}

/*****************************************************************************/

inline Point Triangle::getPoint2() const
{
	return m_p2;
}

/*****************************************************************************/

inline Point Triangle::getPoint3() const
{
	return m_p3;
}

/*****************************************************************************/

inline double Triangle::getSide12Length() const
{
	return m_p1.distanceTo(m_p2);
}

/*****************************************************************************/

inline double Triangle::getSide23Length() const
{
	return m_p2.distanceTo(m_p3);
}

/*****************************************************************************/

inline double Triangle::getSide13Length() const
{
	return m_p1.distanceTo(m_p3);
}

/*****************************************************************************/

inline double Triangle::getPerimeter() const
{
	return getSide12Length() + getSide13Length() + getSide23Length();
}

/*****************************************************************************/

inline double Triangle::getArea() const
{
	double p = getPerimeter() / 2;
	return std::sqrt(p*(p - getSide12Length())*(p - getSide13Length())*(p - getSide23Length()));
}

/*****************************************************************************/

inline bool Triangle::operator == (const Triangle & _tr) const
{
	return m_p1.m_x == _tr.m_p1.m_x && m_p1.m_y == _tr.m_p1.m_y
		&& m_p2.m_x == _tr.m_p2.m_x && m_p2.m_y == _tr.m_p2.m_y
		&& m_p3.m_x == _tr.m_p3.m_x && m_p3.m_y == _tr.m_p3.m_y;
}

/*****************************************************************************/

inline bool Triangle::operator != (const Triangle & _tr) const
{
	return !(*this == _tr);
}

/*****************************************************************************/

inline double Triangle::getAngle2() const
{
	double a = getSide12Length()
		,  b = getSide23Length()
		,  c = getSide13Length();
	return std::acos((std::pow(a,2) + std::pow(b,2) - std::pow(c,2))/(2 * a * b));
}

/*****************************************************************************/

inline double Triangle::getAngle1() const
{
	double a = getSide12Length()
		, b = getSide23Length()
		, c = getSide13Length();
	return std::acos((std::pow(a, 2) + std::pow(c, 2) - std::pow(b, 2)) / (2 * a * c));
}

/*****************************************************************************/

inline double Triangle::getAngle3() const
{
	double a = getSide12Length()
		, b = getSide23Length()
		, c = getSide13Length();
	return std::acos((std::pow(c, 2) + std::pow(b, 2) - std::pow(a, 2)) / (2 * b * c));
}

/*****************************************************************************/

inline bool Triangle::isRectangular() const
{
	return equalDoubles( getAngle1(), 1.570796)
		|| equalDoubles( getAngle2(), 1.570796)
		|| equalDoubles( getAngle3(), 1.570796);
}

/*****************************************************************************/

inline bool Triangle::isIsosceles() const
{
	return equalDoubles(getSide12Length() , getSide13Length())
		|| equalDoubles(getSide12Length() , getSide23Length())
		|| equalDoubles(getSide13Length() , getSide23Length());
}

/*****************************************************************************/

inline bool Triangle::isEquilateral() const
{
	return equalDoubles(getSide12Length(), getSide13Length())
		&& equalDoubles(getSide12Length(), getSide23Length())
		&& equalDoubles(getSide13Length(), getSide23Length());
}

/*****************************************************************************/

#endif //  _TRIANGLE_HPP_
