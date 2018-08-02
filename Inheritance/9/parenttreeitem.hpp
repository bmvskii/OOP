// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _PARENTTREEITEM_HPP_
#define _PARENTTREEITEM_HPP_

//-----------------------------------------------------------------------------

#include "treeitem.hpp"
#include <memory>
#include <vector>

#include "messages.hpp"
//-----------------------------------------------------------------------------

class ParentTreeItem
	: public TreeItem
{
	std::vector<std::unique_ptr<TreeItem> > Nodes;
	bool isHide;
public:

	ParentTreeItem(std::string const & _NameOfNode,bool _IsHide = true);
	~ParentTreeItem() = default;

	TreeItem & getNode(int _Index) const override
	{
		if (isHide)
			return *Nodes[_Index];
		else
			throw std::logic_error(Messages::TreeItemHasNotChildren);
	}
	int getNodesAmount() const override
	{
		return isHide ? Nodes.size() : 0;
	}
	void addNode(std::unique_ptr<TreeItem>_Node)
	{
		Nodes.push_back(std::move(_Node));
	}
	void setHide(bool _State)
	{
		isHide = _State;
	}
	bool isHidden() const
	{
		return isHide;
	}
};


#endif // _PARENTTREEITEM_HPP_