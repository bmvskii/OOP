#include "houseplant.hpp"
#include "message.hpp"

Houseplant::Houseplant(
	std::string const & _name,
	int _waterPeriod
)
	: m_name(_name)
	, m_waterPeriod(_waterPeriod)
	, m_age(0)
{
	if (_name.empty())
		throw std::logic_error(Messages::EmptyHouseplantName);
	
	if (_waterPeriod < 1)
		throw std::logic_error(Messages::InvalidWateringNumber);

	m_currentDate = DateTime();
	m_birthday = m_currentDate;
	m_recentWaterDate = m_currentDate;
}

void Houseplant::skippingDay()
{
	getCurrentDate()++;
	if (getCurrentDate() == getBirthday()) upAge();
}

int Houseplant::getDifference(DateTime _lhs, DateTime _rhs)
{
	int nDiffer = 0;
	while (_lhs++ != _rhs) nDiffer++;
	return nDiffer;
}

void Houseplant::changeRecentWaterDate()
{
	m_recentWaterDate = m_currentDate;
}

void Houseplant::upAge()
{
	m_age++;
}

void Houseplant::upWaterPeriod()
{
	m_waterPeriod += 2;
}

void Houseplant::countSkippingDays(int _N)
{
	for (int i = 0; i < _N; i++) skippingDay();
}

