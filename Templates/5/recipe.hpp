// (C) 2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _RECIPE_HPP_
#define _RECIPE_HPP_

#include <string>
#include <map>
#include <vector>
#include "messages.hpp"

class Recipe
{
	std::string Author;

	std::string Name;

	std::string Desc;

	std::vector<std::string> Steps;

	std::map<std::string, int> Ing;

public:

	Recipe( 
		std::string const & _name,
		std::string const & _description,
		std::string const & _author
	);

	Recipe(Recipe & _rececipe) = delete;

	Recipe(Recipe && _rececipe) = delete;

	Recipe & operator = (Recipe && _rececipe) = delete;

	Recipe & operator = (Recipe & _rececipe) = delete;

	~Recipe() = default;

	void addIngredient(std::string const & _ing, int _w);

	void modifyIngredient(std::string const & _ing, int _newW);

	int getIngredientValue(std::string const & _ing) const;

	std::string	const & getAuthor() const
	{
		return Author;
	}

	std::string const & getName() const
	{
		return Name;
	}

	std::string const & getDescription() const
	{
		return Desc;
	}

	bool operator == (Recipe const & _rec) const
	{
		return (Author == _rec.Author && Desc == _rec.Desc && Name == _rec.Name && Ing == _rec.Ing && Steps == _rec.Steps);
	}

	bool operator != (Recipe const & _rec) const
	{
		return !(*this == _rec);
	}

	std::map<std::string, int>::const_iterator beginIngredients() const
	{
		return Ing.cbegin();
	}

	std::map<std::string, int>::const_iterator endIngredients() const
	{
		return Ing.cend();
	}

	void addCookStep(std::string const & _step)
	{
		if (_step.empty()) throw std::logic_error(Messages::EmptyCookStep);
		Steps.push_back(_step);
	}
	
	int getIngredientsCount() const
	{
		return Ing.size();
	}
	
	int getCookStepsCount() const
	{
		return Steps.size();
	}
	
	std::string const & getCookStep(int _i) const
	{
		if (_i < 0 || _i >= Steps.size()) throw std::logic_error(Messages::IndexOutOfRange);
		return Steps[_i];
	}

	bool hasIngredient(std::string const & _ing) const
	{
		return Ing.find(_ing) != Ing.end();
	}
};

#endif // _RECIPE_HPP_
