#include "bot.h"

Bot::Bot() :
	Object		(Object::ObjectType::BOT),
	mProgram	(BOT_PROGRAM_SIZE), 
	mProgramPtr	(0),
	mDirection	(rand() % 6),
	mHealph		(START_HEALPH)
{
	for (auto& i : mProgram) i = rand() % COMMAND_LIMIT + 1;
}

Bot::Bot(const Bot& aOther) :
	Object(Object::ObjectType::BOT),
	mProgramPtr(0),
	mDirection(rand() % 6),
	mHealph(START_HEALPH)
{
	mProgram = aOther.mProgram;
}

Bot::~Bot(){}

const Direction&
Bot::getDirection() const
{
	return mDirection;
}

Bot::Action 
Bot::makeAction(Object::ObjectType)
{
	Bot::Action result = Bot::Action::NUN;
	switch (mProgram[mProgramPtr])
	{
	case 1 :
		result = Bot::Action::GO;
		break;
	case 2:
		result = Bot::Action::EAT;
		break;
	case 3:
		result = Bot::Action::CONVERT;
		break;
	case 4:
		result = Bot::Action::LOOK;
		break;
	case 5:
		++mDirection;
		result = Bot::Action::VOID;
		break;
	case 6:
		--mDirection;
		result = Bot::Action::VOID;
		break;
	//case 6:
	//	--mDirection;
	//	result = Bot::Action::VOID;
	//	break;
	default:
		std::cout << "bot program error\n";
		break;
	}
	++mProgramPtr;
	if (mProgramPtr >= mProgram.size()) mProgramPtr = 0;
	return result;
}

void 
Bot::feed(float aValue)
{
	mHealph += FOOD_VALUE * aValue;
	if (mHealph > 90) mHealph = 90;
}

void
Bot::poison(float aValue)
{
	mHealph -= POISON_VALUE * aValue;
}

bool
Bot::aging()
{
	mHealph--;
	return mHealph > 0;
}

void 
Bot::evolve(uint_8 aValue)
{
	std::set<uint_16> mutations;
	while (mutations.size() < aValue)
	{
		mutations.insert(rand() % mProgram.size());
	}

	for (auto& i : mutations)
	{
		uint_8 new_value = mProgram[i];
		do
		{
			new_value = rand() % COMMAND_LIMIT + 1;
		} while (new_value == mProgram[i]);

		mProgram[i] = new_value;
	}
}

void
Bot::reset()
{
	mProgramPtr = 0;
	mDirection = rand() % 6;
	mHealph = START_HEALPH;
}
//void
//Bot::changeHealph(sint_8 aValue)
//{
//	mHealph += aValue;
//}

sint_8
Bot::getHealph() const
{
	return mHealph;
}