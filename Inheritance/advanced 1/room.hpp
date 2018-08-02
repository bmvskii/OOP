#ifndef _ROOM_HPP
#define _ROOM_HPP

#include <vector>
#include <memory>
#include "houseplant.hpp"

class Room
{
public:
	Room() = default;
	~Room() = default;
	void addHouseplant(std::unique_ptr<Houseplant> _p);
	int ñountHouseplants() const;
private:
	std::vector<std::unique_ptr<Houseplant> > m_houseplants;
};

inline
int Room::ñountHouseplants() const
{
	return m_houseplants.size();
}

#endif // !_ROOM_HPP

