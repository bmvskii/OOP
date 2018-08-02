// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _LEAFTREEITEM_HPP_
#define _LEAFTREEITEM_HPP_

//-----------------------------------------------------------------------------

#include "treeitem.hpp"
#include "messages.hpp"

//-----------------------------------------------------------------------------

class LeafTreeItem
	: public TreeItem
{
public:
	LeafTreeItem(std::string const & _NameOfNode);
	~LeafTreeItem() = default;

	TreeItem & getNode(int _Index) const override 
	{
		throw std::logic_error(Messages::TreeItemHasNotChildren);
	}
	int getNodesAmount() const override 
	{
		return 0;
	}
};

//-----------------------------------------------------------------------------

#endif // _LEAFTREEITEM_HPP_