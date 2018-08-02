// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "controller.hpp"
#include "messages.hpp"
#include "course.hpp"
#include "student.hpp"
#include "checkpoint.hpp"
#include <algorithm>
#include <iostream>

Controller::Controller() = default;

Controller::~Controller() = default;

void Controller::addCourse(const std::string & _courseName, ControlForm _controlForm)
{
	if (_courseName.empty()) throw std::logic_error(Messages::EmptyCourseName);
	if (Courses.find(_courseName) != Courses.end()) throw std::logic_error(Messages::DuplicateCourse);
		
	Courses.insert(std::make_pair(_courseName, std::make_unique<Course>(_courseName,_controlForm)));
}

ControlForm Controller::getCourseControlForm(const std::string & _courseName) const
{
	if (Courses.find(_courseName) == Courses.end()) throw std::logic_error(Messages::CourseCannotBeFound);
	return Courses.find(_courseName)->second->getControlForm();
}

void Controller::validateCourseCheckpoints(const std::string & _courseName) const
{
	if (Courses.find(_courseName) == Courses.end()) throw std::logic_error(Messages::CourseCannotBeFound);
	if (!Courses.find(_courseName)->second->hasCheckpoints()) throw std::logic_error(Messages::NoCheckpointsFound);
	if (Courses.find(_courseName)->second->getCheckpointSum() != 100) throw std::logic_error(Messages::CheckpointsSumMismatch);
}

void Controller::addCheckpoint(const std::string & _courseName,const std::string & _checkpointName,int _maxMark)
{
	if (_checkpointName.empty()) throw std::logic_error(Messages::EmptyCheckpointName);
	if (_maxMark < 1 || _maxMark > 100) throw std::logic_error(Messages::InvalidMarkValue);
	if (Courses.find(_courseName) == Courses.end()) throw std::logic_error(Messages::CourseCannotBeFound);
	Courses.find(_courseName)->second->addCheckpoint(std::make_unique<Checkpoint>(_checkpointName, _maxMark));
}

int Controller::getCheckpointMaxMark(const std::string & _courseName,const std::string & _checkpointName) const
{
	if (Courses.find(_courseName) == Courses.end()) throw std::logic_error(Messages::CourseCannotBeFound);
	if (!Courses.find(_courseName)->second->hasCheckpoint(_checkpointName)) throw std::logic_error(Messages::CheckpointCannotBeFound);
	return Courses.find(_courseName)->second->getCheckpoint(_checkpointName).getMark();
}

int Controller::getCheckpointMinMark( const std::string & _courseName,const std::string & _checkpointName) const
{
	if (Courses.find(_courseName) == Courses.end()) throw std::logic_error(Messages::CourseCannotBeFound);
	if (!Courses.find(_courseName)->second->hasCheckpoint(_checkpointName)) throw std::logic_error(Messages::CheckpointCannotBeFound);
	return Courses.find(_courseName)->second->getCheckpoint(_checkpointName).getMark() * 0.6;
}

void Controller::addStudent(const std::string & _fullName)
{
	if (_fullName.empty()) throw std::logic_error(Messages::EmptyStudentName);
	if (Students.find(_fullName) != Students.end()) throw std::logic_error(Messages::DuplicateStudent);
	Students.insert(std::make_pair(_fullName, std::make_unique<Student>(_fullName)));
}

void Controller::addStudentCheckpoint(const std::string & _fullName, const std::string & _courseName, const std::string & _checkpointName,int _mark)
{
	if (Courses.find(_courseName) == Courses.end()) throw std::logic_error(Messages::CourseCannotBeFound);
	if (!Courses.find(_courseName)->second->hasCheckpoint(_checkpointName)) throw std::logic_error(Messages::CheckpointCannotBeFound);
	if (Students.find(_fullName) == Students.end()) throw std::logic_error(Messages::StudentCannotBeFound);
	if (_mark < 0 || _mark > getCheckpointMaxMark(_courseName, _checkpointName))throw std::logic_error(Messages::InvalidMarkValue);
	Students.find(_fullName)->second->addCheckpoint(Courses.find(_courseName)->second->getCheckpoint(_checkpointName), _mark);
}

