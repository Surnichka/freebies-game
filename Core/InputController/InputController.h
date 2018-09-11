#pragma once
#include <string>
#include <SFML/Window/Event.hpp>

namespace core
{

class InputController
{
public:
    void Bind(const std::string& id, sf::Keyboard key);
private:
};

} //end of core
