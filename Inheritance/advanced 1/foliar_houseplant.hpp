#ifndef _FOLIAR_HOUSEPLANT_HPP
#define _FOLIAR_HOUSEPLANT_HPP

#include "houseplant.hpp"
#include <memory>

class Room;
class PlantOwner;

class FoliarHouseplant : public Houseplant
{
public:
	
	FoliarHouseplant(
		std::string const & _name,
		int _waterPeriod,
		int _beginningHeigth
	);

	~FoliarHouseplant();
	void water() override;
	bool isHight() const;
	void daySkip() override;
	void setPlantOwner(PlantOwner * _pOwner);
	void nDaysPassed(int _N);
private:

	void growing();
	PlantOwner * m_owner;
	int m_flowerHeight;
};

inline bool FoliarHouseplant::isHight() const
{
	return m_flowerHeight >= 250;
}

#endif // !_FOLIAR_HOUSEPLANT_HPP


