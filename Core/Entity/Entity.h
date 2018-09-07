#pragma once
#include "TextureWrapper.h"
#include <Box2D/Dynamics/b2Body.h>

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Vertex.hpp>

#include <functional>
#include <vector>
#include <chrono>

namespace core
{

class Entity : public sf::Drawable, public sf::Transformable
{
public:
    std::string name;
    virtual ~Entity() override;
    void setBody(sf::FloatRect rect, b2BodyType bodyType);
///////////////////////////////////////////////////////////////////////////////
//    void setTexture(const TextureWrapper::Ptr& textureWrapper);
    void setTexture(const sf::Texture* texture);
    void setTextureRect(const sf::FloatRect& rect);
    void setColor(const sf::Color& color);

//    const TextureWrapper::Ptr& getTexture() const;
    const sf::Texture* getTeture() const;
    const sf::FloatRect& getTextureRect() const;
    sf::FloatRect getGlobalBounds() const;
    sf::Color getColor() const;

    ///This will check for collision
    void applyForce(sf::Vector2f force);

    void update(std::vector<Entity>& entities);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    b2Body* m_body = nullptr;
private:
    void resolveCollisions(std::vector<Entity>& entities);
    void updateTextures();
    void updatePositions();
    void updateTexCoords();
////////////////////////////////////////////////////////////////////////////////////////////////
//    TextureWrapper::Ptr m_textureWrapper;
    const sf::Texture* m_texture;
    sf::Vertex m_vertices[4];
    sf::FloatRect m_textureRect;
    sf::Vector2f m_velocity;
};

} //end of core
