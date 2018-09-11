#pragma once
#include <Box2D/Dynamics/b2Body.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace core
{

///Non copyable object
class Entity
{
public:
    Entity() = default;
    ~Entity();

    Entity(const Entity&) = delete;
    Entity& operator=(const Entity&) = delete;

    Entity(Entity&&) = default;
    Entity& operator=(Entity&&) = default;

    void SetTexture(const std::string& holder, const std::string& id);
    void SetBody(const sf::FloatRect& box, b2BodyType bodyType);

    void ApplyForce(sf::Vector2f force);
    void Update();
    void Draw(sf::RenderWindow& window) const;
private:
    void updateSprite();

    b2Body* m_rigidBody = nullptr;
    sf::Vector2f m_velocity;

    sf::FloatRect m_textureRect;
    sf::Sprite m_sprite;
};

}
