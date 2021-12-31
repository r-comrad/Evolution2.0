#include "map.h"

void Map::check()
{
	//int ss1 = 0;
	//for (sint_16 i = 0; i < mField.size(); ++i)
	//{
	//	for (sint_16 j = 0; j < mField[0].size(); ++j)
	//	{
	//		if (mField[i][j]->getType() == Object::ObjectType::FOOD)
	//		{
	//			ss1++;
	//		}
	//	}
	//}

	//if (ss1 != FOOD_START_COUNT || mFoodtCounter != FOOD_START_COUNT)
	//{
	//	std::cout << "error count\n";
	//}

	//ss1 = 0;
	//for (sint_16 i = 0; i < mField.size(); ++i)
	//{
	//	for (sint_16 j = 0; j < mField[0].size(); ++j)
	//	{
	//		if (mField[i][j]->getType() == Object::ObjectType::POISON)
	//		{
	//			ss1++;
	//		}
	//	}
	//}

	//if (ss1 != POISON_START_COUNT || mPoisonCounter != POISON_START_COUNT)
	//{
	//	std::cout << "error count\n";
	//}

//	ss1 = 0;
//	for (sint_16 i = 0; i < mField.size(); ++i)
//	{
//		for (sint_16 j = 0; j < mField[0].size(); ++j)
//		{
//			if (mField[i][j]->getType() == Object::ObjectType::POISON)
//			{
//				ss1++;
//			}
//		}
//	}
//
//	if (ss1 != WALL_START_COUNT + mField.size() * 2+ mField[0].size() * 2 - 4)
//	{
//		std::cout << "error count\n";
//	}
}

Map::Map(sint_16 aN, sint_16 aM) :
	mField(aN + 2, std::vector<Object*>(aM + 2, NULL)),
	mFoodtCounter		(0),
	mPoisonCounter		(0),
	mWallCounter		(0),
	mPlantBalanceChange	(0)
{
	for (auto& i : mField)
	{
		for (auto& j : i)
		{
			j = new Object(Object::ObjectType::VOID);
		}
	}

	for (sint_16 i = 0; i < mField.size(); ++i)
	{
		setNewObject(Object::ObjectType::WALL, Pair<sint_16>(i, 0));
		setNewObject(Object::ObjectType::WALL, Pair<sint_16>(i, mField[0].size() - 1));
	}

	for (sint_16 i = 0; i < mField[0].size(); ++i)
	{
		setNewObject(Object::ObjectType::WALL, Pair<sint_16>(0, i));
		setNewObject(Object::ObjectType::WALL, Pair<sint_16>(mField.size() - 1, i));
	}

	//setNewObject(Object::ObjectType::FOOD, Pair<sint_16>(10, 10));
	//setNewObject(Object::ObjectType::FOOD, Pair<sint_16>(20, 10));
	//setNewObject(Object::ObjectType::FOOD, Pair<sint_16>(30, 10));

	//setNewObject(Object::ObjectType::POISON, Pair<sint_16>(10, 17));
	//setNewObject(Object::ObjectType::POISON, Pair<sint_16>(20, 17));
	//setNewObject(Object::ObjectType::POISON, Pair<sint_16>(30, 17));
	//return;

	regenerateField();
	createObjects(BOTS_START_COUNT, Object::ObjectType::BOT);
	std::vector <Pair<sint_16>> temp = getObjectsCoordinates(Object::ObjectType::BOT);
	for (auto& i : temp) mBotsCoord.push(i);

	//mFoodCoord = getObjectsCoordinates(Object::ObjectType::FOOD);
	//mPoisonCoord = getObjectsCoordinates(Object::ObjectType::POISON);
}

const std::vector<std::vector<Object*>>&
Map::getPresentation()
{
	return mField;
}

void
Map::setNewObject
(
	Object::ObjectType aType,
	Pair<sint_16> aCoord
)
{
	switch (aType)
	{
	case Object::VOID:
		setExictingObject (new Object(Object::ObjectType::VOID), aCoord);
		break;
	case Object::BOT:
		setExictingObject(new Bot(), aCoord);
		break;
	case Object::FOOD:
		setExictingObject(new Object(Object::ObjectType::FOOD), aCoord);
		break;
	case Object::POISON:
		setExictingObject(new Object(Object::ObjectType::POISON), aCoord);
		break;
	case Object::WALL:
		setExictingObject(new Object(Object::ObjectType::WALL), aCoord);
		break;
	default:
		setExictingObject(new Object(Object::ObjectType::NUN), aCoord);
		break;
	}
}

