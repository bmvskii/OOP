// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "numeric_range.hpp"

#include <stdexcept>

NumericRange::Iterator::Iterator(int _pos)
{
	m_currPos = _pos;
}

//оператор разыменования
int NumericRange::Iterator::operator*() const
{
	return m_currPos;
}

bool NumericRange::Iterator::operator==(Iterator _iter) const
{
	return _iter.m_currPos == m_currPos;
}

bool NumericRange::Iterator::operator!=(Iterator _iter) const
{
	return !(_iter == *this);
}

//оператор постфиксного инкремента
NumericRange::Iterator & NumericRange::Iterator::operator++()
{
	NumericRange::Iterator _new = *this;
	m_currPos++;
	return _new;
}

//оператор префиксного инкремента
NumericRange::Iterator NumericRange::Iterator::operator++(int)
{
	m_currPos++;
	return * this;
}

//конструктор по умолчанию
NumericRange::NumericRange()
{
	m_highBound = m_lowBound = 0;
}

//конструктор с параметрами
NumericRange::NumericRange(
	int _l,
	int _h
)
{
	m_lowBound = _l;
	m_highBound = _h;
	if (m_lowBound > m_highBound)
		throw std::logic_error("Low bound higher than high bound");
}

//конструктор из строки
NumericRange::NumericRange(std::string const & _s)
{
	//переменные для левой и правой границы интервала
	std::string l, h;
	
	//воспользуемся встроеным методом в std::string::find , который
	//ищет вхождение символов/строки и возвращает индекс , в противном случае
	//возвращает -1

	if (_s.find("[") == std::string::npos) 
		throw std::logic_error("Invalid format");
	if (_s.find("]") == std::string::npos)
		throw std::logic_error("Invalid format");
	if (_s.find(":") == std::string::npos) 
		throw std::logic_error("Invalid format");
	
	//проверка на то, что у нас в строке имеется только по одному екземпляру
	//квадратных скобок и двоеточие
	int lBr = 0,
		rBr = 0,
		dots = 0;

	for (int i = 0; i < _s.length(); i++)
	{
		if (_s[i] == '[')
			lBr++;
		if (_s[i] == ']')
			rBr++;
		if (_s[i] == ':')
			dots++;
	}

	//если больше 1 , то выбрасываем исключение
	if (lBr > 1 || rBr > 1 || dots > 1)
		throw std::logic_error("Invalid format");

	//начинаем разделять числа
	bool isDots = false;
	for (int i = 1; i < _s.length() - 1; i++)
	{
		//если дошли до разделителя, то начинаем считывать другую границу
		if (_s[i] == ':')
		{
			isDots = true;
			continue;
		}

		//добавление символов 
		if (isDots)
			h += _s[i];
		else
			l += _s[i];
	}

	//пытаемся получившееся проверить на то,
	//преобразуется ли данная строка в число или нет
	if (!std::atoi(l.c_str()))
		throw std::logic_error("Invalid format");
	if (!std::atoi(h.c_str())) 
		throw std::logic_error("Invalid format");

	//если да , то присваиваем
	m_lowBound = std::atoi(l.c_str());
	m_highBound = std::atoi(h.c_str());
	if (m_lowBound > m_highBound)
		throw std::logic_error("Low bound higher than high bound");
}

std::ostream & operator<<(std::ostream & _s, NumericRange const & _nr)
{
	//глобальный оператор вывода в поток
	_s << "[" << _nr.getLowBound() << ":" << _nr.getHighBound() << "]";
	return _s;
}