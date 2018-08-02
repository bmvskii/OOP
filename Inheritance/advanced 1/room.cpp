#include "room.hpp"

void Room::addHouseplant(std::unique_ptr<Houseplant> _p)
{
	m_houseplants.push_back(std::move(_p));
}
