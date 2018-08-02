#include "house_owner.hpp"
#include "foliar_houseplant.hpp"
#include "replace_houseplant.hpp"
#include "message.hpp"

PlantOwner::~PlantOwner() = default;

PlantOwner::PlantOwner(Room * _r)
	: m_room(_r)
{
	if (_r == nullptr)
		throw std::logic_error(Messages::RoomNullptr);
}

void PlantOwner::replace(std::unique_ptr<FoliarHouseplant> _fh)
{
	m_room->addHouseplant(std::move(_fh));
}