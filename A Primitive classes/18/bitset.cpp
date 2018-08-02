// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "bitset.hpp"

#include <stdexcept>

/*****************************************************************************/

bool Bitset::isSet(int _index) const
{
	if (_index < 0 || _index >= m_bitsetSize)
		throw std::logic_error("Index out of range");

	return m_bitset[_index / 32] & (1 << ((_index % 32) - 1));
}

/*****************************************************************************/

void Bitset::set(int _index)
{
	if (_index < 0 || _index >= m_bitsetSize)
		throw std::logic_error("Index out of range");

	m_bitset[_index / 32] |= (1 << (_index % 32) - 1);
}

/*****************************************************************************/

void Bitset::clear(int _index)
{
	if (_index < 0 || _index >= m_bitsetSize)
		throw std::logic_error("Index out of range");

	m_bitset[_index / 32] &= ~(1 << (_index % 32) - 1);
}

/*****************************************************************************/

void Bitset::clearAll()
{
	memset(m_bitset, 0, sizeof(unsigned int)* getArraySize());
}

/*****************************************************************************/

Bitset & Bitset::operator~()
{
	for (int i = 0; i < getArraySize(); i++)
		m_bitset[i] = ~m_bitset[i];

	return * this;
}

/*****************************************************************************/

bool Bitset::operator!() const
{
	for (int i = 0; i < m_bitsetSize; i++)
		if (m_bitset[i / 32] & (1 << i)) return false;

	return true;
}

/*****************************************************************************/

bool Bitset::operator()()
{

	return !!*this;
}

/*****************************************************************************/

int Bitset::getArraySize() const
{
	int size = 1;
	while (!((size++ * 32) / m_bitsetSize));

	return size;
}

/*****************************************************************************/

Bitset::Bitset(int _size)
{
	if (_size < 1)
		throw std::logic_error("Non-positive bitset size");

	m_bitsetSize = _size;
	m_bitset = new unsigned int[getArraySize()];
	clearAll();
}

/*****************************************************************************/

Bitset::Bitset(const char * _str)
	: m_bitsetSize(strlen(_str))
{
	if (m_bitsetSize < 1)
		throw std::logic_error("Non-positive bitset size");

	m_bitset = new unsigned int[getArraySize()];
	clearAll();

	for (int i = m_bitsetSize - 1; i >= 0; i--)
	{
		if (_str[i] == '0') continue;
		else if (_str[i] == '1')
			m_bitset[i / 32] |= (1 << i - 1);
		else
			throw std::logic_error("Unexpected bitset symbol");
	}
}

Bitset & Bitset::operator=(Bitset const & _b)
{
	if (&_b == this) return * this;

	m_bitsetSize = _b.m_bitsetSize;
	m_bitset = new unsigned int[getArraySize()];
	memcpy(m_bitset, _b.m_bitset, sizeof(unsigned int)* getArraySize());

	return * this;
}

Bitset Bitset::operator & (Bitset & _b) const
{

	Bitset _new(*this);

	for (int i = 0; i < getArraySize(); i++)
		_new.m_bitset[i] = m_bitset[i] & _b.m_bitset[i];

	return _new;
}

Bitset Bitset::operator | (Bitset & _b) const
{
	Bitset _new(*this);

	for (int i = 0; i < getArraySize(); i++)
		_new.m_bitset[i] = m_bitset[i] | _b.m_bitset[i];

	return _new;
}

Bitset & Bitset::operator &= ( Bitset & _b)
{
	for (int i = 0; i < getArraySize(); i++)
		m_bitset[i] &= _b.m_bitset[i];

	return *this;
}

Bitset & Bitset::operator |= (Bitset & _b)
{
	for (int i = 0; i < getArraySize(); i++)
		m_bitset[i] |= _b.m_bitset[i];

	return *this;
}

Bitset::Bitset(Bitset const & _b)
{
	m_bitsetSize = _b.m_bitsetSize;
	m_bitset = new unsigned int[getArraySize()];
	memcpy(m_bitset, _b.m_bitset, sizeof(unsigned int)* getArraySize() - 1);
}

Bitset & Bitset::operator=(Bitset && _b)
{
	if (&_b == this) return * this;

	m_bitsetSize = _b.m_bitsetSize;
	std::swap(m_bitset, _b.m_bitset);

	return *this;
}

Bitset::Bitset(Bitset && _b)
{
	m_bitsetSize = _b.m_bitsetSize;
	std::swap(m_bitset, _b.m_bitset);
}

/*****************************************************************************/

std::ostream & operator << (std::ostream & _s, Bitset const & _set)
{
	for (int i = 0; i < _set.getSize(); i++)
		if (_set.isSet(i))
			_s << '1';
		else
			_s << '0';
	
	return _s;
}