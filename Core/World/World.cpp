#include "World.h"
#include "../AssetsParser/MapParser.h"
#include "../Resources/Resources.h"
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

void World2::Init()
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
    m_map.reserve(mapGrid.size() * mapGrid.front().size());
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

            m_map.emplace_back(Entity());
            m_map.back().SetSize({tileWidth, tileHeight});
            m_map.back().SetBody({posInWorld.x + tileWidth / 2,
                                  posInWorld.y + tileHeight / 2,
                                  tileWidth,
                                  tileHeight},
                                  b2_staticBody);
            m_map.back().SetTexture("map", "box");
        }
        posInWorld.x = 0;
    }

    m_character.SetSize({50, 50});
    m_character.SetBody({700, 100, 50, 50}, b2_dynamicBody);
    m_character.SetTexture("map", "box");
}

void World2::Update()
{
    sf::Vector2f bla;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) bla.x -= 10.0f;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) bla.x += 10.0f;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) bla.y -= 10.0f;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) bla.y += 10.0f;

//    m_character.ApplyForce({gravity.x, gravity.y});
    m_character.ApplyForce(bla);

    for(auto& tile : m_map)
    {
        tile.Update();
    }
    m_character.Update();
}

void World2::Draw(sf::RenderWindow &window)
{
    window.draw(m_background);
    for(const auto& tile : m_map)
    {
        tile.Draw(window);
    }
    m_character.Draw(window);
}


} //end of core