void
Map::setExictingObject
(
	Object* aObjectPtr,
	Pair<sint_16> aCoord
)
{
	delete(mField[aCoord.x][aCoord.y]);
	mField[aCoord.x][aCoord.y] = aObjectPtr;
}

bool
Map::trySetNewObject
(
	Object::ObjectType aType,
	Pair<sint_16> aCoord
)
{
	//if (mField[aCoord.x][aCoord.y]->getType() != aType)
	if (mField[aCoord.x][aCoord.y]->getType() == Object::ObjectType::VOID)
	{
		setNewObject(aType, aCoord);
		return true;
	}
	return false;
}

void 
Map::createObjects
(
	sint_16 aLimit,
	Object::ObjectType aType
)
{
	for (sint_16 cnt = 0; cnt < aLimit; )
	{
		Pair<sint_16> p(rand() % mField.size(), rand() % mField[0].size());
		if (trySetNewObject(aType, p)) ++cnt;
	}
}

void
Map::makeTurn()
{
	check();

	uint_16 count = mBotsCoord.size();
	for (uint_16 i = 0; i < count; ++i)
	{
		//std::cout << "  i : " << int(i) << "\n";
		Pair<sint_16> cur = mBotsCoord.front();
		mBotsCoord.pop();

		Bot* botPtr = static_cast<Bot*>(mField[cur.x][cur.y]);
		Object::ObjectType argument = Object::ObjectType::VOID;
		for (uint_8 j = 0; j < 8; ++j)
		{
			//std::cout << "     j : " << int(j) << "\n";
			Bot::Action action = botPtr->makeAction(argument);

			const Direction& dir = botPtr->getDirection();
			Pair<sint_16> next = dir.shiftPair(cur);
			Object::ObjectType type = mField[next.x][next.y]->getType();
			switch (action)
			{
			case Bot::Action::NUN:
				std::cout << "bot action error\n";
				break;
			case Bot::Action::VOID:
				break;
			case Bot::Action::GO:
				if (type == Object::ObjectType::FOOD)
				{
					botPtr->feed(0.5);
					destroyPlant();
				}
				else if (type == Object::ObjectType::POISON)
				{
					botPtr->poison(0.5);
					--mPoisonCounter;
				}

				if (type != Object::ObjectType::WALL && type != Object::ObjectType::BOT)
				{
					setExictingObject(botPtr, next);
					mField[cur.x][cur.y] = new Object(Object::ObjectType::VOID);
					cur = next;
				}
				j = 100;
				break;
			case Bot::Action::EAT:
				if (type == Object::ObjectType::FOOD)
				{
					botPtr->feed(1);
					destroyPlant();
					setNewObject(Object::ObjectType::VOID, next);
				}
				else if (type == Object::ObjectType::POISON)
				{
					botPtr->poison(1);
					--mPoisonCounter;
					setNewObject(Object::ObjectType::VOID, next);
				}
				j = 100;
				break;
			case Bot::Action::CONVERT:
				if (type == Object::ObjectType::POISON)
				{
					//TODO: error
					++mPlantBalanceChange;
					setNewObject(Object::ObjectType::FOOD, next);
				}
				break;
			case Bot::Action::LOOK:
				argument = mField[next.x][next.y]->getType();
				break;
			}
		}
		if (!botPtr->aging())
		{
			mOldBots.push(botPtr);
			mField[cur.x][cur.y] = new Object(Object::ObjectType::VOID);
			while (mOldBots.size() > 8) mOldBots.pop();
			//setNewObject(Object::ObjectType::VOID, cur);
		}
		else
		{
			mBotsCoord.push(cur);
		}
	}

	if (mFoodtCounter < FOOD_START_COUNT)
	{
		++mFoodtCounter;
		createNewPlant(Object::ObjectType::FOOD, mFoodSuitableCells, 1);
	}
	if (mPoisonCounter < POISON_START_COUNT)
	{
		++mPoisonCounter;
		createNewPlant(Object::ObjectType::POISON, mPoisonSuitableCells, 1);
	}


	//for (sint_8 i = 0; i < 1; ++i)
	//{
	//	//if (mFoodtCounter < FOOD_START_COUNT)
	//	//{
	//	//	createObjects(1, Object::ObjectType::FOOD);
	//	//	++mFoodtCounter;
	//	//}
	//	//else break;
	//}


	//createObjects(POISON_START_COUNT - mPoisonCounter, Object::ObjectType::POISON);

	//mFoodtCounter = FOOD_START_COUNT;
	//mPoisonCounter = POISON_START_COUNT;

	//check();
}

