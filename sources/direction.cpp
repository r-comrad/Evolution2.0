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

sint_8 
Direction::getX() const
{
	sint_8 result = 0;
	if (mValue == 0 || mValue == 5) result = -1;
	else if (mValue == 2 || mValue == 3) result = 1;
	return result;
}

sint_8 
Direction::getY() const
{
	sint_8 result = 0;
	if (mValue < 3) result = 1;
	else result = -1;
	return result;
}