#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Event.hpp"
#include <iostream>
#include "Core/Application/Application.h"
#include "Core/Characters/CharacterCreator.h"
#include "Core/World/World.h"
#include <Box2D/Box2D.h>
#include "Core/World/PWorld.h"

int main()
{
    auto& app = Application::Get();
    app.Init();

    core::World world;
    world.Init();

    static const std::vector<std::string> testCharacters =
    {
        "knight", "cute_girl"
    };
    static const std::vector<std::string> testAnimations =
    {
        "idle", "walk", "run", "jump", "attack", "jump_attack", "die"
    };
    auto currentCharacter = testCharacters.cbegin();
    auto currentAnimId = testAnimations.cbegin();

    core::Character character;

    sf::RenderWindow window(sf::VideoMode(static_cast<uint32_t>(app.windowSize.x),
                                          static_cast<uint32_t>(app.windowSize.y)),
                                          "FREEBIES");
    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        window.clear(sf::Color(127, 174, 169));

        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }
            if(event.type == sf::Event::KeyPressed)
            {
                if(event.key.code == sf::Keyboard::T)
                {
                    currentAnimId++;
                    if(currentAnimId == testAnimations.cend())
                    {
                        currentAnimId = testAnimations.cbegin();
                    }
                    std::cout << "Current animation :" << (*currentAnimId) << std::endl;
                }
                else if(event.key.code == sf::Keyboard::R)
                {
                    currentCharacter++;
                    if(currentCharacter == testCharacters.cend())
                    {
                        currentCharacter = testCharacters.cbegin();
                    }
                    character = app.characterCreator->Create((*currentCharacter));

                    character.setScale({0.25f, 0.25f});
                    character.setPosition({300, 300});
                }
            }
            if(event.type == sf::Event::MouseMoved)
            {
            }
        }
        app.frameTime = 15ms; //calculate delta time
        app.physicWorld->Update();

        character.Play((*currentAnimId), 700ms, core::ReplayPolicy::OnNew);

        character.Update();
        character.Draw(window);

        world.Update();
        world.Draw(window);

        window.display();
    }

    return 0;
}

