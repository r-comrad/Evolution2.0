#include "gui.h"
#include "map.h"

#include <iostream>

int main()
{
	Map map(32, 20);
	GUI gui(1775, 940);
	bool needToDraw = true;
	bool pause = false;
	for (int cnt = 0, era = 0; !gui.isAppClosed(); ++cnt)
	{
		if (needToDraw) gui.drawField(map.getPresentation());
		std::vector<GUI::EventType> events = gui.getEvents();
		for (auto& i : events)
		{
			if (i == GUI::EventType::SWITCH_DRAW_MODE) needToDraw = !needToDraw;
			else if (i == GUI::EventType::SWITCH_PAUSE) pause = !pause;
		}
		if (pause) continue;

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