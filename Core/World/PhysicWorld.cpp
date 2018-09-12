#include "PhysicWorld.h"
#include "Box2D/Box2D.h"
#include "../Math/WorldConvertations.h"

namespace core
{

namespace config
{
    const b2Vec2 gravity = {0.0f, 0.0f};
    const constexpr float timeStep = 1.0f / 60.0f;
    const int32_t velocityIterations = 50;
    const int32_t positionIterations = 50;
}

void PhysicWorld::Init()
{
    m_world = std::make_unique<b2World>(config::gravity);
}

void PhysicWorld::Update()
{
    m_world->Step(config::timeStep, config::velocityIterations, config::positionIterations);
}

b2Body* PhysicWorld::CreateBox(const sf::FloatRect &rect, b2BodyType bodyType)
{
    Material material = Material::Default;

    b2BodyDef bodyDef;
    bodyDef.type = bodyType;
    bodyDef.position.Set(math::PixelToMeter(rect.left), math::PixelToMeter(rect.top) );

    b2PolygonShape shape;
    shape.SetAsBox(math::PixelToMeter(rect.width / 2), math::PixelToMeter(rect.height / 2));

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = material.density;
    fixtureDef.friction = material.friction;
    fixtureDef.restitution = material.restitution;

    b2Body* body = m_world->CreateBody(&bodyDef);
    body->CreateFixture(&fixtureDef);
    return body;
}

void PhysicWorld::RemoveFromWorld(b2Body *body)
{
    m_world->DestroyBody(body);
}

std::unique_ptr<b2World> &PhysicWorld::GetB2World()
{
    return m_world;
}

} //end of core
