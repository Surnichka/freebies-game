#pragma once
#include "../Entity/Entity.h"
#include "../Animator/Animator.h"
#include "../InputController/InputController.h"
#include "../FSM/StateMachine.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include <set>
#include <map>
#include <functional>

namespace core
{

class Character : public Entity
{
public:
    void Init(Animator&& animator);
    void Update() override;
    void Draw(sf::RenderWindow& window) const override;
private:
    void moveCharacter();
    Animator m_animator;
    fsm::StateMachine m_stateMachine;
};

} //end of core