void 
Map::getSuitableCells
(
	Object::ObjectType aType,
	std::queue<Pair<sint_16>>& aContainer
)
{
	std::set<Pair<sint_16>> setOfSuitableCells;
	Direction dir(0);
	for (sint_16 i = 1; i < mField.size() - 1; ++i)
	{
		for (sint_16 j = 1; j < mField[0].size() - 1; ++j)
		{
			Pair<sint_16> cur(i, j);
			if (mField[cur.x][cur.y]->getType() == aType)
			{
				for (uint_8 k = 0; k < 6; ++k)
				{
					Pair<sint_16> next = dir.shiftPair(cur);
					if (mField[next.x][next.y]->getType() == Object::ObjectType::VOID)
					{
						setOfSuitableCells.insert(next);
					}
					++dir;
				}
			}
		}
	}

	std::vector<std::vector<Pair<sint_16>>> randomOrder(10);
	for (auto& i : setOfSuitableCells)
	{
		int num = rand() % randomOrder.size();
		randomOrder[num].push_back(i);
	}
	for (auto& i : randomOrder)
	{
		for (auto& j : i)
		{
			aContainer.push(j);
		}
	}
}

void
Map::createNewPlant
(
	Object::ObjectType aType, 
	std::queue<Pair<sint_16>>& aSuitableCells, 
	sint_16 aCount
)
{
	while (aCount)
	{
		if (aSuitableCells.empty())
		{
			getSuitableCells(aType, aSuitableCells);
		}

		Pair<sint_16> cur = aSuitableCells.front();
		aSuitableCells.pop();
		if (mField[cur.x][cur.y]->getType() != Object::ObjectType::VOID) continue;
		
		Direction dir(0);
		for (uint_8 k = 0; k < 6; ++k)
		{
			Pair<sint_16> neighbour = dir.shiftPair(cur);
			if (mField[neighbour.x][neighbour.y]->getType() == aType)
			{
				setNewObject(aType, cur);
				--aCount;
				break;
			}
			++dir;
		}
	}
}

//void
//Map::createNewPlant(Object::ObjectType aType, sint_16 aCount)
//{
//	if (aCount == 0) return;
//
//	//sint_16 x = rand() % (mField.size() - 2) + 1;
//	//sint_16 y = rand() % (mField[0].size() - 2) + 1;
//
//	std::set<Pair<sint_16>> setOfSuitableCells;
//	Direction dir(0);
//	for (sint_16 i = 1; i < mField.size() - 1; ++i)
//	{
//		for (sint_16 j = 1; j < mField[0].size() - 1; ++j)
//		{
//			Pair<sint_16> cur(i, j);
//			if (mField[cur.x][cur.y]->getType() == aType)
//			{
//				for (uint_8 k = 0; k < 6; ++k)
//				{
//					Pair<sint_16> next = dir.shiftPair(cur);
//					if (mField[next.x][next.y]->getType() == Object::ObjectType::VOID)
//					{
//						setOfSuitableCells.insert(next);
//					}
//					++dir;
//				}
//			}
//		}
//	}
//
//	std::vector<Pair<sint_16>> arrayOfSuitableCells;
//	for (auto& i : setOfSuitableCells) arrayOfSuitableCells.push_back(i);
//
//	for (sint_16 i = 0; i < std::min(aCount, sint_16(arrayOfSuitableCells.size())); ++i)
//	{
//		int num = rand() % arrayOfSuitableCells.size();
//		if (arrayOfSuitableCells[num].x != -1)
//		{
//			setNewObject(aType, arrayOfSuitableCells[num]);
//			arrayOfSuitableCells[num].x = -1;
//			--aCount;
//			--i;
//		}
//	}
//
//	createObjects(aCount, aType);
//}