int Controller::getStudentCheckpointMark(const std::string & _fullName,const std::string & _courseName,const std::string & _checkpointName)
{
	if (Courses.find(_courseName) == Courses.end()) throw std::logic_error(Messages::CourseCannotBeFound);
	if (!Courses.find(_courseName)->second->hasCheckpoint(_checkpointName)) throw std::logic_error(Messages::CheckpointCannotBeFound);
	if (Students.find(_fullName) == Students.end()) throw std::logic_error(Messages::StudentCannotBeFound);

	if (Students.find(_fullName)->second->isCheckpointPassed(_checkpointName))
		return Students.find(_fullName)->second->getMark(_checkpointName);
	else 
		return 0;
}

std::vector<std::string> Controller::getStudentsPermittedForExams() const
{
	std::vector<std::string> studentsPermittedForExams;
	int result, coursesCounter, testCounter = 0;

	for (auto course = Courses.begin(); course != Courses.end(); ++course) if (course->second->getControlForm() == ControlForm::Test) testCounter++;
	for (auto student = Students.begin(); student != Students.end(); ++student)
	{
		coursesCounter = 0;
		for (auto course = Courses.begin(); course != Courses.end(); ++course)
		{
			result = 0;
			if (course->second->getControlForm() == ControlForm::Test)
				student->second->forEachCheckpoint([&](Checkpoint const & _c)
			{
				if (course->second->hasCheckpoint(_c.getName())) result += student->second->getMark(_c.getName());
			});
			if (result >= course->second->getCheckpointSum() * 0.6) coursesCounter++;
		}
		if (coursesCounter == testCounter) studentsPermittedForExams.push_back(student->first);
	};

	std::sort(studentsPermittedForExams.begin(), studentsPermittedForExams.end());
	return studentsPermittedForExams;
}

std::vector<std::string> Controller::getCoursesWithEveryonePassed() const
{
	std::vector<std::string> coursesWithEveryonePassed;
	int result, passedCounter;

	for (auto course = Courses.begin(); course != Courses.end(); ++course)
	{
		passedCounter = 0;
		for (auto student = Students.begin(); student != Students.end(); ++student)
		{
			result = 0;
			student->second->forEachCheckpoint([&](Checkpoint const & _c)
			{
				if (course->second->hasCheckpoint(_c.getName()))
					result += student->second->getMark(_c.getName());
			}
			);
			if (result >= course->second->getCheckpointSum() * 0.6) passedCounter++;
		}
		if (passedCounter == Students.size()) coursesWithEveryonePassed.push_back(course->first);
	}

	std::sort(coursesWithEveryonePassed.begin(), coursesWithEveryonePassed.end());
	return coursesWithEveryonePassed;
}

std::vector<std::pair<std::string, double>> Controller::getAverageScoreByCourse() const
{
	int passedCounter;
	std::vector<std::pair<std::string, double>> averageScoreByCourse;
	double result;

	for (auto course = Courses.begin(); course != Courses.end(); ++course)
	{
		passedCounter = 0;
		result = 0;
		for (auto student = Students.begin(); student != Students.end(); ++student)
		{
			student->second->forEachCheckpoint([&](Checkpoint const & _c)
			{
				if (course->second->hasCheckpoint(_c.getName())) result += student->second->getMark(_c.getName());
			}
			);
		}
		averageScoreByCourse.push_back(std::make_pair(course->first, result / Students.size()));
	}

	std::sort(averageScoreByCourse.begin(),averageScoreByCourse.end(),[&](std::pair<std::string,double> const & left, std::pair<std::string,double> const & right)
	{
		return left.first < right.first;
	});

	return averageScoreByCourse;
}

std::string Controller::getStudentWithBestAverageScore() const
{
	std::string studentWithBestAverageScore;
	int result;
	double results,max = 0;

	for (auto student = Students.begin(); student != Students.end(); ++student)
	{
		results = 0;
		for (auto course = Courses.begin(); course != Courses.end(); ++course)
		{
			result = 0;
			student->second->forEachCheckpoint([&](Checkpoint const & _c)
			{
				if (course->second->hasCheckpoint(_c.getName())) result += student->second->getMark(_c.getName());
			});
			results += result;
		}
		results /= Courses.size();
		if (results >= max)
		{
			max = results;
			studentWithBestAverageScore = student->first; 
		}
	}

	return studentWithBestAverageScore;
}