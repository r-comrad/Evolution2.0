#ifndef DIRECTION_H
#define DIRECTION_H

#include "domain.h"

#define DIRECTION_MIN_LIMIT 0
#define DIRECTION_MAX_LIMIT 5

struct Direction
{
public:
	//enum Direction
	//{
	//	UP_RIGHT = 0,
	//	RIGHT = 1,
	//	DOWN_RIGHT = 2,
	//	DOWN_LEFT = 3,
	//	LEFT = 4,
	//	UP_LEFT = 5
	//};
	//union MyUnion
	//{
	//	sint_8 value;
	//	Direction direction;
	//};

	Direction(sint_8 aDirValue);

	Direction& operator++();
	Direction operator++(int);

	Direction& operator--();
	Direction operator--(int);

	Pair<sint_16> shiftPair(const Pair<sint_16>& aPair) const;

private:
	sint_8 mValue;

	//sint_8 getX() const;
	//sint_8 getY() const;
};

#endif //DIRECTION_H