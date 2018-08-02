// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _COURSE_HPP_
#define _COURSE_HPP_

class Checkpoint;

#include "controlform.hpp"

#include <string>
#include <memory>
#include <unordered_map>
#include <functional>

class Course
{
	std::unordered_map<std::string, std::unique_ptr<Checkpoint> > Checkpoints;

	std::string Name;
	
	ControlForm Form;
	

public:

	Course(
		std::string const & _Name,
		ControlForm _Form
	);

	~Course() = default;

	std::string const & getName() const
	{
		return Name;
	}

	ControlForm getControlForm() const
	{
		return Form;
	}

	bool hasCheckpoints() const
	{
		return !Checkpoints.empty();
	}

	bool hasCheckpoint(std::string const & _c) const
	{
		return Checkpoints.find(_c) != Checkpoints.end();
	}

	Checkpoint & getCheckpoint(std::string const & _c) const
	{
		return *Checkpoints.find(_c)->second.get();
	}

	int getCheckpointSum() const;

	void forEachCheckpoint(std::function<void(Checkpoint const &)> _f) const;

	void addCheckpoint(std::unique_ptr<Checkpoint> _c);
};

#endif // _COURSE_HPP_