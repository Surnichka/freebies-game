#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Event.hpp"
#include <iostream>
#include "Core/Application/Application.h"
#include "Core/Characters/CharacterCreator.h"

int main()
{
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

    auto& app = Application::Get();
    app.Init();

    core::Character character;

    sf::RenderWindow window(sf::VideoMode(1400, 1024), "FREEBIES");
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

        character.Play((*currentAnimId), 700ms, core::ReplayPolicy::OnNew);

        character.Update(15ms);
        character.Draw(window);

        window.display();
    }

    return 0;
}

