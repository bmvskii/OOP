// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "coffeemachine.hpp"

#include <stdexcept>

/*****************************************************************************/

CoffeeMachine::CoffeeMachine(int _maxBeansNumber,int _maxWaterLiters,int _maxCoffeeCups)
{
	//проверяем входные данные
	if (_maxBeansNumber < 1 || _maxCoffeeCups < 1 || _maxWaterLiters < 1) throw std::logic_error("Incorrect initial parameters");
	
	//инициализируем переменные
	maxBeansNumber = _maxBeansNumber;
	maxCoffeeCups = _maxCoffeeCups;
	maxWaterLiters = _maxWaterLiters;
	availableBeansNumber = availableWaterLiters = 0;
	availableCoffeeCups = _maxCoffeeCups;
}

/*****************************************************************************/

int CoffeeMachine::loadBeans()
{
	//получаем разницу и добавляем зерен
	int diff = maxBeansNumber - availableBeansNumber;
	availableBeansNumber = maxBeansNumber;
	return diff;
}

/*****************************************************************************/

int CoffeeMachine::loadWater()
{
	//получаем разницу и добавляем воды
	int diff = maxWaterLiters - availableWaterLiters;
	availableWaterLiters = maxWaterLiters;
	return diff;
}

/*****************************************************************************/

void CoffeeMachine::cleanWaste()
{
	//очищаем бачек для отходов
	availableCoffeeCups = maxCoffeeCups;
}

/*****************************************************************************/

bool CoffeeMachine::makeCoffee(Recipe _coffeeRecipe, Strength _coffeeStrength)
{
	//если нет места для отходов, то возвращаем false
	if (availableCoffeeCups == 0) return false;
		
	switch (_coffeeRecipe)
	{
		//проверяем ресурсы для еспрессо
	case CoffeeMachine::Espresso:
		if (availableWaterLiters - WATER_FOR_ESPRESSO < 0) return false;
		else availableWaterLiters -= WATER_FOR_ESPRESSO;
		break;
		//проверяем ресурсы для американо
	case CoffeeMachine::Americano:
		if (availableWaterLiters - WATER_FOR_AMERICANO < 0) return false;
		else availableWaterLiters -= WATER_FOR_AMERICANO;
		break;
	default:
		break;
	}

	switch (_coffeeStrength)
	{
		//проверяем кол-во зерен для слабой крепости
	case CoffeeMachine::Light:
		if (availableBeansNumber - BEANS_FOR_LIGHT < 0) return false;
		else availableBeansNumber -= BEANS_FOR_LIGHT;
		break;

		//проверяем кол-во зерен для средней крепости
	case CoffeeMachine::Medium:
		if (availableBeansNumber - BEANS_FOR_MEDIUM < 0) return false;
		else availableBeansNumber -= BEANS_FOR_MEDIUM;
		break;

		//проверяем кол-во зерен для сильной крепости
	case CoffeeMachine::Strong:
		if (availableBeansNumber - BEANS_FOR_STRONG < 0) return false;
		else availableBeansNumber -= BEANS_FOR_STRONG;
		break;
	default:
		break;
	}

	//уменьшаем кол-во возможных чашек кофе
	availableCoffeeCups--;
	return true;
}

/*****************************************************************************/

void CoffeeMachine::washMachine()
{
	//проверяем кол-во воды для мытья
	if (availableWaterLiters - WATER_FOR_WASHING > 0) availableWaterLiters -= WATER_FOR_WASHING;
	else availableWaterLiters = 0;
}

/*****************************************************************************/

CoffeeMachine::operator bool () const
{
	//проверяем можно ли сделать чашку кофе любого вида и любой крепости
	if (availableCoffeeCups <= 0 || availableBeansNumber < 12 || availableWaterLiters < 200) return false;
	return true;
}

/*****************************************************************************/