#include "PhysicDebugDraw.h"
#include <SFML/Graphics/Color.hpp>
#include "../Math/WorldConvertations.h"

namespace core
{

namespace helper
{
    sf::Color b2ColorToSFML(const b2Color &color, sf::Uint8 alpha = 255)
    {
        return sf::Color(static_cast<sf::Uint8>(color.r * 255),
                         static_cast<sf::Uint8>(color.g * 255),
                         static_cast<sf::Uint8>(color.b * 255),
                         alpha);
    }

    sf::Vector2f b2VecToSFML(const b2Vec2& vec)
    {
        return {math::MeterToPixel(vec.x), math::MeterToPixel(vec.y)};
    }
}

PhysicDebugDraw::PhysicDebugDraw(sf::RenderWindow &window)
    : m_windowRef(window)
{
//    e_shapeBit				= 0x0001,	///< draw shapes
//    e_jointBit				= 0x0002,	///< draw joint connections
//    e_aabbBit				= 0x0004,	///< draw axis aligned bounding boxes
//    e_pairBit				= 0x0008,	///< draw broad-phase pairs
//    e_centerOfMassBit		= 0x0010
    b2Draw::SetFlags(e_shapeBit);
}

void PhysicDebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
    sf::ConvexShape polygon((size_t(vertexCount)));
    sf::Vector2f center;
    for(int i = 0; i < vertexCount; i++)
    {
        sf::Vector2f transformedVec = helper::b2VecToSFML(vertices[i]);
        polygon.setPoint(size_t(i), sf::Vector2f(std::floor(transformedVec.x), std::floor(transformedVec.y))); // flooring the coords to fix distorted lines on flat surfaces
    }																								   // they still show up though.. but less frequently
    polygon.setOutlineThickness(-1.f);
    polygon.setFillColor(sf::Color::Transparent);
    polygon.setOutlineColor(helper::b2ColorToSFML(color));

    m_windowRef.draw(polygon);
}
void PhysicDebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
    sf::ConvexShape polygon((size_t(vertexCount)));
    for(int i = 0; i < vertexCount; i++)
    {
        sf::Vector2f transformedVec = helper::b2VecToSFML(vertices[i]);
        polygon.setPoint(size_t(i), sf::Vector2f(std::floor(transformedVec.x), std::floor(transformedVec.y)));
    }
    polygon.setOutlineThickness(-1.0f);
    polygon.setFillColor(helper::b2ColorToSFML(color, 60));
    polygon.setOutlineColor(sf::Color::Blue);

    m_windowRef.draw(polygon);
}
void PhysicDebugDraw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
{
    sf::CircleShape circle(math::MeterToPixel(radius));
    circle.setOrigin(math::MeterToPixel(radius), math::MeterToPixel(radius));
    circle.setPosition(helper::b2VecToSFML(center));
    circle.setFillColor(sf::Color::Transparent);
    circle.setOutlineThickness(-1.f);
    circle.setOutlineColor(helper::b2ColorToSFML(color));

    m_windowRef.draw(circle);
}
void PhysicDebugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
{
    sf::CircleShape circle(math::MeterToPixel(radius));
    circle.setOrigin(math::MeterToPixel(radius), math::MeterToPixel(radius));
    circle.setPosition(helper::b2VecToSFML(center));
    circle.setFillColor(helper::b2ColorToSFML(color, 60));
    circle.setOutlineThickness(1.f);
    circle.setOutlineColor(helper::b2ColorToSFML(color));

    b2Vec2 endPoint = center + radius * axis;
    sf::Vertex line[2] =
    {
        sf::Vertex(helper::b2VecToSFML(center), helper::b2ColorToSFML(color)),
        sf::Vertex(helper::b2VecToSFML(endPoint), helper::b2ColorToSFML(color)),
    };

    m_windowRef.draw(circle);
    m_windowRef.draw(line, 2, sf::Lines);
}
void PhysicDebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
    sf::Vertex line[] =
    {
        sf::Vertex(helper::b2VecToSFML(p1), helper::b2ColorToSFML(color)),
        sf::Vertex(helper::b2VecToSFML(p2), helper::b2ColorToSFML(color))
    };

    m_windowRef.draw(line, 2, sf::Lines);
}
void PhysicDebugDraw::DrawTransform(const b2Transform& xf)
{
    float lineLength = 0.4f;

    b2Vec2 xAxis = xf.p + lineLength * xf.q.GetXAxis();
    sf::Vertex redLine[] =
    {
        sf::Vertex(helper::b2VecToSFML(xf.p), sf::Color::Red),
        sf::Vertex(helper::b2VecToSFML(xAxis), sf::Color::Red)
    };

    b2Vec2 yAxis = xf.p + lineLength * xf.q.GetYAxis();
    sf::Vertex greenLine[] =
    {
        sf::Vertex(helper::b2VecToSFML(xf.p), sf::Color::Green),
        sf::Vertex(helper::b2VecToSFML(yAxis), sf::Color::Green)
    };

    m_windowRef.draw(redLine, 2, sf::Lines);
    m_windowRef.draw(greenLine, 2, sf::Lines);
}

} //end of core
