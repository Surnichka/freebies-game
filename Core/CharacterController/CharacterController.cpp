#include "CharacterController.h"
#include <SFML/Window/Event.hpp>
#include "../Enemy/AI_AgressiveToPlayer.h"

namespace core
{

namespace controllers
{

CharacterController Player_One()
{
    CharacterController cc;
    cc.requestMoveLeft =    [](Character&){ return sf::Keyboard::isKeyPressed(sf::Keyboard::A); };
    cc.requestMoveRight =   [](Character&){ return sf::Keyboard::isKeyPressed(sf::Keyboard::D); };
    cc.requestJump =        [](Character&){ return sf::Keyboard::isKeyPressed(sf::Keyboard::W); };
    cc.requestAttack =      [](Character&){ return sf::Keyboard::isKeyPressed(sf::Keyboard::Space); };
    return cc;
}

CharacterController Player_Two()
{
    CharacterController cc;
    cc.requestMoveLeft =    [](Character&){ return sf::Keyboard::isKeyPressed(sf::Keyboard::Left); };
    cc.requestMoveRight =   [](Character&){ return sf::Keyboard::isKeyPressed(sf::Keyboard::Right); };
    cc.requestJump =        [](Character&){ return sf::Keyboard::isKeyPressed(sf::Keyboard::Up); };
    cc.requestAttack =      [](Character&){ return sf::Keyboard::isKeyPressed(sf::Keyboard::Down); };
    return cc;
}

CharacterController AI_AgressiveToPlayer()
{
    CharacterController cc;
    cc.requestMoveLeft =    [](Character&){ return sf::Keyboard::isKeyPressed(sf::Keyboard::Left); };
    cc.requestMoveRight =   [](Character&){ return sf::Keyboard::isKeyPressed(sf::Keyboard::Right); };
    cc.requestJump =        [](Character&){ return sf::Keyboard::isKeyPressed(sf::Keyboard::Up); };
    cc.requestAttack =      [](Character&){ return sf::Keyboard::isKeyPressed(sf::Keyboard::Down); };
    return cc;
}

} //end of controllers
} //end of core
