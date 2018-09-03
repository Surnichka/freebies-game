#pragma once
#include <array>
#include <vector>
#include <string>

struct CharacterParser
{
public:
    void Parse();
    using CharacterKeys = std::array<std::string, 3>;
    std::vector<CharacterKeys> charactersKeys;

private:
    void parse(const std::string& directory, int depthLevel);
};
