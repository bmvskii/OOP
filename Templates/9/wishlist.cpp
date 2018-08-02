// (C) 2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "wishlist.hpp"
#include <iostream>
#include <functional>

void Wishlist::addWish(std::string const & _wish, int _prior)
{
	if (_wish.empty())
	{
		throw std::logic_error(Messages::WishNameEmpty);
	}

	if (hasWish(_wish))
	{
		throw std::logic_error(Messages::WishAlreadyExists);
	}

	if (_prior < 0)
	{
		throw std::logic_error(Messages::NegativePriority);
	}

	Wishes.insert(std::make_pair(_wish, std::make_pair(_wish, _prior)));
	Registration.push_back(std::make_pair(_prior, _wish));
}

void Wishlist::addWish(Wish const & _wish)
{
	if (_wish.first.empty())
	{
		throw std::logic_error(Messages::WishNameEmpty);
	}

	if (hasWish(_wish.first))
	{
		throw std::logic_error(Messages::WishAlreadyExists);
	}

	if (_wish.second < 0)
	{
		throw std::logic_error(Messages::NegativePriority);
	}

	Wishes.insert(std::make_pair(_wish.first, Wish(_wish.first, _wish.second)));
	Registration.push_back(std::make_pair(_wish.second, _wish.first));
}

Wishlist::Wishlist(std::string const & _name)
{
	m_name = _name;

	if (m_name.empty())
	{
		throw std::logic_error(Messages::OwnerNameEmpty);
	}
}

void Wishlist::updateWishPriority(std::string const & _wish, int _newWishPriority)
{
	if (_wish.empty())
	{
		throw std::logic_error(Messages::WishNameEmpty);
	}

	if (!hasWish(_wish))
	{
		throw std::logic_error(Messages::WishDoesNotExist);
	}

	if (_newWishPriority < 0)
	{
		throw std::logic_error(Messages::NegativePriority);
	}

	auto it = Wishes.find(_wish);
	it->second.second = _newWishPriority;

	for (int i = 0; i < Registration.size(); i++)
	{
		if (Registration[i].second == _wish)
		{
			Registration[i].first = _newWishPriority;
			break;
		}
	}
}

Wish Wishlist::operator[](int _index) const
{
	if (_index < 0 || _index >= Wishes.size())
	{
		throw std::out_of_range("");
	}

	std::pair<int, std::string > p = Registration[_index];
	return Wish(p.second, p.first);
}

Wishlist::Wishlist(std::string const & _name, std::initializer_list<Wish> _wishes)
{
	m_name = _name;

	if (m_name.empty())
	{
		throw std::logic_error(Messages::OwnerNameEmpty);
	}
		
	for (auto wish : _wishes)
	{
		if (wish.first.empty())
		{
			throw std::logic_error(Messages::WishNameEmpty);
		}
			
		if (wish.second < 0)
		{
			throw std::logic_error(Messages::NegativePriority);
		}
		
		if (hasWish(wish.first))
		{
			throw std::logic_error(Messages::WishAlreadyExists);
		}
			
		Wishes.insert(std::make_pair(wish.first, wish));
	}
}

Wishlist::Wishlist(std::string const & _name, std::vector<Wish> & _wishes)
{
	m_name = _name;

	if (m_name.empty())
	{
		throw std::logic_error(Messages::OwnerNameEmpty);
	}
		
	for (auto wish = _wishes.begin(); wish != _wishes.end(); ++wish)
	{
		Wishes.insert(std::make_pair(wish->first, *wish));
		Registration.push_back(std::make_pair(wish->second, wish->first));
	}
}

Wishlist::Wishlist(Wishlist && _wish)
{
	std::swap(m_name, _wish.m_name);
	Wishes = std::move(_wish.Wishes);
	Registration = std::move(_wish.Registration);
}

