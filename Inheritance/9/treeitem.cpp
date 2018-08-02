// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "treeitem.hpp"

//-----------------------------------------------------------------------------

TreeItem::TreeItem(std::string const & _nameOfNode)
	: NameOfNode(_nameOfNode), visibleFlag(true)
{}

//-----------------------------------------------------------------------------

TreeItem::~TreeItem() = default;

//-----------------------------------------------------------------------------

void TreeItem::out(std::ostream & _Stream, int _Level) const
{
	if (visibleFlag)
	{
		for (int i = 0; i < _Level; i++) _Stream << "\t";
		_Stream << NameOfNode << std::endl;
		for (int i = 0; i < getNodesAmount(); i++) getNode(i).out(_Stream, _Level + 1);
	}
}
//-----------------------------------------------------------------------------
