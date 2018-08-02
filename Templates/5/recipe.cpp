// (C) 2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "recipe.hpp"
#include "messages.hpp"

Recipe::Recipe(
	std::string const & _Name,
	std::string const & _Desc,
	std::string const & _Author
)
	: Name ( _Name )
	, Desc ( _Desc )
	, Author (_Author )
{
	if (Desc.empty()) throw std::logic_error(Messages::EmptyRecipeDescription);
	if (Name.empty()) throw std::logic_error(Messages::EmptyRecipeName);
	if (Author.empty()) throw std::logic_error(Messages::EmptyRecipeAuthor);
}

void Recipe::addIngredient(std::string const & _ing, int _w)
{
	if (hasIngredient(_ing)) throw std::logic_error(Messages::DuplicateIngredient);
	if (_ing.empty()) throw std::logic_error(Messages::EmptyIngredientName);
	if (_w < 1) throw std::logic_error(Messages::IngredientValueMustBePositive);
	Ing.insert(std::make_pair(_ing, _w));
}

void Recipe::modifyIngredient(std::string const & _ing, int _newW)
{
	if (_ing.empty()) throw std::logic_error(Messages::EmptyIngredientName);
	if (_newW < 1) throw std::logic_error(Messages::IngredientValueMustBePositive);
	if (!hasIngredient(_ing)) throw std::logic_error(Messages::IngredientCannotBeFound);
	Ing.find(_ing)->second = _newW;
}

int Recipe::getIngredientValue(std::string const & _ing) const
{
	if (_ing.empty()) throw std::logic_error(Messages::EmptyIngredientName);
	if (!hasIngredient(_ing)) throw std::logic_error(Messages::IngredientCannotBeFound);
	return Ing.find(_ing)->second;
}