void Wishlist::operator+=(const Wish & _wish)
{
	if (_wish.first.empty())
	{
		throw std::logic_error(Messages::WishNameEmpty);
	}
		
	if (_wish.second < 0)
	{
		throw std::logic_error(Messages::NegativePriority);
	}
		
	if (hasWish(_wish.first))
	{
		throw std::logic_error(Messages::WishAlreadyExists);
	}

	Wishes.insert(std::make_pair(_wish.first, _wish));
	Registration.push_back(std::make_pair(_wish.second, _wish.first));
}

std::vector<std::string> Wishlist::getMostPrioritizedWishes(int _number) const
{
	if (_number < 1)
	{
		throw std::logic_error(Messages::NonPositiveAmount);
	}
	
	std::vector<std::string> result;
	std::set<int,std::greater<int>> temp;

	for (int i = 0; i < Registration.size(); i++)
	{
		temp.insert(Registration[i].first);
	}
		
	int k = 0;
	for (auto it = temp.begin(); it != temp.end(); ++it)
	{
		if (k == _number)
		{
			break;
		}
		
		for (int j = 0; j < Registration.size(); j++)
		{
			if (*it == Registration[j].first)
			{
				result.push_back(Registration[j].second);
				k++;
			}

			if (k == _number)
			{
				break;
			}
		}
	}
	return result;
}

std::vector<std::string> Wishlist::getLeastPrioritizedWishes(int _number) const
{
	if (_number < 1)
	{
		throw std::logic_error(Messages::NonPositiveAmount);
	}
		
	std::vector<std::string> result;
	std::set<int> temp;

	for (int i = 0; i < Registration.size(); i++)
	{
		temp.insert(Registration[i].first);
	}

	int k = 0;
	for (auto it = temp.begin(); it != temp.end(); ++it)
	{
		if (k == _number)
		{
			break;
		}
			
		for (int j = 0; j < Registration.size(); j++)
		{
			if (*it == Registration[j].first)
			{
				result.push_back(Registration[j].second);
				k++;
			}
			if (k == _number)
			{
				break;
			}
		}
	}

	return result;
}

std::set<std::string> Wishlist::getSimilarWishes(const Wishlist & _wish) const
{
	std::set<std::string> result;

	for (auto it1 = Wishes.begin(); it1 != Wishes.end(); ++it1)
	{
		for (auto it2 = _wish.Wishes.begin(); it2 != _wish.Wishes.end(); ++it2)
		{
			if (it1->first == it2->first)
			{
				result.insert(it1->first);
			}
		}
	}
		
	return result;
}

void Wishlist::dropWish(std::string const & _wish)
{
	if (_wish.empty())
	{
		throw std::logic_error(Messages::WishNameEmpty);
	}
		
	if (!hasWish(_wish))
	{
		throw std::logic_error(Messages::WishDoesNotExist);
	}
	
	for (auto it = Registration.begin(); it != Registration.end(); it++)
		if ((*it).second == _wish)
		{
			Registration.erase(it);
			break;
		}
	Wishes.erase(_wish);
}

void Wishlist::dropWishesWithPriorityLessThan(int _prior)
{
	int k = 0;
	for (int i = k; i < Registration.size(); i++)
	{
		if (Registration[i].first < _prior)
		{
			Wishes.erase(Registration[i].second);
			Registration.erase(Registration.begin() + i);
			i = k;
		}
	}

	//если остается 1 элемент, то удаляем его т.к. его не замечает чего-то
	if (Registration.size() == 1 && Registration[0].first < _prior)
	{
		Wishes.erase(Registration[0].second);
		Registration.erase(Registration.begin());
		return;
	}
}

std::vector<std::string> Wishlist::getWishesWithPriority(int _prior) const
{
	if (_prior < 0)
	{
		throw std::logic_error(Messages::NegativePriority);
	}
		
	std::vector<std::string> result;

	for (auto wish = Registration.begin(); wish != Registration.end(); ++wish)
	{
		if (wish->first == _prior)
		{
			result.push_back(wish->second);
		}
	}
			
	return result;
}