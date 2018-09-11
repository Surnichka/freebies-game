#include "CharacterCreator.h"
#include "../AssetsParser/CharacterParser.h"
#include "../Application/Application.h"
#include "../Resources/Resources.h"
#include <SFML/Graphics/Texture.hpp>
#include "Animations.h"

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

        std::vector<std::string> textureIds;
        textureIds.reserve(texturePathList.size());
        for(const auto& path : texturePathList)
        {
            const auto& key = path;
            resources->Aquire(key, path);
            textureIds.emplace_back(key);
        }
        auto frameAnim = std::make_unique<FrameAnimation>(name, std::move(textureIds));
        character.AddAnimation(animId, std::move(frameAnim));
    }
    resources->Load();
    return character;
}

} //end of core
