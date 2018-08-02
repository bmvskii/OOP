// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _PROJECT_HPP_
#define _PROJECT_HPP_

/*****************************************************************************/
#include <string>
#include <set>
#include <map>
#include <functional>
#include <memory>

class Document;

class Project
{
	std::string ProjectName;
	std::set<std::string> Standards;
	std::map<std::string, std::unique_ptr<Document>> Documents;

public:

	Project(std::string const & _projectName);
	~Project();
	std::string const & getProjectName() const;
	void addStandard(std::string const & _Standard);
	bool hasStandard(std::string const & _Standard) const;
	void addDocument(std::string const & _document, std::string const & _standard);
	Document const & getDocument(std::string const & _document) const;
	bool hasDocument(std::string const & _document) const;
	std::set<std::string> const & getStandards() const;
	std::map<std::string, std::unique_ptr<Document>> const & getDocuments() const;
	int getStandardsSize() const;
	int getDocumentsSize() const;
};



#endif // _PROJECT_HPP_
