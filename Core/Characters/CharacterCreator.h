#pragma once
#include "Character.h"

namespace core
{
class CharacterParser;
class CharacterCreator
{
public:
    void Init();
    Character Create(const std::string& name);
private:
    std::unique_ptr<CharacterParser> m_parser;
};

} //end of core
