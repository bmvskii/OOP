// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine
#define _CRT_SECURE_NO_WARNINGS
#include "clipboard.hpp"

#include <stdexcept>
#include <cstring>
 
/*****************************************************************************/

Clipboard::Clipboard(int _size)
	: m_dataBufferSize(_size)
	, m_currentFormat(DataFormat::Format_Empty)
	, m_currentDataSize(0)
{
	if (_size < 1)
		throw std::logic_error("Buffer size must be positive");
}

/*****************************************************************************/

Clipboard::Clipboard(Clipboard & _c)
{
	m_currentDataSize = _c.m_currentDataSize;
	m_dataBufferSize = _c.m_dataBufferSize;
	m_currentFormat = _c.m_currentFormat;
	m_stringBuffer = _c.m_stringBuffer;
	
	if (m_currentFormat == DataFormat::Format_Binary)
		memcpy(m_binaryData, _c.m_binaryData, m_currentDataSize);
}

/*****************************************************************************/

Clipboard & Clipboard::operator=(Clipboard & _c)
{
	if (&_c == this) return *this;

	m_currentDataSize = _c.m_currentDataSize;
	m_dataBufferSize = _c.m_dataBufferSize;
	m_currentFormat = _c.m_currentFormat;
	m_stringBuffer = _c.m_stringBuffer;

	if (m_currentFormat == DataFormat::Format_Binary)
		memcpy(m_binaryData, _c.m_binaryData, m_currentDataSize);

	return * this;
}

/*****************************************************************************/

Clipboard::Clipboard(Clipboard && _c)
{
	m_currentDataSize = _c.m_currentDataSize;
	m_dataBufferSize = _c.m_dataBufferSize;
	m_currentFormat = _c.m_currentFormat;
	m_stringBuffer = std::move(_c.m_stringBuffer);

	if (m_currentFormat == DataFormat::Format_Binary)
		m_binaryData = std::move(_c.m_binaryData);

	_c.clear();
}

/*****************************************************************************/

Clipboard & Clipboard::operator=(Clipboard && _c)
{
	if (&_c == this) return *this;
	
	m_currentDataSize = _c.m_currentDataSize;
	m_dataBufferSize = _c.m_dataBufferSize;
	m_currentFormat = _c.m_currentFormat;
	m_stringBuffer = std::move(_c.m_stringBuffer);

	if (m_currentFormat == DataFormat::Format_Binary)
		m_binaryData = std::move(_c.m_binaryData);

	_c.clear();

	return * this;
}

/*****************************************************************************/

void Clipboard::putText(const char * _text)
{
	if (m_currentFormat == DataFormat::Format_Empty)
		m_currentFormat = DataFormat::Format_Text;

	if (strlen(_text) + 1 > m_dataBufferSize)
		for (int i = 0; i < m_dataBufferSize - 1; i++)
			m_stringBuffer += _text[i];
	else
		m_stringBuffer += _text;
}

/*****************************************************************************/

bool Clipboard::putBinaryData(void * _data, int _size)
{
	if (_size > m_dataBufferSize)
		return false;

	if (m_currentFormat == DataFormat::Format_Empty)
		m_currentFormat = DataFormat::Format_Binary;

	m_binaryData = _data;
	m_currentDataSize = _size;
	return true;
}

/*****************************************************************************/

void Clipboard::clear()
{
	m_currentFormat = DataFormat::Format_Empty;
	m_currentDataSize = 0;
	m_stringBuffer = "";
}

/*****************************************************************************/

void Clipboard::copyTextTo(char * _text)
{
	if (m_stringBuffer.empty() || m_currentFormat != DataFormat::Format_Text)
		throw std::logic_error("No text in clipboard");
		
	strcpy(_text, m_stringBuffer.c_str());
}

/*****************************************************************************/

void Clipboard::copyBinaryDataTo(void * _data)
{
	if (!m_currentDataSize || m_currentFormat != DataFormat::Format_Binary)
		throw std::logic_error("No binary data in clipboard");

	memcpy(_data, m_binaryData, m_currentDataSize);
}

/*****************************************************************************/

Clipboard::operator bool() const
{
	if ((m_currentDataSize == 0 && m_stringBuffer.empty()) ||
		m_currentFormat == DataFormat::Format_Empty) return false;
	return true;
}

/*****************************************************************************/

void Clipboard::operator+=(const char * _str)
{
	if (m_currentFormat == DataFormat::Format_Binary)
		return;
	if (m_currentDataSize == DataFormat::Format_Empty)
		m_currentFormat = DataFormat::Format_Text;

	m_stringBuffer += _str;
}

/*****************************************************************************/
