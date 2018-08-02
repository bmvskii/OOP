#include "artificial_houseplant.hpp"

ArtificialHouseplant::ArtificialHouseplant(
	std::string const & _name,
	int _waterPeriod
)
	: Houseplant(_name,_waterPeriod)
{}

void ArtificialHouseplant::water()
{
	std::cout << "WARNING! DON'T WATER ARTIFICIAL HOUSEPLANT.";
}

void ArtificialHouseplant::daySkip()
{
	skippingDay();
}