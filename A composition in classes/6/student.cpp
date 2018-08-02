// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "student.hpp"
#include "messages.hpp"
#include "checkpoint.hpp"

Student::Student(std::string const & _FullName) : FullName(_FullName)
{}

Student::~Student() = default;

void Student::addCheckpoint(Checkpoint & _c, int _mark)
{
	if (FixedCheckpoints.find(_c.getName()) != FixedCheckpoints.end())
		FixedCheckpoints.find(_c.getName())->second.second = _mark;
	else
		FixedCheckpoints.insert(std::make_pair(_c.getName(),std::make_pair(&_c, _mark)));
}