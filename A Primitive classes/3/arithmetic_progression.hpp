#ifndef _ARITHMETIC_PROGRESSION_HPP_
#define _ARITHMETIC_PROGRESSION_HPP_

/*****************************************************************************/

#include <iostream>
#include <initializer_list>

/*****************************************************************************/


class ArithmeticProgression
{
public:

	ArithmeticProgression();

	ArithmeticProgression(int _value, int _step = 1);
	
	int getInitialValue() const;

	int getStep() const;

	int getIthElement(int _i) const;

	int partialSum(int, int) const;

	float partialAverage(int, int) const;

	void display(int i, int k, std::ostream & _stream = std::cout);

	bool matchesArray(const int * _pElements, int _N) const;

	bool matchesArray(const std::initializer_list<int> _pElements) const;

	ArithmeticProgression makeInverted() const;

	bool operator==(const ArithmeticProgression & _prog) const;

	bool operator!=(const ArithmeticProgression & _prog) const;

private:

	void isValidIndeces(int _i, int _k) const;

	int m_progressionStep, m_startValue;
};

/*****************************************************************************/

inline
int ArithmeticProgression::getInitialValue() const
{
	return m_startValue;
}

/*****************************************************************************/

inline
int ArithmeticProgression::getStep() const
{
	return m_progressionStep;
}

/*****************************************************************************/

inline
bool ArithmeticProgression::operator==(const ArithmeticProgression & _prog) const
{
	return _prog.m_progressionStep == m_progressionStep && _prog.m_startValue == m_startValue;
}

/*****************************************************************************/

inline
bool ArithmeticProgression::operator!=(const ArithmeticProgression & _prog) const 
{
	return !(*this == _prog);
}

/*****************************************************************************/

inline
void ArithmeticProgression::isValidIndeces(int _i, int _k) const
{
	if (_i < 0 || _k < 0 || _i > _k)
		throw std::logic_error("Invalid index range");
}

/*****************************************************************************/

#endif //  _ARITHMETIC_PROGRESSION_HPP_