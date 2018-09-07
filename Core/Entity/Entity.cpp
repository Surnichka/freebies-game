#include "Entity.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include "../Application/Application.h"
#include "../Math/WorldConvertations.h"
#include "../Math/RangeMap.h"
#include "../Math/Math.h"
#include "../World/PWorld.h"
#include <cmath>

namespace core
{
////////////////////////////////////////////////////////////////////////////////////////////////
//void Entity::setTexture(const TextureWrapper::Ptr& textureWrapper)
//{
//    m_textureWrapper = textureWrapper;
//}

Entity::~Entity()
{
//    if( nullptr != m_body )
//    {
//        Application::Get().physicWorld->DeleteFromWorld(m_body);
//    }
}

void Entity::setBody(sf::FloatRect rect, b2BodyType bodyType)
{
    m_body = Application::Get().physicWorld->CreatePolygonBody(rect, bodyType);
}

void Entity::setTexture(const sf::Texture* texture)
{
    m_texture = texture;
    updateTextures();
}
////////////////////////////////////////////////////////////////////////////////////////////////
void Entity::setTextureRect(const sf::FloatRect& rect)
{
    if(m_textureRect != rect)
    {
        m_textureRect = rect;
        updatePositions();
        updateTexCoords();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////
void Entity::setColor(const sf::Color& color)
{
   m_vertices[0].color = color;
   m_vertices[1].color = color;
   m_vertices[2].color = color;
   m_vertices[3].color = color;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//const TextureWrapper::Ptr& Entity::getTexture() const
//{
//    return m_textureWrapper;
//}
const sf::Texture* Entity::getTeture() const
{
    return m_texture;
}

////////////////////////////////////////////////////////////////////////////////////////////////
const sf::FloatRect& Entity::getTextureRect() const
{
    return m_textureRect;
}

////////////////////////////////////////////////////////////////////////////////////////////////
sf::Color Entity::getColor() const
{
    return m_vertices[0].color;
}

void Entity::applyForce(sf::Vector2f force)
{
    m_velocity += force;

    b2Vec2 vel = m_body->GetLinearVelocity();
    float dvx = force.x - vel.x;
    float dvy = force.y - vel.y;
    float mass = m_body->GetMass();
    m_body->ApplyLinearImpulse( b2Vec2(mass * dvx,mass * dvy),
               m_body->GetWorldCenter(), true );

}

void Entity::update(std::vector<Entity>& entities)
{
    updateTextures();
    //resolveCollisions(entities);
    setPosition({math::MeterToPixel(m_body->GetPosition().x),
                 math::MeterToPixel(m_body->GetPosition().y)});
    setRotation(math::RadiansToDegree(m_body->GetAngle()));
}

////////////////////////////////////////////////////////////////////////////////////////////////
sf::FloatRect Entity::getGlobalBounds() const
{
    return getTransform().transformRect(getTextureRect());
}

////////////////////////////////////////////////////////////////////////////////////////////////
void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
//    bool validTexture = m_textureWrapper->texture != nullptr;

//    if(validTexture)
//    {
//        states.transform *= getTransform();
//        states.texture = m_textureWrapper->texture.get();
//        target.draw(m_vertices, 4, sf::TriangleStrip, states);
//    }

    bool validTexture = m_texture != nullptr;

    if(validTexture)
    {
        states.transform *= getTransform();
        states.texture = m_texture;
        target.draw(m_vertices, 4, sf::TriangleStrip, states);
    }
}

void Entity::resolveCollisions(std::vector<Entity>& entities)
{

    move(m_velocity);
    m_velocity = sf::Vector2f();
}

void Entity::updateTextures()
{
//    bool validTexture = m_textureWrapper->texture != nullptr;
//    bool invalidRect = m_textureRect == sf::FloatRect();

//    if(validTexture && invalidRect)
//    {
//        auto textureRect = sf::FloatRect(0, 0,
//                                         m_textureWrapper->texture->getSize().x,
//                                         m_textureWrapper->texture->getSize().y);

//        setTextureRect(std::move(textureRect));
//    }
//    else
//    {
//        m_textureRect = sf::FloatRect();
//    }


    bool validTexture = m_texture != nullptr;
    bool invalidRect = m_textureRect == sf::FloatRect();

    if(validTexture && invalidRect)
    {
        auto textureRect = sf::FloatRect(0, 0,
                                         m_texture->getSize().x,
                                         m_texture->getSize().y);

        setTextureRect(std::move(textureRect));
    }
//    else
//    {
//        m_textureRect = sf::FloatRect();
//    }
}

////////////////////////////////////////////////////////////////////////////////////////////////
void Entity::updatePositions()
{
    m_vertices[0].position = sf::Vector2f(0, 0);
    m_vertices[1].position = sf::Vector2f(0, m_textureRect.height);
    m_vertices[2].position = sf::Vector2f(m_textureRect.width, 0);
    m_vertices[3].position = sf::Vector2f(m_textureRect.width, m_textureRect.height);
}

////////////////////////////////////////////////////////////////////////////////////////////////
void Entity::updateTexCoords()
{
    float left   = m_textureRect.left;
    float right  = left + m_textureRect.width;
    float top    = m_textureRect.top;
    float bottom = top + m_textureRect.height;

    m_vertices[0].texCoords = sf::Vector2f(left, top);
    m_vertices[1].texCoords = sf::Vector2f(left, bottom);
    m_vertices[2].texCoords = sf::Vector2f(right, top);
    m_vertices[3].texCoords = sf::Vector2f(right, bottom);
}
}

