#include "CharacterCreator.h"
#include "../AssetsParser/CharacterParser.h"
#include "../Application/Application.h"
#include "../Resources/Resources.h"
#include <SFML/Graphics/Texture.hpp>
#include "FrameAnimation.h"

namespace core
{

void CharacterCreator::Init()
{
    m_parser = std::make_unique<CharacterParser>();
    m_parser->Parse();
}

Character CharacterCreator::Create(const std::string &name)
{
    if( false == m_parser->HasCharacter(name) )
    {
        throw std::runtime_error("Trying to create character: " + name + ", that doesn't exist!");
    }

    auto resources = Application::Get().resources->GetHolder<sf::Texture>(name);

    Character character;
    const auto& animMap = m_parser->GetAnimations(name);
    for(const auto& p : animMap)
    {
        const auto& animId = p.first;
        const auto& texturePathList = p.second;

        std::vector<sf::Sprite> frames;
        frames.reserve(texturePathList.size());
        for(const auto& path : texturePathList)
        {
            const auto& key = path;
            resources->Aquire(key, path);
            auto& texture = resources->Get(key);
            frames.emplace_back(sf::Sprite(texture));
        }
        character.AddAnimation(animId, frames);
    }
    return character;
}

Character2 CharacterCreator::Create2(const std::string &name)
{
    if( false == m_parser->HasCharacter(name) )
    {
        throw std::runtime_error("Trying to create character: " + name + ", that doesn't exist!");
    }

    auto resources = Application::Get().resources->GetHolder<sf::Texture>(name);

    Character2 character;

    const auto& animMap = m_parser->GetAnimations(name);
    for(const auto& p : animMap)
    {
        const auto& animId = p.first;
        const auto& texturePathList = p.second;

        std::vector<sf::Sprite> frames;
        frames.reserve(texturePathList.size());
        for(const auto& path : texturePathList)
        {
            const auto& key = path;
            resources->Aquire(key, path);
            auto& texture = resources->Get(key);
            frames.emplace_back(sf::Sprite(texture));
        }
        auto animation = std::make_unique<FrameAnimation>(frames);
        character.AddAnimation(animId, std::move(animation));
    }

    return character;
}

} //end of core
