// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "musicalnote.hpp"

#include <stdexcept>

const int MusicalNote::noteToInterval[] = { 0, 2, 3 , 5, 7, 8, 10 };

const MusicalNote::Note MusicalNote::intervalToNote[]= { Note_A, Note_A, Note_B, Note_C, Note_C, Note_D, Note_D, Note_E, Note_F, Note_F, Note_G, Note_G };//оприделения static, константний масив значень з enum Note

const MusicalNote::Sign MusicalNote::intervalToSigns[] = { Sign_None, Sign_Sharp, Sign_None, Sign_None, Sign_Sharp ,Sign_None, Sign_Sharp, Sign_None, Sign_None, Sign_Sharp, Sign_None, Sign_Sharp };//оприделения static, константний масив значень з enum Sign

MusicalNote::MusicalNote(int _note, int _sign) 
	:	m_note(_note)
	,   m_sign(_sign)
{
	if ((_note == 4 && _sign == 1) || (_note == 5 && _sign == 2) 
		|| (_note == 1 && _sign == 1) || (_note == 2 && _sign == 2))
		throw std::logic_error("Invalid note");

	m_interval = noteToInterval[_note];

	if (_sign == 1)
		++m_interval;
	else if (_sign == 2)
		--m_interval;
}

MusicalNote::MusicalNote(std::string _nS)
{
	if (_nS.size() == 2 && _nS[0] > 64 && _nS[0] < 72 && (_nS[1] == '#' || _nS[1] == 'b'))
	{
		m_note = _nS[0] - 'A';
		if (_nS[1] == '#')
			m_sign = Sign_Sharp;
		else if (_nS[1] == 'b')
			m_sign = Sign_Flat;
	}
	else if (_nS.size() == 1 && _nS[0] > 64 && _nS[0] < 72) {
		m_note = _nS[0] - 'A';
		m_sign = Sign_None;
	}
	else
		throw std::logic_error("Invalid format");

	m_interval = noteToInterval[m_note];
	if (m_sign == 1)
		++m_interval;
	else if (m_sign == 2)
		--m_interval;

	if ((m_note == 4 && m_sign == 1) || (m_note == 5 && m_sign == 2) ||
		(m_note == 1 && m_sign == 1) || (m_note == 2 && m_sign == 2)) 
		throw std::logic_error("Invalid note");
}

int MusicalNote::getNote() const
{
	return m_note;
}

int MusicalNote::getSign() const
{
	return m_sign;
}

char* MusicalNote::toString() const
{
	char signNew;
	char noteNew; 
	noteNew = m_note + 'A';

	if (m_sign == Sign_None)
		signNew = '0';
	else if (m_sign == Sign_Sharp)
		signNew = '#';
	else if (m_sign == Sign_Flat)
		signNew = 'b';

	if (signNew != '0') {
		char *cstr = new char[3];
		cstr[0] = noteNew;
		cstr[1] = signNew;
		cstr[2] = '\0';
		return cstr;
	}
	else {
		char *cstr = new char[2];
		cstr[0] = noteNew;
		cstr[1] = '\0';
		return cstr;
	}
}

bool MusicalNote::operator==(MusicalNote _mN)
{
	return m_interval == _mN.m_interval;
}

bool MusicalNote::operator!=(MusicalNote _mN)
{
	return !(*this== _mN);
}

MusicalNote MusicalNote::operator++()
{
	if (m_interval==11) {
		m_interval = 0;
		m_note = 0;
		m_sign = 0;
		return *this;
	}

	++m_interval;
	
	m_note = intervalToNote[m_interval];
	m_sign = intervalToSigns[m_interval];
	
	return *this;
}

MusicalNote MusicalNote::operator++(int)
{
	MusicalNote New(m_note, m_sign);
	
	if (m_interval == 11) {
		m_interval = 0;
		m_note = 0;
		m_sign = 0;
		return New;
	}
	
	++m_interval;
	
	m_note = intervalToNote[m_interval];
	m_sign = intervalToSigns[m_interval];
	
	return New;
}

MusicalNote MusicalNote::operator--()
{
	if (m_interval == 0) {
		m_interval = 11;
		m_note = 6;
		m_sign = 1;
	
		return *this;
	}
	
	--m_interval;
	
	m_note = intervalToNote[m_interval];
	m_sign = intervalToSigns[m_interval];
	
	return *this;
}

MusicalNote MusicalNote::operator--(int)
{
	MusicalNote New(m_note, m_sign);
	
	if (m_interval == 0) {
		m_interval = 11;
		m_note = 6;
		m_sign = 1;
	
		return New;
	}

	--m_interval;

	m_note = intervalToNote[m_interval];
	m_sign = intervalToSigns[m_interval];

	return New;
}

MusicalNote MusicalNote::operator+=(int _i)
{
	if ((m_interval + _i) < 12) {
		m_interval += _i;
		m_note = intervalToNote[m_interval];
		m_sign = intervalToSigns[m_interval];
	}
	else {
		m_interval = (m_interval + _i) % 11;
		m_note = intervalToNote[m_interval];
		m_sign = intervalToSigns[m_interval];
	}

	return *this;
}

MusicalNote MusicalNote::operator-=(int _i)
{
	if ((m_interval - _i) > 0) {
		m_interval -= _i;
		m_note = intervalToNote[m_interval];
		m_sign = intervalToSigns[m_interval];
	}
	else {
		m_interval = 12-(((m_interval - _i)*-1) % 11);
		m_note = intervalToNote[m_interval];
		m_sign = intervalToSigns[m_interval];
	}

	return *this;
}

int MusicalNote::operator-(MusicalNote _mN)
{
	if (m_interval >= _mN.m_interval) 
		return m_interval - _mN.m_interval;
	else 
		return _mN.m_interval - m_interval;
}
