#include "gui.h"
#include "map.h"

#include <iostream>


bool dirCheck()
{
	std::vector<Pair<sint_16>> ss = { {25, 12}, {25, 11} };
	std::vector<std::vector< Pair<sint_16>>> sss =
	{
		{
			{25, 11},
			{26, 12},
			{25, 13},
			{24, 13},
			{24, 12},
			{24, 11}
		},
		{
			{26, 10},
			{26, 11},
			{26, 12},
			{25, 12},
			{24, 11},
			{25, 10}
		},
	};

	Direction dir(0);
	for (int j = 0; j < 2; ++j)
	{
		for (int i = 0; i < 6; ++i)
		{
			if (sss[j][i] != dir.shiftPair(ss[j])) return false;
			++dir;
		}
	}
	return true;
}

int main()
{
	//std::cout << dirCheck() << "\n";
	//return 0;
	Map map(32, 20);
	GUI gui(1775, 940);
	bool needToDraw = true;
	bool turnOff = false;
	//long long pauseTime = 1*7*7*7*7*7*7*7;
	long long pauseTime = 1;
	for (int cnt = 0, era = 0; !gui.isAppClosed(); ++cnt)
	{
		if (needToDraw) gui.drawField(map.getPresentation());
		for (long long i = 0; i < pauseTime; ++i)
		{
			std::vector<GUI::EventType> events = gui.getEvents();
			for (auto& i : events)
			{
				if (i == GUI::EventType::SWITCH_DRAW_MODE) needToDraw = !needToDraw;
				else if (i == GUI::EventType::SWITCH_PAUSE) turnOff = !turnOff;
				else if (i == GUI::EventType::INCREASE_PAUSE) pauseTime *= 7;
				else if (i == GUI::EventType::DECREASE_PAUSE) pauseTime /= 7;
				else if (i == GUI::EventType::ZERO_PAUSE) pauseTime = 1;
			}

			if (!needToDraw) break;
		}
		if (turnOff) continue;

		map.makeTurn();
		if (map.needToEvolve())
		{
			map.evolve();
			std::cout << era << ": " << cnt << std::endl;
			cnt = 0;
			++era;
		}
	}
}