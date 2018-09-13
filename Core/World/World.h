#pragma once
#include <vector>
#include "../Entity/Entity.h"
#include "../Character/Character.h"
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
//    Character CreateCharacter(const std::string& name,
//                              const sf::Vector2f& pos,
//                              const sf::Vector2f& characterSize,
//                              const sf::Vector2f& rigidBodySize,
//                              b2BodyType bodyType);
private:
    sf::Sprite m_background;
    std::vector<Entity> m_tiles;
};

} //end of core
