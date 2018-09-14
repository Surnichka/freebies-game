#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Event.hpp"

#include "Core/Application/Application.h"
#include "Core/CharacterController/CharacterController.h"

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

    auto character = app.world->CreateCharacter("knight", {120, 100, 100, 100}, {60, 80});
    character.SetController(core::controllers::Player_One());

//    auto character2 = app.world->CreateCharacter("cute_girl", {120, 100, 100, 100}, {60, 80});
//    character2.SetController(core::controllers::PlayerTwo());

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

        character.ApplyForce({0.0f, 15.0f});
        character.Update();

//        character2.ApplyForce ({0.0f, 15.0f});
//        character2.Update();

        app.world->Update();

        app.world->Draw(window);
        character.Draw(window);
//        character2.Draw(window);

        app.world->GetPhysicWorld()->DrawDebugData();

        window.display();
    }

    return 0;
}

