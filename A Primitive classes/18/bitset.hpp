// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _BITSET_HPP_
#define _BITSET_HPP_

/*****************************************************************************/

#include <iostream>
#include <string>

/*****************************************************************************/


class Bitset
{

/*-----------------------------------------------------------------*/

public:

/*------------------------------------------------------------------*/

	Bitset(int _size = 32);

	Bitset(const char * _str);

	Bitset & operator =(Bitset const & _b);

	Bitset(Bitset const & _b);

	Bitset & operator =(Bitset && _b);

	Bitset(Bitset && _b);

	friend std::ostream & operator << (std::ostream & _s, Bitset const & _set);

	bool isSet(int _index) const;

	void set(int _index);

	void clear(int _index);

	void clearAll();

	Bitset & operator ~ ();

	bool operator !() const;

	bool operator ()();

	int getSize() const;

	Bitset operator & (Bitset & _b) const;

	Bitset operator | (Bitset & _b) const;

	Bitset & operator &= (Bitset & _b);
	
	Bitset & operator |= (Bitset & _b);

/*------------------------------------------------------------------*/

private:
	
	int getArraySize() const;

	unsigned int * m_bitset;
	int m_bitsetSize;

};

inline int Bitset::getSize() const
{
	return m_bitsetSize;
}



/*****************************************************************************/

#endif //  _BITSET_HPP_
