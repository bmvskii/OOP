#ifndef HOUSE_OWNER_HPP
#define HOUSE_OWNER_HPP

#include "replace_houseplant.hpp"
#include "room.hpp"
#include <memory>

class FoliarHouseplant;
class PlantOwner : public ReplaceHouseplant
{
public:
	PlantOwner(Room *_r);
	~PlantOwner();
	void replace(std::unique_ptr<FoliarHouseplant> _p) override;
private:
	Room * m_room;
};

#endif // !HOUSE_OWNER_HPP
