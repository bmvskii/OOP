// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "parenttreeitem.hpp"

//-----------------------------------------------------------------------------

ParentTreeItem::ParentTreeItem(
	std::string const & _NameOfNode,
	bool _IsHide
)
	: TreeItem(_NameOfNode)
	, isHide(_IsHide)
{}

//-----------------------------------------------------------------------------
