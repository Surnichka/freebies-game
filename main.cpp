#include <iostream>
#include "SFML/Graphics.hpp"
#include "libs/xml_parser/XmlParser.h"
#include "libs/events/EventsList.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1400, 1024), "FREEBIES");
    window.setFramerateLimit(60);

    libs::XmlParser xmlParser;
    xmlParser.Init();
    xmlParser.LoadFile("../freebies-game/test.xml");

    sf::Event event;
    while (window.isOpen())
    {
        window.clear(sf::Color::White);
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }
            if(event.type == sf::Event::KeyPressed)
            {
                libs::events::onKeyboardPressed(event.key);
            }
            if(event.type == sf::Event::MouseButtonPressed)
            {
                libs::events::onMousePressed(event.mouseButton);
            }
        }

        libs::events::onUpdate(15ms);
        libs::events::onDraw(window);
        window.display();
    }


    return 0;
}
