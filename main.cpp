#include <iostream>
#include "SFML/Graphics.hpp"
#include "libs/xml_parser/XmlParser.h"
#include "libs/events/EventsList.h"
#include "libs/resource_mgr/TextureWrapper.h"
#include "libs/sprite/Sprite.h"
#include <libs/tweeny/Tween.h>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1400, 1024), "FREEBIES");
    window.setFramerateLimit(60);

//    libs::XmlParser xmlParser;
//    xmlParser.Init();
//    xmlParser.LoadFile("../freebies-game/test.xml");

    auto tw = std::make_shared<libs::TextureWrapper>();
    tw->texture = std::make_unique<sf::Texture>();
    tw->texture->loadFromFile("../freebies-game/resources/Tree_2.png");

    std::vector<libs::Sprite> sprites;
    std::vector<libs::Tween<float>> tweenies;

    libs::Tween<float> tweeny;
    tweeny.addPoint(0.0f)
          .addPoint(15.0f)
          .addPoint(-15.0f)
          .during(300ms)
          .addPoint(7.0f)
          .addPoint(-7.0f)
          .addPoint(0.0f)
          .during(300ms)
          .addPoint(3.0f)
          .addPoint(-3.0f)
          .addPoint(0.0f)
          .during(300ms);

    sprites.resize(20);
    int i = 0;
    for(auto& sprite : sprites)
    {
         i++;
         sprite.setTexture(tw);
         sprite.setPosition(i * 50, 250);
         sprite.setScale(0.5f, 0.5f);
         tweenies.push_back(tweeny);
         tweenies.back().onStep(
         [&sprite](const auto& tween)
         {
             sprite.xWeight = tween.peek();
         });
    }

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
                if(event.key.code == sf::Keyboard::A)
                {
                    tweenies[0].start();
                }
            }
            if(event.type == sf::Event::MouseMoved)
            {
//                libs::events::onMousePressed(event.mouseButton);

                for(int i = 0; i < sprites.size(); i++)
                {
                    if(sprites[i].getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y))
                    {
                        if(tweenies[i].getProgress() == tweenies[i].getDuration())
                        {
                            tweenies[i].start();
                        }
                    }
                }
            }
        }

        for(auto& tweeny : tweenies)
        {
            tweeny.stepBy(15ms);
        }

        for(auto& sprite : sprites)
        {
            sprite.update(15ms);
            window.draw(sprite);
        }

        libs::events::onUpdate(15ms);
        libs::events::onDraw(window);
        window.display();
    }


    return 0;
}
