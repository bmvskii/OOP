// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _TREEITEM_HPP_
#define _TREEITEM_HPP_

//-----------------------------------------------------------------------------

#include <string>

//-----------------------------------------------------------------------------

class TreeItem
{
	std::string NameOfNode;
	bool visibleFlag;

public:

	TreeItem(std::string const & _NameOfNode);
	virtual ~TreeItem();

	virtual int getNodesAmount() const = 0;
	virtual TreeItem & getNode(int _index) const = 0;

	void out(std::ostream & _Stream, int _Level) const;
	std::string const & getName() const
	{
		return NameOfNode;
	}
	bool isVisible() const
	{
		return visibleFlag;
	}
	void setVisibility(bool _s)
	{
		visibleFlag = _s;
	}
};

#endif // _TREEITEM_HPP_