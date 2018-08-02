// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "controller.hpp"
#include "leaftreeitem.hpp"
#include "treeitem.hpp"
#include "parenttreeitem.hpp"
#include "messages.hpp"

//-----------------------------------------------------------------------------

Controller::Controller() = default;

//-----------------------------------------------------------------------------

Controller::~Controller() = default;

//-----------------------------------------------------------------------------

void Controller::startParentNode(std::string const & _text)
{
	if (_text.empty()) throw std::logic_error(Messages::EmptyDescriptionText);

	auto node = std::make_unique<ParentTreeItem>(_text);
	ParentTreeItem * pItem = node.get();
	if (currentTreeNode.empty()) Roots.push_back(std::move(node));
	else currentTreeNode.back()->addNode(std::move(node));
	
	currentTreeNode.push_back(pItem);
}

//-----------------------------------------------------------------------------

void Controller::addLeafNode(std::string const & _text)
{
	if (_text.empty()) throw std::logic_error(Messages::EmptyDescriptionText);

	auto node = std::make_unique<LeafTreeItem>(_text);
	if (currentTreeNode.empty()) Roots.push_back(std::move(node));
	else currentTreeNode.back()->addNode(std::move(node));
}

//-----------------------------------------------------------------------------

void Controller::endParentNode()
{
	if (currentTreeNode.empty()) throw std::logic_error(Messages::DidNotOpenParentPreviously);
	currentTreeNode.pop_back();
}

//-----------------------------------------------------------------------------

std::string Controller::getNodeDescription(NodePath const & _path) const
{
	return getTreeNode(_path)->getName();
}

//-----------------------------------------------------------------------------
int Controller::getNodeChildrenCount(NodePath const & _path) const
{
	return getTreeNode(_path)->getNodesAmount();
}

//-----------------------------------------------------------------------------
void Controller::makeInvisible(NodePath const & _path)
{
	getTreeNode(_path)->setVisibility(false);
}

//-----------------------------------------------------------------------------

void Controller::makeVisible(NodePath const & _path)
{
	getTreeNode(_path)->setVisibility(true);
}

//-----------------------------------------------------------------------------

void Controller::expand(NodePath const & _path)
{
	if (dynamic_cast<ParentTreeItem *>(getTreeNode(_path))) dynamic_cast<ParentTreeItem *>(getTreeNode(_path))->setHide(true);
}

//-----------------------------------------------------------------------------

void Controller::collapse(NodePath const & _path)
{
	if (dynamic_cast<ParentTreeItem *>(getTreeNode(_path))) dynamic_cast<ParentTreeItem *>(getTreeNode(_path))->setHide(false);
}

//-----------------------------------------------------------------------------

bool Controller::isVisible(NodePath const & _path) const
{
	return getTreeNode(_path)->isVisible();
}

//-----------------------------------------------------------------------------

bool Controller::isExpanded(NodePath const & _path) const
{
	if (dynamic_cast<ParentTreeItem *>(getTreeNode(_path))) return dynamic_cast<ParentTreeItem *>(getTreeNode(_path))->isHidden();
	return false;
}

//-----------------------------------------------------------------------------

bool Controller::isLeaf(NodePath const & _path) const
{
	return dynamic_cast<LeafTreeItem *>(getTreeNode(_path)) != nullptr;
}

//-----------------------------------------------------------------------------

void Controller::show(std::ostream & _o)
{
	for (auto node = Roots.begin(); node != Roots.end(); node++) node->get()->out(_o, 0);
}

//-----------------------------------------------------------------------------

TreeItem * Controller::getTreeNode(NodePath const & _path) const
{
	if (_path.getIndexAtLevel(0) <= 0 || Roots.size() < _path.getIndexAtLevel(0)) throw std::logic_error(Messages::NodePathUnresolved);
	auto node = Roots.at(_path.getIndexAtLevel(0) - 1).get();
	for (int i = 1; i < _path.getLevelsCount(); i++)
	{
		if (node->getNodesAmount() < _path.getIndexAtLevel(i) ||
			_path.getIndexAtLevel(i) <= 0) throw std::logic_error(Messages::NodePathUnresolved);
		node = &node->getNode(_path.getIndexAtLevel(i) - 1);
	}
	return node;
}

//-----------------------------------------------------------------------------