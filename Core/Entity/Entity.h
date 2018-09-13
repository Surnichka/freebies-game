#pragma once
#include <Box2D/Dynamics/b2Body.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "../World/PhysicWorldUtils.h"

namespace core
{

///Non copyable object
class Entity
{
public:
    Entity() = default;
    virtual ~Entity();

    Entity(const Entity&) = delete;
    Entity& operator=(const Entity&) = delete;

    Entity(Entity&&) = default;
    Entity& operator=(Entity&&) = default;

    void SetTexture(const std::string& holder, const std::string& id);

    void SetSize(const sf::Vector2f& size);
    void SetBody(BodyPtr&& body);
    void SetFlip(bool xFlip, bool yFlip = false);

    void ApplyForce(sf::Vector2f force);
    sf::Sprite& GetSprite();

    virtual void Update();
    virtual void Draw(sf::RenderWindow& window) const;
private:
    void updateSprite();

    BodyPtr m_rigidBody;
    sf::Vector2f m_velocity;

    sf::Sprite m_sprite;
    sf::Vector2f m_size;
    std::pair<bool, bool> m_flip = {false, false};
};

}
