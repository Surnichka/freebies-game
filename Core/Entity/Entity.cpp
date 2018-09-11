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

void Entity::SetSize(const sf::Vector2f &size)
{
    m_size = size;
}

void Entity::SetBody(const sf::FloatRect &box, b2BodyType bodyType)
{
    m_debugBox.setPosition(box.left, box.top);
    m_debugBox.setOrigin(box.width / 2, box.height / 2);
    m_debugBox.setSize({box.width, box.height});
    m_debugBox.setFillColor({255, 0, 0, 100});
    m_debugBox.setOutlineColor(sf::Color::Black);
    m_debugBox.setOutlineThickness(1.0f);

    m_rigidBody = Application::Get().physicWorld->CreateBox(box, bodyType);
    updateSprite();
}

void Entity::SetFlip(bool xFlip, bool yFlip)
{
    m_flip = {xFlip, yFlip};
    auto scale = m_sprite.getScale();
    if((true  == xFlip) && (scale.x > 0.0f)) scale.x = -scale.x;
    if((false == xFlip) && (scale.x < 0.0f)) scale.x = -scale.x;
    if((true  == yFlip) && (scale.y > 0.0f)) scale.y = -scale.y;
    if((false == yFlip) && (scale.y < 0.0f)) scale.y = -scale.y;
    m_sprite.setScale(scale);
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
        m_debugBox.setPosition({xPos, yPos});
    }

    m_velocity = sf::Vector2f();
}

void Entity::Draw(sf::RenderWindow &window) const
{
    window.draw(m_sprite);
    window.draw(m_debugBox);
}

void Entity::updateSprite()
{
    if((nullptr != m_sprite.getTexture()) && (m_size != sf::Vector2f()))
    {
        const auto& width = m_sprite.getLocalBounds().width;
        const auto& height = m_sprite.getLocalBounds().height;

        m_sprite.setOrigin(width / 2, height / 2);

        auto xScale = (m_size.x / width);
        auto yScale = (m_size.y / height);

        xScale = m_flip.first ? -xScale : xScale;
        yScale = m_flip.second ? -yScale : yScale;
        m_sprite.setScale(xScale, yScale);
    }
}

} //end of core
