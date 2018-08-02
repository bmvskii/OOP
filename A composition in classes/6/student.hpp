// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _STUDENT_HPP_
#define _STUDENT_HPP_

class Checkpoint;

#include <string>
#include <map>
#include <functional>

class Student
{
	std::string FullName;

	std::map<std::string, std::pair<Checkpoint *, int> > FixedCheckpoints;

public:

	Student(std::string const & _fullName);

	~Student();

	std::string const & getName() const
	{
		return FullName;
	}

	int getMark(std::string const & _c)
	{
		return FixedCheckpoints.find(_c)->second.second;
	}

	bool isCheckpointPassed(std::string const & _c) const
	{
		return FixedCheckpoints.find(_c) != FixedCheckpoints.end();
	}

	void forEachCheckpoint(std::function<void(Checkpoint const & _e)> _f) const
	{
		for (auto const & checkpoint : FixedCheckpoints)
			_f(*checkpoint.second.first);
	}


	void addCheckpoint(Checkpoint & _c, int _mark);
	
};

#endif // _STUDENT_HPP_