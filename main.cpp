#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Event.hpp"

#include "Core/Application/Application.h"
#include "Core/Animator/AnimatorFactory.h"
#include "Core/Animator/Animator.h"

#include <Box2D/Box2D.h>
#include "Core/World/World.h"
#include "Core/World/PhysicWorld.h"
#include "Core/World/PhysicDebugDraw.h"

#include "Core/Character/Character.h"
int main()
{
    auto& app = Application::Get();
    app.Init();

    core::World world;
    world.Init();

    sf::RenderWindow window(sf::VideoMode(static_cast<uint32_t>(app.windowSize.x),
                                          static_cast<uint32_t>(app.windowSize.y)),
                                          "FREEBIES");

    auto animator = app.animatorFactory->Create("knight");

    core::Character demoCharacter;
    demoCharacter.Init(std::move(animator));
    demoCharacter.SetSize({120, 120});
    demoCharacter.SetBody({200, 150, 65, 80}, b2_dynamicBody);

    core::PhysicDebugDraw b2DebugDraw(window);
    app.physicWorld->GetB2World()->SetDebugDraw(&b2DebugDraw);

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

        app.physicWorld->Update();
        world.Update();

        demoCharacter.ApplyForce(sf::Vector2f(0.0f, 10.0f)); //Gravity
        demoCharacter.Update();

        world.Draw(window);
        demoCharacter.Draw(window);

        app.physicWorld->GetB2World()->DrawDebugData();

        window.display();
    }

    return 0;
}

