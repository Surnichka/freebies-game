#include <iostream>
#include "SFML/Graphics.hpp"


using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(1400, 1024), "FREEBIES");
    window.setFramerateLimit(60);

    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("../freebies-game/resources/BACKGROUND.png");
    sf::Sprite background;
    background.setTexture(backgroundTexture);
    background.setScale(1.4f, 1.37f);


    sf::Event event;
    while (window.isOpen())
    {
        window.clear(sf::Color::White);
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.draw(background);
        window.display();
    }


    return 0;
}
