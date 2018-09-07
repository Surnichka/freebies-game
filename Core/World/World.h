#pragma once
#include <vector>
#include "../Entity/Entity.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace core
{

class World
{
public:
    void Init();

    void Update();
    void Draw(sf::RenderWindow& window);
private:
    sf::Sprite m_background;
    std::vector<Entity> m_map;
};

} //end of core
