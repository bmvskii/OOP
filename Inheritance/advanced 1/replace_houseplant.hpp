#ifndef REPLACE_HOUSEPLANT_HPP
#define REPLACE_HOUSEPLANT_HPP

class FoliarHouseplant;
class Room;

#include <memory>

class ReplaceHouseplant
{
public:
	virtual void replace(std::unique_ptr<FoliarHouseplant> _p) = 0;
};

#endif // !REPLACE_HOUSEPLANT_HPP
