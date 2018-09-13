#pragma once
#include <vector>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "../Entity/Entity.h"
#include "../Character/Character.h"

#include "PhysicWorldUtils.h"

namespace core
{

class World
{
public:
    void Init();

    void Update();
    void Draw(sf::RenderWindow& window);

    std::unique_ptr<b2World>& GetPhysicWorld();

    Character CreateCharacter(const std::string& name,
                              sf::FloatRect spriteRect,
                              sf::Vector2f rigidBodySize);
private:
    BodyPtr createTileBox(sf::FloatRect rect);

    std::unique_ptr<b2World> m_physicWorld;
    std::vector<Entity> m_entities;
    sf::Sprite m_background;
};

} //end of core
