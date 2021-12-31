#ifndef MAP_Hsint_16 mPlantCounter;
#define MAP_H

#include <vector>
#include <set>
#include <queue>

#include "domain.h"
#include "object.h"
#include "bot.h"

#define BOTS_START_COUNT 64
#define POISON_START_COUNT (64 * 3)
#define FOOD_START_COUNT (64 * 2)
#define WALL_START_COUNT (64 * 2)

#define BOT_ACTION_LIMIT 8
#define BOT_DOWN_LIMIT 8
#define BOT_MULTIPLY_COUNT 7

class Map
{
public:
	Map(sint_16 aN, sint_16 aM);
	const std::vector<std::vector<Object*>>& getPresentation();
	void makeTurn();
	bool needToEvolve();
	void evolve();
private:
	std::vector<std::vector<Object*>> mField;
	std::queue<Pair<sint_16>> mBotsCoord;

	void setNewObject(Object::ObjectType aType, Pair<sint_16> aCoord);
	void setExictingObject(Object* aObjectPtr, Pair<sint_16> aCoord);
	bool trySetNewObject(Object::ObjectType aType, Pair<sint_16> aCoord);

	void createObjects(sint_16 aLimit, Object::ObjectType aType);

	sint_16 mFoodtCounter;
	sint_16 mPoisonCounter;
	sint_16 mWallCounter;

	void regenerateField();
	void getBotsCoordinates();
};

#endif //MAP_H

/*

32 * 20 = 640 
64 = 10%		bots
64 * 3 = 30%	poison
64 * 2 = 20%	food
64 * 2 = 20%	wall

*/