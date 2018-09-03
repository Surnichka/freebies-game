#include <iostream>
#include "SFML/Graphics.hpp"
#include <Thor/Resources.hpp>
#include <Box2D/Box2D.h>
#include "AssetsParser/CharacterParser.h"
#include "Core/Characters/Character.h"

int main()
{
    CharacterParser cp;
    cp.Parse();

    std::map<std::string, std::vector<sf::Texture>> animTextures;
    for(auto& p : cp.charactersKeys)
    {
        if((p[1] == std::string("attack")))
        {
            std::cout << p[2] << std::endl;
        }
    }

    for(const auto& keys : cp.charactersKeys)
    {
        const auto& animId = keys[1];
        const auto& path = keys[2];
        auto& textureList = animTextures[animId];
        textureList.push_back(sf::Texture());
        textureList.back().loadFromFile(path);
    }

    core::Character knight;
    for(const auto& p : animTextures)
    {
        const auto& animId = p.first;
        const auto& textureList = p.second;
        std::vector<sf::Sprite> sprites(textureList.size());
        for(size_t i = 0; i < sprites.size(); i++)
        {
            sprites[i].setTexture(textureList[i]);
        }

        knight.AddAnimation(animId, sprites);
    }
    knight.SetScale({0.25f, 0.25f});

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
        knight.Play("idle", 600ms, core::ReplayPolicy::Never);


        knight.Update(15ms);
        knight.Draw(window);

        window.display();
    }

    return 0;
}

