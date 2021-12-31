#include "direction.h"

Direction::Direction(sint_8 aDirValue) :
	mValue	(aDirValue)
{}

Direction& 
Direction::operator++() {
	mValue++;
	if (mValue > DIRECTION_MAX_LIMIT)
	{
		mValue -= DIRECTION_MAX_LIMIT + 1;
	}
	return *this;
}

Direction 
Direction::operator++(int) {
	Direction tmp({ mValue });
	++(*this);
	return tmp;
}

Direction& 
Direction::operator--() {
	mValue--;
	if (mValue < DIRECTION_MIN_LIMIT)
	{
		mValue += DIRECTION_MAX_LIMIT + 1;
	}
	return *this;
}

Direction 
Direction::operator--(int) {
	Direction tmp({ mValue });
	--(*this);
	return tmp;
}

//sint_8 
//Direction::getX() const
//{
//	sint_8 result = 0;
//	if (mValue < 3) result = 1;
//	else result = -1;
//	return result;
//}
//
//sint_8 
//Direction::getY() const
//{
//	sint_8 result = 0;
//	if (mValue == 0 || mValue == 5) result = -1;
//	else if (mValue == 2 || mValue == 3) result = 1;
//	return result;
//}

Pair<sint_16>
Direction::shiftPair(const Pair<sint_16>& aPair) const
{
	Pair<sint_16> result = aPair;
	if (result.y % 2 == 0)
	{
		if (mValue > 2) --result.x;
		else if (mValue == 1) ++result.x;
	}
	else
	{
		if (mValue == 4) --result.x;
		else if (mValue < 3) ++result.x;
	}

	if (mValue == 0 || mValue == 5) --result.y;
	else if (mValue == 2 || mValue == 3) ++result.y;

	return result;
}

