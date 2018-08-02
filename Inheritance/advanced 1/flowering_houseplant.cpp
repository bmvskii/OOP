#include "flowering_houseplant.hpp"
#include "message.hpp"

FloweringHouseplant::FloweringHouseplant(
	std::string const & _name,
	int _waterPeriod,
	int _bloomingDuration,
	int _needWatering
)
	: Houseplant(_name,_waterPeriod)
	, m_bloomingDuration(_bloomingDuration)
	, m_nNeedWatering(_needWatering)
	, m_isBlooming(false)
	, m_nDoneWatering(0)
	, m_nBloomingDays(0)
{
	if (_bloomingDuration < 1)
		throw std::logic_error(Messages::InvalidBloomingDuration);

	if (_waterPeriod < 1)
		throw std::logic_error(Messages::InvalidWateringNumber);

	if (_needWatering < 1)
		throw std::logic_error(Messages::InvalidNeedWatering);

}

void FloweringHouseplant::water()
{
	DateTime rd = getRecentWaterDate();
	DateTime cd   = getCurrentDate();

	int waterPeriod = getWaterPeriod();

	if (getDifference(rd, cd) == waterPeriod)
		blooming();
	else if (getDifference(rd, cd) == waterPeriod + 1 || getDifference(rd, cd) == waterPeriod - 1)
		if (isBlooming())
			m_nBloomingDays++;
	else
		if (m_nDoneWatering != 0)
			m_nDoneWatering--;

	changeRecentWaterDate();
}

void FloweringHouseplant::blooming()
{
	if (m_nNeedWatering == m_nDoneWatering)
		m_isBlooming = true;

	if (m_isBlooming)
		m_nBloomingDays++;
	else
		m_nDoneWatering++;

	if (m_nBloomingDays == m_bloomingDuration)
	{
		std::cout << "CONGRATS! THE PLANT IS GROWN.";
		m_nDoneWatering = 0;
		m_nBloomingDays = 0;
		upWaterPeriod();
	}
}

void FloweringHouseplant::daySkip()
{
	skippingDay();
}

void FloweringHouseplant::nDaysPassed(int _N)
{
	countSkippingDays(_N);
}