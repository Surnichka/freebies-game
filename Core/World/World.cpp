#include "World.h"
#include "Box2D/Box2D.h"
#include "../Math/WorldConvertations.h"

namespace core
{

namespace config
{
    const b2Vec2 gravity = {0.0f, -9.8f};

    const constexpr float timeStep = 1.0f / 60.0f;
    const int32_t velocityIterations = 8;
    const int32_t positionIterations = 3;
}

void World::Init()
{
    m_world = std::make_unique<b2World>(config::gravity);
}

void World::Update()
{
    m_world->Step(config::timeStep, config::velocityIterations, config::positionIterations);
}

b2Body* World::CreatePolygonBody(const sf::FloatRect &rect, b2BodyType bodyType, Material material)
{
    b2BodyDef bodyDef;
    bodyDef.type = bodyType;
    bodyDef.position.Set(math::PixelToMeter(rect.left), math::PixelToMeter(rect.top) );

    b2PolygonShape shape;
    shape.SetAsBox(math::PixelToMeter(rect.width), math::PixelToMeter(rect.height));

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = material.density;
    fixtureDef.friction = material.friction;
    fixtureDef.restitution = material.restitution;

    b2Body* body = m_world->CreateBody(&bodyDef);
    body->CreateFixture(&fixtureDef);
    return body;
}

void World::DeleteFromWorld(b2Body *body)
{
    m_world->DestroyBody(body);
}

} //end of core
