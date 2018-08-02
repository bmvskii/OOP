#include "fruiting_houseplant.hpp"
#include "message.hpp"

FruitingHouseplant::FruitingHouseplant(
	std::string const & _name,
	std::string const & _fruitName,
	int _waterPeriod,
	int _fruitingPeriod
)
	: Houseplant(_name,_waterPeriod)
	, m_fruitName(_fruitName)
	, m_nFruitingPeriod(_fruitingPeriod)
	, m_nFruitingDays(0)
{
	if (_fruitName.empty())
		throw std::logic_error(Messages::EmptyFruitName);

	if (_fruitingPeriod < 1)
		throw std::logic_error(Messages::InvalidFruitingPeriod);
}

void FruitingHouseplant::water()
{

	DateTime rd = getRecentWaterDate();
	DateTime cd = getCurrentDate();

	int waterPeriod = getWaterPeriod();

	if (getDifference(rd, cd) == waterPeriod)
	{
		if (m_nFruitingDays == m_nFruitingPeriod)
		{
			std::cout << "BINGO! THE " << m_fruitName << " ON THE " << getName() << "HAS GROWN.";
			m_nFruitingDays = 0;
		}
		else
			m_nFruitingDays++;
	}
	else if (getDifference(rd, cd) == waterPeriod + 1 || getDifference(rd, cd) == waterPeriod - 1)
		changeRecentWaterDate();
	else
		if (m_nFruitingDays != 0)
			m_nFruitingDays--;
		
	changeRecentWaterDate();
}

void FruitingHouseplant::daySkip()
{
	skippingDay();
}

void FruitingHouseplant::nDaysPassed(int _N)
{
	countSkippingDays(_N);
}