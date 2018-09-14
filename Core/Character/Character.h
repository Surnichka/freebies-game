#pragma once
#include "../Entity/Entity.h"
#include "../Animator/Animator.h"
#include "../FSM/StateMachine.h"
#include "../CharacterController/CharacterController.h"
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
    void SetController(const CharacterController& controller);
    void Update() override;
    void Draw(sf::RenderWindow& window) const override;
private:
    void move(float speed);
    void jump();

    Animator m_animator;
    fsm::StateMachine m_stateMachine;
    CharacterController m_controller;
    Timer m_jumpTimer;
};

} //end of core
