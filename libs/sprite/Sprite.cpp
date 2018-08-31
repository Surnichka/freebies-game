#include "Sprite.h"
#include <SFML/Graphics/RenderTarget.hpp>

namespace libs
{
////////////////////////////////////////////////////////////////////////////////////////////////
Sprite::Sprite(const TextureWrapper::Ptr& textureWrapper)
{
    setTexture(textureWrapper);
}

////////////////////////////////////////////////////////////////////////////////////////////////
Sprite::Sprite(const TextureWrapper::Ptr& textureWrapper, const sf::FloatRect& rect)
{
    setTexture(textureWrapper);
    setTextureRect(rect);
}

////////////////////////////////////////////////////////////////////////////////////////////////
void Sprite::setTexture(const TextureWrapper::Ptr& textureWrapper)
{
    m_textureWrapper = textureWrapper;
}

////////////////////////////////////////////////////////////////////////////////////////////////
void Sprite::setTextureRect(const sf::FloatRect& rect)
{
    if(m_textureRect != rect)
    {
        m_textureRect = rect;
        updatePositions();
        updateTexCoords();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////
void Sprite::setColor(const sf::Color& color)
{
   m_vertices[0].color = color;
   m_vertices[1].color = color;
   m_vertices[2].color = color;
   m_vertices[3].color = color;
}

////////////////////////////////////////////////////////////////////////////////////////////////
const TextureWrapper::Ptr& Sprite::getTexture() const
{
    return m_textureWrapper;
}

////////////////////////////////////////////////////////////////////////////////////////////////
const sf::FloatRect& Sprite::getTextureRect() const
{
    return m_textureRect;
}

////////////////////////////////////////////////////////////////////////////////////////////////
sf::Color Sprite::getColor() const
{
    return m_vertices[0].color;
}

void Sprite::update(std::chrono::milliseconds)
{
    bool validTexture = m_textureWrapper->texture != nullptr;
    bool invalidRect = m_textureRect == sf::FloatRect();

    if(validTexture && invalidRect)
    {
        auto textureRect = sf::FloatRect(0, 0,
                                         m_textureWrapper->texture->getSize().x,
                                         m_textureWrapper->texture->getSize().y);

        setTextureRect(std::move(textureRect));
    }
    else
    {
        m_textureRect = sf::FloatRect();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////
sf::FloatRect Sprite::getGlobalBounds() const
{
    return getTransform().transformRect(getTextureRect());
}

////////////////////////////////////////////////////////////////////////////////////////////////
void Sprite::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    bool validTexture = m_textureWrapper->texture != nullptr;

    if(validTexture)
    {
        states.transform *= getTransform();
        states.texture = m_textureWrapper->texture.get();
        target.draw(m_vertices, 4, sf::TriangleStrip, states);

//        sf::Vertex vert[4];
//        vert[0] = m_vertices[0]; vert[0].color = sf::Color::Black;
//        vert[1] = m_vertices[1]; vert[1].color = sf::Color::Black;
//        vert[2] = m_vertices[2]; vert[2].color = sf::Color::Black;
//        vert[3] = m_vertices[3]; vert[3].color = sf::Color::Black;

//        states.texture = nullptr;
//        target.draw(vert, 4, sf::LineStrip, states);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////
void Sprite::updatePositions()
{
    m_vertices[0].position = sf::Vector2f(xWeight, 0);
    m_vertices[1].position = sf::Vector2f(0, m_textureRect.height);
    m_vertices[2].position = sf::Vector2f(m_textureRect.width + xWeight, 0);
    m_vertices[3].position = sf::Vector2f(m_textureRect.width, m_textureRect.height);
}

////////////////////////////////////////////////////////////////////////////////////////////////
void Sprite::updateTexCoords()
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

} //end of libs
