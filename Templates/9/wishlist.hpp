// (C) 2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _WISHLIST_HPP_
#define _WISHLIST_HPP_

/*****************************************************************************/

#include "messages.hpp"
#include <vector>
#include <string>
#include <set>
#include <map>
#include <unordered_map>
#include <algorithm>

typedef std::pair< std::string, int > Wish;

class Wishlist
{

public:

	Wishlist(std::string const & _name);
	Wishlist(std::string const & _name,std::initializer_list<Wish> _wishes);
	Wishlist(std::string const & _name,std::vector<Wish> & _wishes);
	Wishlist(Wishlist && _wish);
	std::string const & getOwner() const;
	void correctOwner(std::string const & _correctOwnerName);
	void addWish(std::string const & _wish, int _wishPriority);
	void addWish(Wish const & _wish);
	bool hasWish(std::string const & _wish) const;
	int getWishPriority(std::string const & _wish) const;
	int getWishesCount() const;
	void updateWishPriority(std::string const & _wish, int _newWishPriority);
	void clean();
	void operator += (const Wish & _wish);
	Wish operator[](int _index) const;
	std::vector<std::string> getWishesWithPriority(int _wishesPriority) const;
	std::vector<std::string> getMostPrioritizedWishes(int _wishesNumber) const;
	std::vector<std::string> getLeastPrioritizedWishes(int _wishesNumber) const;
	std::set<std::string> getSimilarWishes(const Wishlist & _wish) const;
	void dropWish(std::string const & _wish);
	void dropWishesWithPriorityLessThan(int _wishPriority);

private:

	std::vector<std::pair<int, std::string>> Registration;
	std::string m_name;
	std::unordered_map<std::string, Wish> Wishes;

};

inline std::string const & Wishlist::getOwner() const
{
	return m_name;
}

inline void Wishlist::correctOwner(std::string const & _correctOwnerName)
{
	if (_correctOwnerName.empty())
	{
		throw std::logic_error(Messages::OwnerNameEmpty);
	}
		
	m_name = _correctOwnerName;
}

inline bool Wishlist::hasWish(std::string const & _wish) const
{
	if (_wish.empty())
	{
		throw std::logic_error(Messages::WishNameEmpty);
	}
	
	auto it = Wishes.find(_wish);
	return	it != Wishes.end();
}

inline int Wishlist::getWishPriority(std::string const & _wish) const
{
	if (_wish.empty())
	{
		throw std::logic_error(Messages::WishNameEmpty);
	}
		
	if (!hasWish(_wish))
	{
		throw std::logic_error(Messages::WishDoesNotExist);
	}
		
	auto it = Wishes.find(_wish);
	return it->second.second;
}

inline int Wishlist::getWishesCount() const
{
	if (Wishes.empty())
		return 0;
	else
		return Wishes.size();
}

inline void Wishlist::clean()
{
	Wishes.clear();
	Registration.clear();
}



#endif // _WISHLIST_HPP_
