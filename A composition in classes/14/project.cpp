// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "project.hpp"
#include "messages.hpp"
#include "document.hpp"

int Project::getStandardsSize() const
{
	return Standards.size();
}

int Project::getDocumentsSize() const
{
	return Documents.size();
}

std::string const & Project::getProjectName() const
{
	return ProjectName;
}

void Project::addStandard(std::string const & _standart)
{
	Standards.insert(_standart);
}

bool Project::hasStandard(std::string const & _standart) const
{
	return Standards.find(_standart) != Standards.end();
}

bool Project::hasDocument(std::string const & _document) const
{
	return Documents.find(_document) != Documents.end();
}

Document const & Project::getDocument(std::string const & _document) const
{
	return *Documents.find(_document)->second;
}

Project::Project(std::string const & _projectName)
	: ProjectName(_projectName)
{}

Project::~Project() = default;

std::set<std::string> const & Project::getStandards() const
{
	return Standards;
}

std::map<std::string, std::unique_ptr<Document>> const & Project::getDocuments() const
{
	return Documents;
}

void Project::addDocument(std::string const & _document, std::string const & _standard)
{
	Documents.insert(std::make_pair(_document, std::make_unique<Document>(_document,_standard)));
}