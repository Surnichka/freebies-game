#pragma once
#include <libs/resource_mgr/TextureWrapper.h>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <chrono>
#include <experimental/optional>

namespace libs
{

class Sprite : public sf::Drawable, public sf::Transformable
{
public:
    Sprite() = default;
    explicit Sprite(const TextureWrapper::Ptr& textureWrapper);
    Sprite(const TextureWrapper::Ptr& textureWrapper, const sf::FloatRect& rect);

    void setTexture(const TextureWrapper::Ptr& textureWrapper);
    void setTextureRect(const sf::FloatRect& rect);
    void setColor(const sf::Color& color);

    const TextureWrapper::Ptr& getTexture() const;
    const sf::FloatRect& getTextureRect() const;
    sf::FloatRect getGlobalBounds() const;
    sf::Color getColor() const;

    void update(std::chrono::milliseconds);
    float xWeight = 0.0f;

////////////////////////////////////////////////////////////////////////////////////////////////
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void updatePositions();
    void updateTexCoords();
////////////////////////////////////////////////////////////////////////////////////////////////
    TextureWrapper::Ptr m_textureWrapper;
    sf::Vertex m_vertices[4];
    sf::FloatRect m_textureRect;
};

}//end of libs
