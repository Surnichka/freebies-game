#pragma once
#include "Character.h"
#include "Character2.h"

namespace core
{
class CharacterParser;
class CharacterCreator
{
public:
    void Init();
    Character Create(const std::string& name);
    Character2 Create2(const std::string& name);
private:
    std::unique_ptr<CharacterParser> m_parser;
};

} //end of core
