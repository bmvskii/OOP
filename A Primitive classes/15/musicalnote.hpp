// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef _MUSICALNOTE_HPP_
#define _MUSICALNOTE_HPP_
#include<string>
/*****************************************************************************/


class MusicalNote
{
public:

/*------------------------------------------------------------------*/

	enum Note
	{
		Note_A,
		Note_B,
		Note_C,
		Note_D,
		Note_E,
		Note_F,
		Note_G
	};

	enum Sign
	{
		Sign_None,
		Sign_Sharp,
		Sign_Flat
	};

	enum Interval
	{
		Interval_Prime,
		Interval_Minor_Second,
		Interval_Major_Second,
		Interval_Minor_Third,
		Interval_Major_Third,
		Interval_Fourth,
		Interval_Small_Fifth,
		Interval_Fifth,
		Interval_Minor_Sixth,
		Interval_Major_Sixth,
		Interval_Minor_Seventh,
		Interval_Major_Seventh
	};

	static const int noteToInterval[];

	static const Note intervalToNote[];
	
	static const Sign intervalToSigns[];

/*------------------------------------------------------------------*/


	MusicalNote(int _note, int _sign = Sign_None);

	MusicalNote(std::string nS);

	int getNote()const;

	int getSign()const;

	char* toString() const;

	bool operator ==(MusicalNote _mN);

	bool operator !=(MusicalNote _mN);

	MusicalNote operator ++();

	MusicalNote operator ++(int);

	MusicalNote operator --();

	MusicalNote operator --(int);

	MusicalNote operator +=(int _i);

	MusicalNote operator -=(int _i);

	int operator -(MusicalNote _mN);

private:

	int m_interval;

	int m_note;
	
	int m_sign;

/*------------------------------------------------------------------*/

};


/*****************************************************************************/

#endif //  _MUSICALNOTE_HPP_
