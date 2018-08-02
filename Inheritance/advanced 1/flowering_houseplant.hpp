#ifndef _FLOWERING_HOUSEPLANT_HPP
#define _FLOWERING_HOUSEPLANT_HPP

#include "houseplant.hpp"

class FloweringHouseplant : public Houseplant
{
public:	
	FloweringHouseplant(
		std::string const & _name,
		int _waterPeriod,
		int _bloomingDuration,
		int _needWatering
	);	
	~FloweringHouseplant() = default;
	void water() override;
	void daySkip() override;
	void nDaysPassed(int _N);

private:
	void blooming();
	bool isBlooming() const;
	bool m_isBlooming;
	int m_bloomingDuration;
	int m_nBloomingDays;
	int m_nDoneWatering;
	int m_nNeedWatering;
};

inline bool FloweringHouseplant::isBlooming() const
{
	return m_isBlooming;
}

#endif // !_FLOWERING_HOUSEPLANT_HPP


