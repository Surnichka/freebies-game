#include "World.h"
#include "../AssetsParser/MapParser.h"
#include "../Resources/Resources.h"
#include "../Application/Application.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Event.hpp>

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

            mapResources->Aquire(texturePath, texturePath);
            auto& texture = mapResources->Get(texturePath);

            Entity entity;

            sf::Vector2f tileScale = {1.0f, 1.0f};
            if (texturePath == "../freebies-game/Assets/Box.png")
            {
                tileScale = {(tileWidth / texture.getSize().x),
                             (tileHeight / texture.getSize().y)};
                entity.name = "box";
            }
            else
            {
                entity.name = "tree";
            }
            entity.setTexture(&texture);
            entity.setPosition(posInWorld);
            entity.setScale(tileScale);
            entity.setBody(entity.getGlobalBounds(), b2BodyType::b2_staticBody);

            m_map.emplace_back(std::move(entity));
        }
        posInWorld.x = 0;
    }

    Entity entity;
    entity.name = "lqlq";
    entity.setTexture(&(mapResources->Get("../freebies-game/Assets/Box.png")));
    entity.setPosition(700, 0);
    entity.setScale({0.3f, 0.3f});
    entity.setBody(entity.getGlobalBounds(), b2BodyType::b2_dynamicBody);

    m_map.emplace_back(std::move(entity));
}

void World::Update()
{
    sf::Vector2f bla;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) bla.x -= 5.0f;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) bla.x += 5.0f;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) bla.y -= 5.0f;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) bla.y += 5.0f;

    for(auto& tile : m_map)
    {
        if(tile.name == "lqlq")
        {
            tile.applyForce(config::gravity);
//            tile.applyForce(bla);
        }
        tile.update(m_map);
    }
}

void World::Draw(sf::RenderWindow &window)
{
    window.draw(m_background);
    for(const auto& tile : m_map)
    {
        window.draw(tile);
    }
}


} //end of core
