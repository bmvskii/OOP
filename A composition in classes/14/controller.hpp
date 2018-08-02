// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _CONTROLLER_HPP_
#define _CONTROLLER_HPP_

/*****************************************************************************/

#include <string>
#include <unordered_set>
#include <unordered_map>
#include <memory>

/*****************************************************************************/

class Project;

class Controller
{

/*-----------------------------------------------------------------*/

public:

/*-----------------------------------------------------------------*/

	Controller ();

	~Controller ();

	Controller ( const Controller & ) = delete;

	Controller & operator = ( const Controller & ) = delete;

/*-----------------------------------------------------------------*/

	void addProject ( std::string const & _projectName );

	int getProjectsCount () const;

	bool hasProject ( std::string const & _projectName ) const;

/*-----------------------------------------------------------------*/

	int getProjectDocumentsCount ( std::string const & _projectName ) const;

	bool
	hasProjectDocument (
			std::string const & _projectName
		,	std::string const & _documentName
	) const;

	std::string const &
	getProjectDocumentStandard (
			std::string const & _projectName
		,	std::string const & _documentName
	) const;

	void addDocumentForProject (
			std::string const & _projectName
		,	std::string const & _documentName
		,	std::string const & _standardName
	);

/*-----------------------------------------------------------------*/

	void addStandardForProject (
			std::string const & _projectName
		,	std::string const & _standardName
	);

	int getProjectStandardsCount ( std::string const & _projectName ) const;

	bool hasProjectStandard (
			std::string const & _projectName
		,	std::string const & _standardName
	) const;

/*-----------------------------------------------------------------*/

	typedef std::unordered_set< std::string > StandardNames;

	StandardNames getProjectStandardsUsed () const;

	typedef  std::unordered_set< std::string >  ProjectNames;

	ProjectNames getProjectsWithAllNeededStandardDocuments () const;

	ProjectNames getProjectsNotHavingStandardDocument ( std::string const & _standard ) const;

	std::string getMostPopularStandard () const;

/*-----------------------------------------------------------------*/

private:

/*-----------------------------------------------------------------*/
	
	std::unordered_map<std::string, std::unique_ptr<Project>> m_projects;

/*-----------------------------------------------------------------*/  

};


/*****************************************************************************/

#endif //  _CONTROLLER_HPP_
