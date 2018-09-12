#pragma once
#include <Box2D/Common/b2Draw.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>

namespace core
{

class PhysicDebugDraw : public b2Draw
{
public:
    explicit PhysicDebugDraw(sf::RenderWindow& window);

    void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override;
    void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override;
    void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color) override;
    void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color) override;
    void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) override;
    void DrawTransform(const b2Transform& xf) override;
private:
    sf::RenderWindow& m_windowRef;
};

} //end of core
