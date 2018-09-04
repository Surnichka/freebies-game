#pragma once
#include <vector>
#include <set>
#include <string>
#include <map>
#include "../Math/NaturalCompare.h"

namespace core
{

struct CharacterParser
{
public:
    using TexturePathList = std::set<std::string, math::NaturalCompare>;
    using AnimIdMap = std::map<std::string, TexturePathList>;
    using CharacterNameMap = std::map<std::string, AnimIdMap>;

    void Parse();

    std::vector<std::string> GetCharactersName() const;
    const AnimIdMap& GetAnimations(const std::string& characterName) const;
    const TexturePathList& GetTexturePaths(const std::string& characterName, const std::string& animId) const;
    bool HasCharacter(const std::string& characterName) const;
private:
    void parse(const std::string& directory, int depthLevel);

    CharacterNameMap m_charactersMap;
};

} //end of core
