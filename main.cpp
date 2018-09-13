#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Event.hpp"

#include "Core/Application/Application.h"

#include "Core/World/World.h"
#include <Box2D/Box2D.h>
#include "Core/World/PhysicDebugDraw.h"

#include <chrono>
int main()
{
    auto& app = Application::Get();
    app.Init();

    sf::RenderWindow window(sf::VideoMode(static_cast<uint32_t>(app.windowSize.x),
                                          static_cast<uint32_t>(app.windowSize.y)),
                                          "FREEBIES");
    window.setFramerateLimit(60);

    core::PhysicDebugDraw b2DebugDraw(window);
    app.world->GetPhysicWorld()->SetDebugDraw(&b2DebugDraw);

    auto character = app.world->CreateCharacter("knight", {100, 100, 100, 100}, {60, 80});
//    character.SetController(Player::One);
//    character.SetController(Player::Two);

//    character.SetController(AI::Patrul);
//    character.SetController(AI::Agressive);

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
        app.frameTime = std::chrono::milliseconds(15);

        character.ApplyForce({0.0f, 10.0f});
        character.Update();
        app.world->Update();

        app.world->Draw(window);
        character.Draw(window);

        app.world->GetPhysicWorld()->DrawDebugData();

        window.display();
    }

    return 0;
}

