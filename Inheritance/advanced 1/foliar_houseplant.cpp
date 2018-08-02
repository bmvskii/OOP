#include "foliar_houseplant.hpp"
#include "message.hpp"
#include "house_owner.hpp"

FoliarHouseplant::~FoliarHouseplant() = default;

FoliarHouseplant::FoliarHouseplant(
	std::string const & _name,
	int _waterPeriod,
	int _beginningHeigth
)
	: Houseplant(_name,_waterPeriod)
	, m_flowerHeight(_beginningHeigth)
{
	if (_beginningHeigth < 0)
		throw std::logic_error(Messages::InvalidBeginningHeight);
}

void FoliarHouseplant::water()
{
	DateTime rd = getRecentWaterDate();
	DateTime cd = getCurrentDate();

	int waterPeriod = getWaterPeriod();

	if (getDifference(rd, cd) == waterPeriod)
		growing();

	else if (getDifference(rd, cd) == waterPeriod + 1 || getDifference(rd, cd) == waterPeriod - 1)
		growing();

	changeRecentWaterDate();
}

void FoliarHouseplant::growing()
{
	if (isHight())
	{
		m_flowerHeight /= 2;
		m_owner->replace(std::make_unique<FoliarHouseplant>(
			getName(),
			getWaterPeriod(),
			m_flowerHeight
		));
	}
	else
		m_flowerHeight++;
}

void FoliarHouseplant::daySkip()
{
	skippingDay();
}

void FoliarHouseplant::setPlantOwner(PlantOwner * _pOwner)
{
	if (_pOwner == nullptr)
		throw std::logic_error(Messages::HaveNotOwner);
	m_owner = _pOwner;
}

void FoliarHouseplant::nDaysPassed(int _N)
{
	countSkippingDays(_N);
}