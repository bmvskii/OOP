// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _CHECKPOINT_HPP_
#define _CHECKPOINT_HPP_
#include <string>

class Course;

class Checkpoint
{
	std::string Name;

	int MaximalMark;

public:

	Checkpoint(std::string const & _Name,int _Mark);

	~Checkpoint() = default;

	std::string const & getName() const 
	{
		return Name;
	}

	int getMark() const 
	{
		return MaximalMark;
	}

	bool operator < (Checkpoint const & _c) const
	{
		return Name < _c.Name;
	}

};

#endif // _CHECKPOINT_HPP_