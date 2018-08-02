#ifndef _ARTIFICIAL_HOUSEPLANT_HPP
#define _ARTIFICIAL_HOUSEPLANT_HPP

#include "houseplant.hpp"

class ArtificialHouseplant : public Houseplant
{
public:
	ArtificialHouseplant(
		std::string const & _name,
		int _waterPeriod
	);
	~ArtificialHouseplant() = default;
	void water() override;
	void daySkip() override;
}; 

#endif // !_ARTIFICIAL_HOUSEPLANT_HPP




