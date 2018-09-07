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
                continue;
            }
            entity.setTexture(&texture);
            entity.setPosition(posInWorld.x + (tileWidth / 2),
                               posInWorld.y + (tileHeight / 2));
            entity.setOrigin(tileWidth / 2, tileHeight / 2);
            entity.setScale(tileScale);
            sf::FloatRect box = {entity.getPosition().x,
                                 entity.getPosition().y,
                                 entity.getGlobalBounds().width,
                                 entity.getGlobalBounds().height};

//            if(entity.name == "box")
            {
                b2BodyType bType = (rowIdx == mapGrid.size() - 1) ? b2_staticBody : b2_dynamicBody;
                entity.setBody(box, b2_staticBody);
            }

            m_map.emplace_back(std::move(entity));
        }
        posInWorld.x = 0;
    }

    Entity entity;
    entity.name = "lqlq";
    entity.setTexture(&(mapResources->Get("../freebies-game/Assets/Box.png")));
    entity.setPosition(640, 0);
    entity.setOrigin(tileWidth / 2, tileHeight / 2);
    entity.setScale({0.5f, 0.5f});
    sf::FloatRect box = {entity.getPosition().x,
                         entity.getPosition().y,
                         entity.getGlobalBounds().width,
                         entity.getGlobalBounds().height};
    entity.setBody(box, b2BodyType::b2_dynamicBody);

    m_map.emplace_back(std::move(entity));
}

void World::Update()
{
    sf::Vector2f bla;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) bla.x -= 30.0f;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) bla.x += 30.0f;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) bla.y -= 30.0f;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) bla.y += 30.0f;

    for(auto& tile : m_map)
    {
        if(tile.name == "lqlq")
        {
//            tile.applyForce(config::gravity);
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
