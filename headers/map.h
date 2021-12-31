#ifndef MAP_Hsint_16 mPlantCounter;
#define MAP_H

#include <vector>
#include <set>
#include <queue>
#include <math.h>
#include <algorithm>

#include "domain.h"
#include "object.h"
#include "bot.h"

#define BOTS_START_COUNT 64
#define POISON_START_COUNT (64 * 3)
#define FOOD_START_COUNT (64 * 2)
#define WALL_START_COUNT (64 * 2)
//#define GROW_SPPED

#define BOT_ACTION_LIMIT 8
#define BOT_DOWN_LIMIT 8
//#define BOT_DOWN_LIMIT -1
#define BOT_MULTIPLY_COUNT 7

class Map
{
public:
	Map(sint_16 aN, sint_16 aM);
	const std::vector<std::vector<Object*>>& getPresentation();
	void makeTurn();
	bool needToEvolve();
	void evolve();
	void check();
private:
	std::vector<std::vector<Object*>> mField;
	std::queue<Pair<sint_16>> mBotsCoord;
	//std::map <Pair<sint_16>> mFoodCoord;
	//std::vector <Pair<sint_16>> mPoisonCoord;

	void setNewObject(Object::ObjectType aType, Pair<sint_16> aCoord);
	void setExictingObject(Object* aObjectPtr, Pair<sint_16> aCoord);
	bool trySetNewObject(Object::ObjectType aType, Pair<sint_16> aCoord);

	void createObjects(sint_16 aLimit, Object::ObjectType aType);

	sint_16 mFoodtCounter;
	sint_16 mPoisonCounter;
	sint_16 mWallCounter;
	sint_16 mPlantBalanceChange;

	std::queue<Pair<sint_16>> mFoodSuitableCells;
	std::queue<Pair<sint_16>> mPoisonSuitableCells;
	
	void destroyPlant(Object::ObjectType aType = Object::ObjectType::FOOD);

	void regenerateField();
	std::vector <Pair<sint_16>> getObjectsCoordinates(Object::ObjectType aType);
	std::queue<Bot*> mOldBots;

	void createNewPlant(Object::ObjectType aType, std::queue<Pair<sint_16>>& aSuitableCells, sint_16 aCount);
	void getSuitableCells(Object::ObjectType aType, std::queue<Pair<sint_16>>& aContainer);
};

#endif //MAP_H

/*

32 * 20 = 640 
64 = 10%		bots
64 * 3 = 30%	poison
64 * 2 = 20%	food
64 * 2 = 20%	wall

*/