#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Event.hpp"

#include "Core/Application/Application.h"
#include "Core/Characters/CharacterCreator.h"




#include "Core/World/World.h"
#include <Box2D/Box2D.h>
#include "Core/World/PhysicWorld.h"
#include "Core/Characters/Character.h"

int main()
{
    auto& app = Application::Get();
    app.Init();

    core::World2 world;
    world.Init();


    core::Character character = app.characterCreator->Create("cute_girl");
    character.SetBody(sf::FloatRect(100, 100, 100, 100), b2_dynamicBody);

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
                    character.Play("walk", 500ms);
                }
                else if(event.key.code == sf::Keyboard::R)
                {
                    character.ApplyForce(sf::Vector2f(10.0f, 0.0f));
                }
            }
            if(event.type == sf::Event::MouseMoved)
            {
            }
        }
        app.frameTime = 15ms;

        app.physicWorld->Update();

        world.Update();
        world.Draw(window);

        character.Update();
        character.Draw(window);

        window.display();
    }

    return 0;
}

