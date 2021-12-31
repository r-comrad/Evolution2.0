#include "gui.h"

GUI::GUI(sint_16 aN, sint_16 aM) :
    mWindow     (sf::VideoMode(aN, aM), "Evolution"),
    mHexagon    (HEXAGON_SIZE, 6)
{
    mHexagon.setOutlineColor(sf::Color::Black);
    mHexagon.setOutlineThickness(HEXAGON_OTLINE_THICKNESS);
    mHexagon.setFillColor(sf::Color::White);
    mHexagon.setOrigin(HEXAGON_SIZE, HEXAGON_SIZE);

    if (!mFont.loadFromFile("font.ttf"))
    {
        std::cout << "Font load error!\n";
    }
    mText.setFont(mFont);
    mText.setFillColor(sf::Color::White);
    //mText.setStyle(sf::Text::Bold | sf::Text::Underlined);
    //mText.setScale
}

void 
GUI::drawField(std::vector<std::vector<Object*>> aField)
{
    mWindow.clear(sf::Color::Black);

    for (sint_16 i = 0; i < aField.size(); ++i) {
        for (sint_16 j = 0; j < aField[0].size(); ++j) {
            mHexagon.setPosition(
                (HEXAGON_DX +
                    (j % 2 ? (HEXAGON_SIZE * 3) : (HEXAGON_SIZE*2.))) + 
                i * HEXAGON_SIZE *2.,
                HEXAGON_DY + j * (HEXAGON_SIZE *1.6f));
            mHexagon.setOutlineColor(sf::Color::White);
            switch (aField[i][j]->getType())
            {
            case Object::ObjectType::VOID:
                mHexagon.setFillColor(sf::Color::Black);
                break;
            case Object::ObjectType::BOT:
                mHexagon.setFillColor(sf::Color::Blue);
                break;
            case Object::FOOD:
                mHexagon.setFillColor(sf::Color::Green);
                break;
            case Object::POISON:
                mHexagon.setFillColor(sf::Color::Red);
                break;
            case Object::WALL:
                mHexagon.setFillColor(sf::Color(125, 125, 125));
                break;
            default:
                mHexagon.setFillColor(sf::Color(255, 175, 25));
                break;
            }
            
            mWindow.draw(mHexagon);

            if (aField[i][j]->getType() == Object::ObjectType::BOT)
            {
                std::string botHealph = std::to_string(static_cast<Bot*>(aField[i][j])->getHealph());
                mText.setPosition(
                    ((botHealph.size() == 1 ? TEXT_SINGLE_DX : 0) + TEXT_DX + HEXAGON_DX +
                        (j % 2 ? (HEXAGON_SIZE * 3) : (HEXAGON_SIZE * 2.))) +
                    i * HEXAGON_SIZE * 2.,
                    TEXT_DY + HEXAGON_DY + j * (HEXAGON_SIZE * 1.6f));
                //std::string ss = (std::to_string(static_cast<Bot*>(aField[i][j])->getHealph()));
                mText.setString(botHealph);
                mWindow.draw(mText);
            }
            //else 
            //{
            //    mText.setScale(sf::Vector2f(0.5, 0.5));
            //    mText.setPosition(
            //        (TEXT_DX + HEXAGON_DX +
            //            (j % 2 ? (HEXAGON_SIZE * 3) : (HEXAGON_SIZE * 2.))) +
            //        i * HEXAGON_SIZE * 2.,
            //        TEXT_DY + HEXAGON_DY + j * (HEXAGON_SIZE * 1.6f));
            //    //std::string ss = (std::to_string(static_cast<Bot*>(aField[i][j])->getHealph()));
            //    mText.setString(std::to_string(i) + " " + std::to_string(j));
            //    mWindow.draw(mText);
            //    mText.setScale(sf::Vector2f(1, 1));
            //}
        }
    }
    mWindow.display();
}

bool 
GUI::isAppClosed()
{
    return !mWindow.isOpen();
}

std::vector<GUI::EventType>
GUI::getEvents()
{
    std::vector<EventType> result = result;
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            mWindow.close();

        if (event.type == sf::Event::KeyReleased)
        {
            if (event.key.code == sf::Keyboard::Key::Tab)
            {
                result.push_back(GUI::EventType::SWITCH_DRAW_MODE);
            }
            else if (event.key.code == sf::Keyboard::Key::Space)
            {
                result.push_back(GUI::EventType::SWITCH_PAUSE);
            }
            else if (event.key.code == sf::Keyboard::Key::X)
            {
                result.push_back(GUI::EventType::INCREASE_PAUSE);
            }
            else if (event.key.code == sf::Keyboard::Key::Z)
            {
                result.push_back(GUI::EventType::DECREASE_PAUSE);
            }
            else if (event.key.code == sf::Keyboard::Key::LShift)
            {
                result.push_back(GUI::EventType::ZERO_PAUSE);
            }
        }
    }
    return result;
}