bool 
Map::needToEvolve()
{
	return sint_16(mBotsCoord.size()) <= BOT_DOWN_LIMIT;
}

void 
Map::evolve()
{
	std::vector<Bot*> bots;

	while (!mBotsCoord.empty())
	{
		Pair<sint_16> cur = mBotsCoord.front();
		mBotsCoord.pop();
		bots.push_back(static_cast<Bot*>(mField[cur.x][cur.y]));
		bots.back()->reset();
		mField[cur.x][cur.y] = new Object(Object::ObjectType::VOID);
	}

	while (mOldBots.size() >  BOT_DOWN_LIMIT - bots.size())
	{
		mOldBots.pop();
	}
	while (!mOldBots.empty())
	{
		bots.push_back(mOldBots.front());
		mOldBots.pop();
	}

	//TODO: delete
	while (bots.size() < BOT_DOWN_LIMIT)
	{
		bots.push_back(new Bot());
		std::cout << "```` error adding bots\n";
	}

	regenerateField();

	for(auto& i : bots)
	{
		Pair<sint_16> new_coord;
		do
		{
			new_coord = Pair<sint_16>(rand() % mField.size(), rand() % mField[0].size());
		} while (mField[new_coord.x][new_coord.y]->getType() != Object::ObjectType::VOID);
		setExictingObject(i, new_coord);
	}

	for (uint_8 i = 0; i < BOT_MULTIPLY_COUNT; ++i)
	{
		for (auto& j : bots)
		{
			Pair<sint_16> new_coord;
			do
			{
				new_coord = Pair<sint_16>(rand() % mField.size(), rand() % mField[0].size());
			} while (mField[new_coord.x][new_coord.y]->getType() != Object::ObjectType::VOID);

			Bot* new_bot = new Bot(*j);
			new_bot->evolve((i - 1) < 0 ? 0 : (i - 1));
			setExictingObject(static_cast<Object*> (new_bot), new_coord);
		}
	}

	std::vector <Pair<sint_16>> temp = getObjectsCoordinates(Object::ObjectType::BOT);;
	for (auto& i : temp) mBotsCoord.push(i);
}

void 
Map::regenerateField()
{
	for (sint_16 i = 1; i < mField.size() - 1; ++i)
	{
		for (sint_16 j = 1; j < mField[0].size() - 1; ++j)
		{
			delete(mField[i][j]);
			mField[i][j] = new Object(Object::ObjectType::VOID);
		}
	}

	createObjects(FOOD_START_COUNT, Object::ObjectType::FOOD);
	createObjects(POISON_START_COUNT, Object::ObjectType::POISON);
	createObjects(WALL_START_COUNT, Object::ObjectType::WALL);

	mFoodtCounter = FOOD_START_COUNT;
	mPoisonCounter = POISON_START_COUNT;
	mWallCounter = WALL_START_COUNT;
}

std::vector<Pair<sint_16>>
Map::getObjectsCoordinates(Object::ObjectType aType)
{
	//while (!mBotsCoord.empty())
	//{
	//	std::cout << "aueue error\n";
	//	mBotsCoord.pop();
	//}
	std::vector <Pair<sint_16>> res;
	for (sint_16 i = 0; i < mField.size(); ++i)
	{
		for (sint_16 j = 0; j < mField[0].size(); ++j)
		{
			if (mField[i][j]->getType() == aType)
			{
				res.push_back({ i, j });
			}
		}
	}
	return res;
}

void 
Map::destroyPlant(Object::ObjectType aType)
{
	if (aType == Object::ObjectType::FOOD)
	{
		if (mPlantBalanceChange > 0)
		{
			--mPlantBalanceChange;
			--mPoisonCounter;
		}
		else --mFoodtCounter;
	}
	else if (aType == Object::ObjectType::POISON)
	{
		--mPoisonCounter;
	}
}

/*

Pair<sint_16> cur_coord = mBotsCoord.front();
		mBotsCoord.pop();
		Pair<sint_16> new_coord = cur_coord;
		do
		{
			new_coord = Pair<sint_16>(rand() % mField.size(), rand() % mField[0].size());
		} while (new_coord == cur_coord &&
			mField[new_coord.x][new_coord.y]->getType!= );
*/