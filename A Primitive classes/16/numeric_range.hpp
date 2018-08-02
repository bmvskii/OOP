// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _NUMERIC_RANGE_HPP_
#define _NUMERIC_RANGE_HPP_

#include <iostream>

class NumericRange
{
public:

	class Iterator
	{
	public:
		explicit Iterator(int _currPos);
		int operator * () const;
		bool operator == (Iterator i) const;
		bool operator != (Iterator i) const;
		Iterator & operator ++ ();
		Iterator operator ++ (int);
	private:
		int m_currPos; 
		friend class NumericRange;
	};

/*-----------------------------------------------------------------*/
public:
	NumericRange();
	NumericRange(int _lBound, int _hBound);
	NumericRange(std::string const & _s);
	Iterator begin() const;
	Iterator end() const;
	int getLowBound() const;
	int getHighBound() const;
	int getWidth() const;
	bool contains(int _num) const;
	bool intersectsWith(NumericRange const & _numRange) const;
	bool includes(NumericRange const & _numRange) const;
	bool belongsTo(NumericRange const & _numRange) const;
	bool adjacentTo(NumericRange const & _numRange) const;
	bool operator ==(NumericRange const & _numRange) const;
	bool operator !=(NumericRange const & _numRange) const;
	bool operator >=(NumericRange const & _numRange) const;
	bool operator <=(NumericRange const & _numRange) const;
	bool operator <(NumericRange const & _numRange) const;
	bool operator >(NumericRange const & _numRange) const;
	friend std::ostream & operator << (std::ostream & _s, NumericRange const & _numRange);

private:
	int m_lowBound, m_highBound;
};

inline int NumericRange::getLowBound() const
{
	return m_lowBound;
}

inline bool NumericRange::belongsTo(NumericRange const & _numRange) const
{
	if (_numRange.m_lowBound <= m_lowBound && _numRange.m_highBound >= m_highBound)
		return true;
	else
		return false;
}

inline int NumericRange::getHighBound() const
{
	return m_highBound;
}

inline int NumericRange::getWidth() const
{
	return m_highBound - m_lowBound + 1;
}

inline bool NumericRange::contains(int _number) const
{
	//проверка точки на наличие в данном интервале
	for (int i = m_lowBound; i < m_highBound + 1; i++)
		if (i == _number) return true;
	return false;
}

inline bool NumericRange::operator ==(NumericRange const & _numRange) const
{
	if (_numRange.m_lowBound == m_lowBound && _numRange.m_highBound == m_highBound)
		return true;
	else
		return false;
}

inline bool NumericRange::intersectsWith(NumericRange const & _numRange) const
{
	//проверка на пересечение с другим интервалом

	if (m_lowBound <= _numRange.m_lowBound && m_highBound >= _numRange.m_lowBound)
	{
		return true;
	}

	if (m_lowBound <= _numRange.m_highBound && m_highBound >= _numRange.m_highBound)
	{
		return true;
	}

	if (m_lowBound >= _numRange.m_lowBound && m_lowBound <= _numRange.m_highBound)
	{
		return true;
	}

	if (m_highBound >= _numRange.m_lowBound && m_highBound <= _numRange.m_highBound)
	{
		return true;
	}
	return false;
}

inline bool NumericRange::includes(NumericRange const & _numRange) const
{
	if (_numRange.m_lowBound >= m_lowBound && _numRange.m_highBound <= m_highBound)
		return true;
	else
		return false;
}

inline bool NumericRange::adjacentTo(NumericRange const & _numRange) const
{
	if (_numRange.m_highBound < m_lowBound || _numRange.m_lowBound > m_highBound)
		return true;
	else
		return false;
}

inline bool NumericRange::operator !=(NumericRange const & _numRange) const
{
	return !(*this == _numRange);
}

inline bool NumericRange::operator >=(NumericRange const & _numRange) const
{
	if (m_lowBound > _numRange.m_lowBound ||
	   (m_lowBound == _numRange.m_lowBound && m_highBound >= _numRange.m_highBound))
		return true;
	else
		return false;
}

inline bool NumericRange::operator <=(NumericRange const & _numRange) const
{
	if (m_lowBound < _numRange.m_lowBound || 
	   (m_lowBound == _numRange.m_lowBound && m_highBound <= _numRange.m_highBound))
		return true;
	else
		return false;
}

inline bool NumericRange::operator <(NumericRange const & _numRange) const
{
	if (m_lowBound < _numRange.m_lowBound ||
	   (m_lowBound == _numRange.m_lowBound && m_highBound < _numRange.m_highBound))
		return true;
	else
		return false;
}

inline bool NumericRange::operator >(NumericRange const & _numRange) const
{
	if (m_lowBound > _numRange.m_lowBound || 
	   (m_lowBound == _numRange.m_lowBound && m_highBound > _numRange.m_highBound))
		return true;
	else
		return false;
}

//возврат итератора на элемент начала интервала
inline NumericRange::Iterator NumericRange::begin() const
{
	return Iterator(m_lowBound);
}

//возврат итератора на элемент за концом интервала
inline NumericRange::Iterator NumericRange::end() const
{
	return Iterator(m_highBound + 1);
}

#endif //  _NUMERIC_RANGE_HPP_
