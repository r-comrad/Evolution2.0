#ifndef BOT_H
#define BOT_H

#include <vector>
#include <iostream>
#include <set>

#include "domain.h"
#include "object.h"
#include "direction.h"

#define BOT_PROGRAM_SIZE 65
#define COMMAND_LIMIT 6

#define START_HEALPH	90
#define FOOD_VALUE		30
#define POISON_VALUE	50

class Bot : public Object
{
public:
	enum class Action
	{
		NUN		=	0,
		VOID	=	1,
		GO		=	2,
		EAT		=	3,
		CONVERT	=	4,
		LOOK	=	5
	};

	Bot();
	Bot(const Bot& aOther);
	virtual ~Bot();
	const Direction& getDirection() const;
	void feed(float aValue);
	void poison(float aValue);
	Bot::Action makeAction(Object::ObjectType);
	bool aging();
	void evolve(uint_8 aValue);
	void reset();
	sint_8 getHealph() const;

private:
	sint_8 mProgramPtr;
	std::vector<sint_8> mProgram;
	sint_8 mHealph;

	Direction mDirection;
	sint_8 generateComand();
	enum Comands
	{
		BOT_GO = 11,
		BOT_EAT = 12,
		BOT_CONVERT = 13,
		BOT_LOOK = 14, 
		BOT_TURN_RIGHT = 15,
		BOT_TURN_LEFT = 16,
	};
	//void changeHealph(sint_8 aValue);
};

#endif //BOT_H