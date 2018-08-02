// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "rgbcolor.hpp"
#include <iomanip>

RGBColor::RGBColor(
	unsigned char _r,
	unsigned char _g,
	unsigned char _b
)
	: m_red(_r)
	, m_green(_g)
	, m_blue(_b)
{}

RGBColor::RGBColor(unsigned int _rgb)
{
	m_red = _rgb >> 16;
	m_green = (_rgb - (_rgb & 0xFF0000)) >> 8;
	m_blue = (_rgb - (_rgb & 0xFF0000)) - (_rgb & 0x00FF00);
}

RGBColor & RGBColor::operator+(RGBColor const & _rgb)
{
	RGBColor _new = *this;
	_new.m_blue += _rgb.m_blue;
	_new.m_red += _rgb.m_red;
	_new.m_green += _rgb.m_green;
	return _new;
}

void RGBColor::operator+=(RGBColor const & _rgb)
{
	m_blue += _rgb.m_blue;
	m_red += _rgb.m_red;
	m_green += _rgb.m_green;
}

std::ostream & operator<<(std::ostream & _s, RGBColor const & _rgb)
{
	_s << "#" << std::setw(6) << std::setfill('0') << std::hex << std::uppercase << _rgb.getPackedRGB();
	return _s;
}

RGBColor RGBColor::getInvertedColor() const
{
	RGBColor _new(255,255,255);

	_new.m_blue -= m_blue;
	_new.m_red -= m_red;
	_new.m_green -= m_green;

	return _new;
}
