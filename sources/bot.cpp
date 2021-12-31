#include "bot.h"

Bot::Bot() :
	Object		(Object::ObjectType::BOT),
	mProgram	(BOT_PROGRAM_SIZE), 
	mProgramPtr	(0),
	mDirection	(rand() % 6),
	mHealph		(START_HEALPH)
{
	for (auto& i : mProgram) i = generateComand();
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
	case BOT_GO:
		result = Bot::Action::GO;
		break;
	case BOT_EAT:
		result = Bot::Action::EAT;
		break;
	case BOT_CONVERT:
		result = Bot::Action::CONVERT;
		break;
	case BOT_LOOK:
		result = Bot::Action::LOOK;
		break;
	case BOT_TURN_RIGHT:
		++mDirection;
		result = Bot::Action::VOID;
		break;
	case BOT_TURN_LEFT:
		--mDirection;
		result = Bot::Action::VOID;
		break;
	//case 6:
	//	--mDirection;
	//	result = Bot::Action::VOID;
	//	break;
	default:
		if (mProgram[mProgramPtr] != 0)
		{
			mProgramPtr += mProgram[mProgramPtr];
			result = Bot::Action::VOID;
		}
		else
		{
			std::cout << "bot program error\n";
		}
		break;
	}
	++mProgramPtr;
	if (mProgramPtr >= sint_8(mProgram.size())) mProgramPtr -= mProgram.size();
	if (mProgramPtr < 0)
	{
		mProgramPtr += mProgram.size();
	}
	return result;
}

sint_8
Bot::generateComand()
{
	int command = rand() % COMMAND_LIMIT;
	switch (command)
	{
	case 0 :
		command = Comands::BOT_GO;
		break;
	case 1:
		command = Comands::BOT_EAT;
		break;
	case 2:
		command = Comands::BOT_CONVERT;
		break;
	case 3:
		command = Comands::BOT_LOOK;
		break;
	case 4:
		if (rand() % 2) command = Comands::BOT_TURN_LEFT;
		else command = Comands::BOT_TURN_RIGHT;
		break;
	case 5:
		if (rand() % 2) command = rand() % 10 + 1;
		else command = -(rand() % 10 + 1);
		break;
	default:
		std::cout << "error command generating\n";
		command = 0;
		break;
	}
	return command;
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
			new_value = generateComand();
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