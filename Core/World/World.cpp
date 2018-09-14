#include "World.h"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Event.hpp>

#include <Box2D/Box2D.h>

#include "../Application/Application.h"
#include "../AssetsParser/MapParser.h"
#include "../Animator/AnimatorFactory.h"
#include "../Resources/Resources.h"
#include "PhysicWorldUtils.h"

namespace core
{

namespace config
{
    const b2Vec2 gravity = {0.0f, 0.0f};
    const constexpr float timeStep = 1.0f / 60.0f;
    const int32_t velocityIterations = 8;
    const int32_t positionIterations = 3;
}

void World::Init()
{
    m_physicWorld = std::make_unique<b2World>(config::gravity);

    MapParser parser;
    parser.Parse();

    auto windowSize = Application::Get().windowSize;
    auto mapResources = Application::Get().resources->GetHolder<sf::Texture>("map");
    {
        mapResources->Aquire("background", "../freebies-game/Assets/BACKGROUND.png");
        auto& texture = mapResources->Get("background");

        sf::Vector2f scale((windowSize.x / texture.getSize().x),
                           (windowSize.y / texture.getSize().y));

        m_background.setTexture(texture);
        m_background.setScale(scale);
    }

    const auto& mapGrid = parser.GetMapGrid();
    m_entities.reserve(mapGrid.size() * mapGrid.front().size());
    float tileWidth = windowSize.x / mapGrid.cbegin()->size();
    float tileHeight = windowSize.y / mapGrid.size();

    sf::Vector2f posInWorld;
    for(size_t rowIdx = 0; rowIdx < mapGrid.size(); rowIdx++)
    {
        posInWorld.y = tileHeight * rowIdx;
        for(size_t colIdx = 0; colIdx < mapGrid[rowIdx].size(); colIdx++)
        {
            posInWorld.x = tileWidth * colIdx;

            const auto& texturePath = mapGrid[rowIdx][colIdx];
            if(texturePath.empty())
            {
                continue;
            }

            mapResources->Aquire("box", texturePath);

            m_entities.emplace_back(Entity());
            m_entities.back().SetSize({tileWidth, tileHeight});

            auto tileBody = createTileBox({posInWorld.x + tileWidth / 2,
                                           posInWorld.y + tileHeight / 2,
                                           tileWidth,
                                           tileHeight});

            m_entities.back().SetBody( std::move(tileBody) );
            m_entities.back().SetTexture("map", "box");
        }
        posInWorld.x = 0;
    }
}

void World::Update()
{
    GetPhysicWorld()->Step(config::timeStep, config::positionIterations, config::velocityIterations);
    for(auto& entity : m_entities)
    {
        entity.Update();
    }
}

void World::Draw(sf::RenderWindow &window)
{
    window.draw(m_background);
    for(const auto& entity : m_entities)
    {
        entity.Draw(window);
    }
}

std::unique_ptr<b2World>& World::GetPhysicWorld()
{
    return m_physicWorld;
}

Character World::CreateCharacter(const std::string &name,
                                 sf::FloatRect spriteRect,
                                 sf::Vector2f rigidBodySize)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2BodyType::b2_dynamicBody;
    bodyDef.fixedRotation = true;
    bodyDef.position.Set(PixelToMeter(spriteRect.left), PixelToMeter(spriteRect.top) );

    b2PolygonShape shape;
    shape.SetAsBox(PixelToMeter(rigidBodySize.x / 2), PixelToMeter(rigidBodySize.y / 2));

    b2FixtureDef bodyFixtureDef;
    bodyFixtureDef.shape = &shape;
    bodyFixtureDef.density = 1.0f;
    bodyFixtureDef.userData = const_cast<void*>(static_cast<const void*>(&fixtureTypes::bodyBox));

    BodyPtr body( GetPhysicWorld()->CreateBody(&bodyDef) );
    body->CreateFixture(&bodyFixtureDef);

    shape.SetAsBox(PixelToMeter(rigidBodySize.x / 3),
                   PixelToMeter(10.0f), b2Vec2{0.0f, 1.45f}, 0);

    b2FixtureDef footSensorDef;
    footSensorDef.shape = &shape;
    footSensorDef.isSensor = true;
    footSensorDef.userData = const_cast<void*>(static_cast<const void*>(&fixtureTypes::footSensor));
    body->CreateFixture(&footSensorDef);

    shape.SetAsBox(PixelToMeter(rigidBodySize.x / 2),
                   PixelToMeter(5.0f), b2Vec2{0.0f, -1.3f}, 0);
    b2FixtureDef headSensorDef;
    headSensorDef.shape = &shape;
    headSensorDef.isSensor = true;
    headSensorDef.userData = const_cast<void*>(static_cast<const void*>(&fixtureTypes::headSensor));
    body->CreateFixture(&headSensorDef);

    Animator animator = Application::Get().animatorFactory->Create(name);

    Character character;
    character.Init(std::move(animator));
    character.SetSize({spriteRect.width, spriteRect.height});
    character.SetBody(std::move(body));

    return character;
}

BodyPtr World::createTileBox(sf::FloatRect rect)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2BodyType::b2_staticBody;
    bodyDef.position.Set(PixelToMeter(rect.left), PixelToMeter(rect.top) );

    b2PolygonShape shape;
    shape.SetAsBox(PixelToMeter(rect.width / 2), PixelToMeter(rect.height / 2));

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.userData = const_cast<void*>(static_cast<const void*>(&fixtureTypes::bodyBox));

    BodyPtr body( GetPhysicWorld()->CreateBody(&bodyDef) );
    body->CreateFixture(&fixtureDef);

    return body;
}

} //end of core
