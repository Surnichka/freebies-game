#pragma once
#include "Animator.h"
#include <memory>

namespace core
{

class CharacterParser;
struct AnimatorFactory
{
public:
    void Init();
    Animator Create(const std::string& name);
private:
    std::unique_ptr<CharacterParser> m_parser;
};

} //end of core
