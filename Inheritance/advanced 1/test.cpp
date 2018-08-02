#include "testslib.hpp"
#include "flowering_houseplant.hpp"
#include "foliar_houseplant.hpp"
#include "fruiting_houseplant.hpp"
#include "artificial_houseplant.hpp"
#include "room.hpp"
#include "message.hpp"
#include "house_owner.hpp"

DECLARE_OOP_TEST(test_foliar_houseplant)
{
	//тестируем на пустое имя
	ASSERT_THROWS(
		FoliarHouseplant fh("",1,1),
		Messages::EmptyHouseplantName
	);
	//тестируем на неправильный период полива
	ASSERT_THROWS(
		FoliarHouseplant fh("Plant",0,1),
		Messages::InvalidWateringNumber
	);
	//тестируем на отрицательную высоту
	ASSERT_THROWS(
		FoliarHouseplant fh("Plant",1,-1),
		Messages::InvalidBeginningHeight
	);

	//моделируем ситуацию идеального полива : соблюдение ежедневного равномерного полива
	//растений в конце должно быть 2
	{
		Room r;
		PlantOwner po(&r);
		FoliarHouseplant fh("Plant", 1, 245);

		fh.setPlantOwner(&po);
		r.addHouseplant(std::make_unique<FoliarHouseplant>(fh));

		assert(r.сountHouseplants() == 1);
		for (int i = 0; i < 6; i++)
		{
			fh.daySkip();
			fh.water();
		}
		assert(r.сountHouseplants() == 2);
	}
	
	//моделируем ситуацию с допустимым поливом, когда растение может быть поделено
	//будем поливать его черезмерно, но в итоге должны получить 2 растения
	{
		Room r;
		PlantOwner po(&r);
		FoliarHouseplant fh("Plant", 2, 245);

		fh.setPlantOwner(&po);
		r.addHouseplant(std::make_unique<FoliarHouseplant>(fh));

		assert(r.сountHouseplants() == 1);
		for (int i = 0; i < 6; i++)
		{
			fh.daySkip();
			fh.water();
		}
		assert(r.сountHouseplants() == 2);
	}

	//ситуация с плохим поливом
	//несоблюдаем норму полива
	//растение должно остатося одно и не вырости
	{
		Room r;
		PlantOwner po(&r);
		FoliarHouseplant fh("Plant", 3, 245);

		fh.setPlantOwner(&po);
		r.addHouseplant(std::make_unique<FoliarHouseplant>(fh));

		assert(r.сountHouseplants() == 1);
		for (int i = 0; i < 6; i++)
		{
			fh.daySkip();
			fh.water();
		}
		assert(r.сountHouseplants() == 1);
	}
}

DECLARE_OOP_TEST(test_artificial_houseplant)
{
	//проверяем на пустое имя
	ASSERT_THROWS(
		ArtificialHouseplant ah("", 7),
		Messages::EmptyHouseplantName
	);
	//проверяем на неправильный период полива
	ASSERT_THROWS(
		ArtificialHouseplant ah("Plant", 0),
		Messages::InvalidWateringNumber
	);
	Room r;
	ArtificialHouseplant ah("Plant", 2);

	r.addHouseplant(std::make_unique<ArtificialHouseplant>(ah));
	//пытаемся полить исскуственное растение : должны получить ошибку на консоль
	ah.water();
}

DECLARE_OOP_TEST(test_fruiting_houseplant_functional)
{
	//проверяем неверные данные конструктора :
	// - пустое имя
	// - неправильный период полива
	// - неправильный период плодоношения
	// - пустое имя плода
	{
		ASSERT_THROWS(
			FruitingHouseplant f1("", "lemon", 0, 0),
			Messages::EmptyHouseplantName
		);
		ASSERT_THROWS(
			FruitingHouseplant f2("lemon tree", "lemon", 0, 2),
			Messages::InvalidWateringNumber
		);
		ASSERT_THROWS(
			FruitingHouseplant f3("lemon tree", "lemon", 1, 0),
			Messages::InvalidFruitingPeriod
		);
		ASSERT_THROWS(
			FruitingHouseplant f4("lemon tree", "", 2, 2),
			Messages::EmptyFruitName
		);
	}

	//создаем лимон
	//моделируем ситуацию, когда при правильном поливе
	//должен созреть плод ( лимон ) и появиться сообщение на экране
	{
		Room r;
		FruitingHouseplant fh("lemon tree", "lemon", 1, 5);
		r.addHouseplant(std::make_unique<FruitingHouseplant>(fh));
		for (int i = 0; i < 7; i++)
		{
			fh.daySkip();
			fh.water();
		}
	}
	
	//моделируем ситуацию, когда полив будет неправильным
	//ожидания : плод не должен созреть
	{
		Room r;
		FruitingHouseplant fh("lemon tree", "lemon", 1, 5);
		r.addHouseplant(std::make_unique<FruitingHouseplant>(fh));
		for (int i = 0; i < 7; i++)
		{
			fh.nDaysPassed(2);
			fh.water();
		}
	}
}

DECLARE_OOP_TEST(test_flowering_houseplant_functional)
{
	//проверяем неверные данные конструктора :
	// - пустое имя
	// - неправильный период полива
	// - неправильный период цветения
	// - неправильное кол-во требуемого полива
	{
		ASSERT_THROWS(
			FloweringHouseplant fh("", 0, 0, 0),
			Messages::EmptyHouseplantName
		);
		ASSERT_THROWS(
			FloweringHouseplant fh("Flower", 0, 0, 0),
			Messages::InvalidWateringNumber
		);
		ASSERT_THROWS(
			FloweringHouseplant fh("Flower", 1, 0, 2),
			Messages::InvalidBloomingDuration
		);
		ASSERT_THROWS(
			FloweringHouseplant fh("Flower", 1, 1, 0),
			Messages::InvalidNeedWatering
		);
	}

	//моделируем ситуацию, когда полив сделан правильно
	//и должно растение покрепчать
	{
		Room r;
		FloweringHouseplant fl("Flower", 1, 5, 5);
		r.addHouseplant(std::make_unique<FloweringHouseplant>(fl));
		for (int i = 0; i < 10; i++)
		{
			fl.daySkip();
			fl.water();
		}
		for (int i = 0; i < 10; i++)
		{
			fl.nDaysPassed(2);
			fl.water();
		}
	}

	//моделируем ситуацию плохо полива
	//поливаем растение 9 дней , делаем задержку на 2 дня и поливаем обратно
	//ожидаемый результат : ничего не будет выведено на экран
	{
		Room r;
		FloweringHouseplant fl("Flower", 1, 5, 5);

		r.addHouseplant(std::make_unique<FloweringHouseplant>(fl));

		for (int i = 0; i < 9; i++)
		{
			fl.daySkip();
			fl.water();
		}

		fl.nDaysPassed(2);
		fl.water();
	}
}