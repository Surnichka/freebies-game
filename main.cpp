#include <iostream>
#include "SFML/Graphics.hpp"
#include <Thor/Resources.hpp>
#include <Box2D/Box2D.h>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1400, 1024), "FREEBIES");
    window.setFramerateLimit(60);

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

            }
            if(event.type == sf::Event::MouseMoved)
            {

            }
        }
        window.display();
    }

    return 0;
}

