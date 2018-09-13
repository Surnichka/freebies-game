#include "World.h"
#include "../AssetsParser/MapParser.h"
#include "../Resources/Resources.h"
#include "../Animator/AnimatorFactory.h"
#include "../Application/Application.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Event.hpp>
#include "PhysicWorld.h"
#include "Box2D/Dynamics/b2World.h"

namespace core
{

namespace config
{
    const sf::Vector2f gravity = {0.0f, 10.0f};
}

void World::Init()
{
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
    m_tiles.reserve(mapGrid.size() * mapGrid.front().size());
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

            m_tiles.emplace_back(Entity());
            m_tiles.back().SetSize({tileWidth, tileHeight});
            m_tiles.back().SetBody({posInWorld.x + tileWidth / 2,
                                  posInWorld.y + tileHeight / 2,
                                  tileWidth,
                                  tileHeight},
                                  b2_staticBody);
            m_tiles.back().SetTexture("map", "box");
        }
        posInWorld.x = 0;
    }
}

void World::Update()
{
    for(auto& tile : m_tiles)
    {
        tile.Update();
    }
}

void World::Draw(sf::RenderWindow &window)
{
    window.draw(m_background);
    for(const auto& tile : m_tiles)
    {
        tile.Draw(window);
    }
}

//Character World::CreateCharacter(const std::string& name,
//                                 const sf::Vector2f& pos,
//                                 const sf::Vector2f& characterSize,
//                                 const sf::Vector2f& rigidBodySize,
//                                 b2BodyType bodyType)
//{
//    core::Character character;
//    character.Init();
//    character.m_animator = Application::Get().animatorFactory->Create(name);
//    character.SetSize(characterSize);
//    character.SetBody({pos.x, pos.y, rigidBodySize.x, rigidBodySize.y}, bodyType);
//    return character;
//}


} //end of core
