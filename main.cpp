#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Event.hpp"

#include "Core/Application/Application.h"
#include "Core/Animator/AnimatorFactory.h"
#include "Core/Animator/Animator.h"

#include "Core/World/World.h"
#include <Box2D/Box2D.h>
#include "Core/World/PhysicWorld.h"

#include "Core/Character/Character.h"

int main()
{
    auto& app = Application::Get();
    app.Init();

    core::World2 world;
    world.Init();

    core::Character character;
    character.Init();
    character.m_animator = app.animatorFactory->Create("knight");
    character.SetSize({100, 100});
    character.SetBody({500, 60, 70, 70}, b2_dynamicBody);

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
            }
            if(event.type == sf::Event::MouseMoved)
            {
            }
        }
        app.frameTime = 15ms;
        character.ApplyForce(sf::Vector2f(0.0f, 20.0f));

        app.physicWorld->Update();

        world.Update();
        world.Draw(window);

        character.Update();
        character.Draw(window);

        window.display();
    }

    return 0;
}

