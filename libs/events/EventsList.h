#pragma once
#include "Events.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <chrono>

using namespace std::chrono_literals;

namespace libs
{
namespace events
{
    static Event<void(std::chrono::milliseconds)> onUpdate;
    static Event<void(sf::RenderWindow&)> onDraw;
    static Event<void(const sf::Event::MouseButtonEvent&)> onMousePressed;
    static Event<void(const sf::Event::KeyEvent&)> onKeyboardPressed;
}
}
