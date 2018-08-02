#ifndef _FRUITING_HOUSEPLANT_HPP
#define  _FRUITING_HOUSEPLANT_HPP

#include <string>
#include "houseplant.hpp"

class FruitingHouseplant : public Houseplant
{
public:
	FruitingHouseplant(
		std::string const & _name,
		std::string const & _fruitName,
		int _waterPeriod,
		int _fruitingPeriod
	);
	~FruitingHouseplant() = default;
	void water() override;
	void daySkip() override;
	void nDaysPassed(int _N);
private:
	std::string m_fruitName;
	int m_nFruitingPeriod;
	int m_nFruitingDays;
};

#endif // !_FRUITING_HOUSEPLANT_HPP


