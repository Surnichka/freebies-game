#include "AnimatorFactory.h"

#include <SFML/Graphics/Texture.hpp>

#include "../Application/Application.h"
#include "../AssetsParser/CharacterParser.h"
#include "../Resources/Resources.h"

#include "../Animations/AnimationSequence.h"
namespace core
{

void AnimatorFactory::Init()
{
    m_parser = std::make_unique<CharacterParser>();
    m_parser->Parse();
}

Animator AnimatorFactory::Create(const std::string &name)
{
    if( false == m_parser->HasCharacter(name) )
    {
        throw std::runtime_error("Trying to create character: " + name + ", that doesn't exist!");
    }

    auto resources = Application::Get().resources->GetHolder<sf::Texture>(name);

    Animator animator;
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
        auto frameAnim = std::make_unique<AnimationSequence>(name, std::move(textureIds));
        animator.AddAnimation(animId, std::move(frameAnim));
    }
    resources->Load();
    return animator;
}

} //end of core
