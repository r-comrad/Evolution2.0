#ifndef GUI_H
#define GUI_H

#include <iostream>
#include <vector>
#include <string>

#include <SFML/Graphics.hpp>

#include "object.h"
#include "bot.h"
#include "domain.h"

#define HEXAGON_DX 0.f
#define HEXAGON_DY 50.f

#define TEXT_DX -18.f
#define TEXT_DY -20.f

#define HEXAGON_OTLINE_THICKNESS 5.f
#define HEXAGON_SIZE 25.f

class GUI
{
public:
	enum EventType
	{
		NUN = 0,
		SWITCH_DRAW_MODE = 1,
		SWITCH_PAUSE = 2
	};

	GUI(sint_16 aN, sint_16 aM);
	void drawField(std::vector<std::vector<Object*>> aField);
	bool isAppClosed();
	std::vector<EventType> getEvents();

private:
	sf::RenderWindow mWindow;

	sf::Font mFont;
	sf::Text mText;

	sf::CircleShape mHexagon;
};

#endif //GUI_H