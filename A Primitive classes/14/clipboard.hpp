// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _CLIPBOARD_HPP_
#define _CLIPBOARD_HPP_

/*****************************************************************************/

#include <string>

class Clipboard
{

/*-----------------------------------------------------------------*/

public:

/*------------------------------------------------------------------*/

	enum DataFormat
	{
		Format_Empty,
		Format_Text,
		Format_Binary
	};

	Clipboard(int _size = 4096);

	~Clipboard() = default;

	Clipboard(Clipboard & _c); 

	Clipboard & operator = (Clipboard & _c);

	Clipboard(Clipboard && _c);

	Clipboard & operator = (Clipboard && _c);
	
	void putText(const char* _text);

	bool putBinaryData(void* _data, int _size);

	void clear();

	DataFormat getCurrentFormat() const;

	int getCurrentDataSize() const;

	int getMaxBufferSize() const;

	void copyTextTo(char* _text);

	void copyBinaryDataTo(void* _data);

	operator bool() const;

	void operator += (const char * _str);

/*------------------------------------------------------------------*/

private:
	
	DataFormat m_currentFormat;

	int m_dataBufferSize;

	int m_currentDataSize;

	void * m_binaryData;

	std::string m_stringBuffer;
/*------------------------------------------------------------------*/

};

/*****************************************************************************/

inline Clipboard::DataFormat 
Clipboard::getCurrentFormat() const
{
	return m_currentFormat;
}

/*****************************************************************************/

inline int Clipboard::getCurrentDataSize() const
{
	switch (m_currentFormat)	
	{
	case Clipboard::Format_Empty:
		return 0;
	case Clipboard::Format_Text:
		return m_stringBuffer.length() + 1;
	case Clipboard::Format_Binary:
		return m_currentDataSize;
	default:
		break;
	}
}

/*****************************************************************************/

inline int Clipboard::getMaxBufferSize() const
{
	return m_dataBufferSize;
}

/*****************************************************************************/

#endif //  _CLIPBOARD_HPP_
