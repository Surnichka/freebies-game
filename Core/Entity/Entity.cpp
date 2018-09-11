#include "Entity.h"
#include "../Application/Application.h"
#include "../World/PhysicWorld.h"
#include "../Math/WorldConvertations.h"
#include "../Resources/Resources.h"
#include "SFML/Graphics/Texture.hpp"

namespace core
{

Entity::~Entity()
{
    if(nullptr != m_rigidBody)
    {
        Application::Get().physicWorld->RemoveFromWorld(m_rigidBody);
    }
}

void Entity::SetTexture(const std::string& holder, const std::string &id)
{
    const auto& texture = Application::Get().resources->GetHolder<sf::Texture>(holder)->Get(id);
    m_sprite.setTexture(texture);
    updateSprite();
}

void Entity::SetBody(const sf::FloatRect &box, b2BodyType bodyType)
{
    m_textureRect = box;
    m_rigidBody = Application::Get().physicWorld->CreateBox(box, bodyType);
    updateSprite();
}

void Entity::ApplyForce(sf::Vector2f force)
{
    m_velocity += force;
}

void Entity::Update()
{
    if(nullptr != m_rigidBody)
    {
        m_rigidBody->SetLinearVelocity({m_velocity.x, m_velocity.y});

        auto xPos = math::MeterToPixel(m_rigidBody->GetPosition().x);
        auto yPos = math::MeterToPixel(m_rigidBody->GetPosition().y);
        m_sprite.setPosition({xPos, yPos});
    }

    m_velocity = sf::Vector2f();
}

void Entity::Draw(sf::RenderWindow &window) const
{
    window.draw(m_sprite);
}

void Entity::updateSprite()
{
    if((nullptr != m_sprite.getTexture()) && (m_textureRect != sf::FloatRect()))
    {
        const auto& width = m_sprite.getLocalBounds().width;
        const auto& height = m_sprite.getLocalBounds().height;

        m_sprite.setOrigin(width / 2, height / 2);
        m_sprite.setScale((m_textureRect.width / width), (m_textureRect.height / height));
    }
}

} //end of core
