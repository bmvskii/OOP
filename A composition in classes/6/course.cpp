// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "course.hpp"
#include "messages.hpp"
#include "checkpoint.hpp"

Course::Course( std::string const & _Name, ControlForm _Form ) : Name(_Name) , Form(_Form)
{}

void Course::addCheckpoint(std::unique_ptr<Checkpoint> _c)
{
	Checkpoints.insert(std::make_pair(_c->getName(),std::move(_c)));
}

void Course::forEachCheckpoint(std::function<void(Checkpoint const &)> _f) const
{
	for (auto it = Checkpoints.begin(); it != Checkpoints.end(); ++it)
		_f(*it->second.get());
}

int Course::getCheckpointSum() const
{
	int total = 0;
	for (auto const & checkpoint : Checkpoints)
		total += checkpoint.second->getMark();
	return total;
}