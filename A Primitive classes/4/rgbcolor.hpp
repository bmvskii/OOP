// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _RGBCOLOR_HPP_
#define _RGBCOLOR_HPP_

/*****************************************************************************/

#include <iostream>

/*****************************************************************************/

class RGBColor
{

/*-----------------------------------------------------------------*/
public:
	
	RGBColor(
		unsigned char _r,
		unsigned char _g,
		unsigned char _b
	);

	RGBColor(unsigned int _rgb);

	unsigned char getGreen() const;

	unsigned char getBlue() const;

	unsigned char getRed() const;

	unsigned int getPackedRGB() const;

	bool operator == (RGBColor const & _rgb) const;

	bool operator != (RGBColor const & _rgb) const;

	RGBColor getInvertedColor() const;

	friend std::ostream & operator << (std::ostream & _s, RGBColor const & _rgb);

	double getBlackKey() const;

	double getCyanColor() const;

	double getMagentaColor() const;

	double getYellowColor() const;

	RGBColor & operator + (RGBColor const & _rgb);

	void operator += (RGBColor const & _rgb);

private:

	unsigned char m_red, m_green, m_blue;

/*------------------------------------------------------------------*/

};

inline
unsigned char RGBColor::getGreen() const
{
	return m_green;
}

inline
unsigned char RGBColor::getBlue() const
{
	return m_blue;
}

inline
unsigned char RGBColor::getRed() const
{
	return m_red;
}

inline
unsigned int RGBColor::getPackedRGB() const
{
	return ((m_red << 16) & 0xFF0000) + ((m_green << 8) & 0x00FF00) + (m_blue & 0x0000FF);
}

inline
double RGBColor::getBlackKey() const
{
	double r = m_red / 255.0,
	   	   g = m_green / 255.0,
		   b = m_blue / 255.0;

	double max = std::fmax(r, g);
	
	max = std::fmax(max, b);
	return 1 - max;
}

inline
double RGBColor::getCyanColor() const
{
	if (getRed() == 0 && getBlue() == 0 && getGreen() == 0)
		return 0;
	return (1 - m_red / 255.0 - getBlackKey()) / (1 - getBlackKey());
}

inline
double RGBColor::getMagentaColor() const
{
	if (getRed() == 0 && getBlue() == 0 && getGreen() == 0)
		return 0;
	return (1 - m_green / 255.0 - getBlackKey()) / (1 - getBlackKey());
}

inline
double RGBColor::getYellowColor() const
{
	if (getRed() == 0 && getBlue() == 0 && getGreen() == 0)
		return 0;
	return (1 - m_blue / 255.0 - getBlackKey()) / (1 - getBlackKey());
}

inline
bool RGBColor::operator == (RGBColor const & _rgb) const
{
	return m_blue == _rgb.m_blue && m_green == _rgb.m_green && m_red == _rgb.m_red;
}

inline
bool RGBColor::operator != (RGBColor const & _rgb) const
{
	return !(*this == _rgb);
}

/*****************************************************************************/

#endif //  _RGBCOLOR_HPP_
