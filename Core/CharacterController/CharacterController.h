#pragma once
#include <functional>

namespace core
{
class Character;
class CharacterController
{
public:
    std::function<bool(Character&)> requestMoveLeft;
    std::function<bool(Character&)> requestMoveRight;
    std::function<bool(Character&)> requestJump;
    std::function<bool(Character&)> requestAttack;
};

namespace controllers
{
    CharacterController Player_One();
    CharacterController Player_Two();
    CharacterController AI_AgressiveToPlayer();
} //end of controllers

} //end of core
