#include "CharacterParser.h"
#include "experimental/filesystem"
#include <algorithm>

namespace core
{

namespace config
{
    const std::string directory = "../freebies-game/Assets/characters/";
    const std::vector<std::string> extensions = {".png"};
}

void CharacterParser::Parse()
{
    parse(config::directory, 0);
}

std::vector<std::string> CharacterParser::GetCharactersName() const
{
    std::vector<std::string> charactersName;
    charactersName.reserve(m_charactersMap.size());
    for(const auto& p : m_charactersMap)
    {
        charactersName.push_back(p.first);
    }
    return charactersName;
}

bool CharacterParser::HasCharacter(const std::string &characterName) const
{
    auto charNames = GetCharactersName();
    auto iter = std::find(charNames.begin(), charNames.end(), characterName);
    return (iter != charNames.end());
}

const CharacterParser::AnimIdMap& CharacterParser::GetAnimations(const std::string &characterName) const
{
    auto iter = m_charactersMap.find(characterName);
    if(iter == m_charactersMap.end())
    {
        static CharacterParser::AnimIdMap empty;
        return empty;
    }
    return iter->second;
}

const CharacterParser::TexturePathList& CharacterParser::GetTexturePaths(const std::string &characterName,
                                                                         const std::string &animId) const
{
    auto animations = GetAnimations(characterName);
    auto iter = animations.find(animId);
    if(iter == animations.end())
    {
        static CharacterParser::TexturePathList empty;
        return empty;
    }
    return iter->second;
}

void CharacterParser::parse(const std::string &directory, int depthLevel)
{
    namespace fs = std::experimental::filesystem;

    static std::string key;
    static std::string animId;

    for(const auto& entry : fs::directory_iterator(directory))
    {
        if(depthLevel == 0)
        {
            key = entry.path().stem();
        }
        else if(depthLevel == 1)
        {
            animId = entry.path().stem();
        }
        else if(depthLevel == 2)
        {
            if(fs::is_directory(entry))
            {
                throw std::runtime_error(std::string("Reaching depth 3, but find entry that is not regular file!")
                                         + "in directory: "
                                         + config::directory);
            }
            else
            {
                auto iter = std::find(config::extensions.begin(),
                                      config::extensions.end(),
                                      entry.path().extension().string());
                if(iter != config::extensions.end())
                {
                    std::string path = entry.path().string();
                    m_charactersMap[key][animId].insert(path);
                }
                else
                {
                    throw std::runtime_error(std::string("Finding regular file with non supported extension: "
                                                         + entry.path().extension().string()));
                }
            }
        }
        else
        {
            throw std::runtime_error("Parsing character directory: "
                                     + config::directory
                                     + ", that depth is more than: 3");
        }

        if(fs::is_directory(entry))
        {
            parse(entry.path(), (depthLevel + 1));
        }
    }
}

} //end of core
