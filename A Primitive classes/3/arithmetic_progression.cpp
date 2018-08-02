
#include "arithmetic_progression.hpp"

#include <stdexcept>

/*****************************************************************************/

ArithmeticProgression::ArithmeticProgression() : 
	m_progressionStep(1), 
	m_startValue(0)
{}

/*****************************************************************************/

ArithmeticProgression::ArithmeticProgression(int _value, int _step) :
	m_progressionStep(_step),
	m_startValue(_value)
{}

/*****************************************************************************/

int ArithmeticProgression::getIthElement(int _i) const
{
	if (_i < 0)
		throw std::logic_error("Invalid index");
	_i++;
	return m_startValue + (m_progressionStep*(_i-1));
}

/*****************************************************************************/

int ArithmeticProgression::partialSum(int _i, int _k) const
{
	isValidIndeces(_i, _k);

	int partialSum = 0;

	for (int i = _i; i < _k + 1; i++)
		partialSum += getIthElement(i);

	return partialSum;
}

/*****************************************************************************/

float ArithmeticProgression::partialAverage(int _i, int _k) const
{
	isValidIndeces(_i, _k);
	return (float) partialSum(_i, _k) / (_k - _i + 1);
}

/*****************************************************************************/

void ArithmeticProgression::display(int _i, int _k, std::ostream & _stream)
{
	isValidIndeces(_i, _k);
	for (int i = _i; i < _k + 1; i++)
	{
		_stream << getIthElement(i);
		(i == _k) ? _stream << "" : _stream << " ";
 	}
}

/*****************************************************************************/

bool ArithmeticProgression::matchesArray(const int * _pElements, int _N) const
{
	for (int i = 0; i < _N; i++)
		if (getIthElement(i) != _pElements[i]) return false;

	return true;
}

/*****************************************************************************/

bool ArithmeticProgression::matchesArray(const std::initializer_list<int> _pElements) const
{
	int index = 0;

	for (int item : _pElements)
		if (item != getIthElement(index++)) return false;
		
	return true;
}

/*****************************************************************************/

ArithmeticProgression ArithmeticProgression::makeInverted() const
{
	return ArithmeticProgression(m_startValue, -m_progressionStep);
}

/*****************************************************************************/