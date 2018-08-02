#ifndef _HOUSEPLANT_HPP
#define _HOUSEPLANT_HPP

#include <string>
#include "datetime.hpp"

class Houseplant
{
protected:
	Houseplant(
		std::string const & _name,
		int _waterPeriod
	);
	void skippingDay();
	int getDifference(
		DateTime _lhs,
		DateTime _rhs
	);
	void countSkippingDays(int _N);
public:
	virtual ~Houseplant() = default;
	virtual void water() = 0;
	virtual void daySkip() = 0;

	void changeRecentWaterDate();
	void upAge();
	void upWaterPeriod();

	std::string const & getName() const;
	DateTime & getRecentWaterDate();
	DateTime & getCurrentDate();
	int getAge() const;
	int getWaterPeriod() const;
	DateTime const & getBirthday() const;
private:
	std::string m_name;
	DateTime m_recentWaterDate;
	DateTime m_birthday;
	DateTime m_currentDate;
	int m_age;
	int m_waterPeriod;
};

inline int Houseplant::getAge() const
{
	return m_age;
}

inline std::string const & Houseplant::getName() const
{
	return m_name;
}

inline int Houseplant::getWaterPeriod() const
{
	return m_waterPeriod;
}

inline DateTime & Houseplant::getRecentWaterDate()
{
	return m_recentWaterDate;
}

inline DateTime const & Houseplant::getBirthday() const
{
	return m_birthday;
} 

inline DateTime & Houseplant::getCurrentDate()
{
	return m_currentDate;
}

#endif // !_HOUSEPLANT_HPP


