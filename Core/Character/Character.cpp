#include "Character.h"
#include "SFML/Window/Event.hpp"
#include "../Application/Application.h"
#include "../Animations/FadeAnimation.h"
#include "../CollisionInfo/CollisionInfo.h"

#include <map>

namespace core
{

void Character::Init(Animator &&animator)
{
    m_animator = std::move(animator);

////////////////////////////////////////////////////////////////////////////
    m_stateMachine.defaultState = "idle";
    m_stateMachine.AddState("idle",
    nullptr, //ConditionToEnter
    [this](fsm::StateMachine&) //OnEnter
    {
        m_animator.Loop("idle", 500ms);
    },
    nullptr, //OnUpdate
    {"run", "attack", "jump"}); //TransitionList
////////////////////////////////////////////////////////////////////////////

    m_stateMachine.AddState("attack",
    [this](fsm::StateMachine&) //ConditionToEnter
    {
        return m_controller.requestAttack((*this));
    },
    [this](fsm::StateMachine& sm) //OnEnter
    {
        m_animator.Play("attack", 300ms);
        sm.RequestState("idle", 300ms);
    },
    [this](fsm::StateMachine&) //OnUpdate
    {
        if(m_jumpTimer.IsRunning()) //Can move while attacking only while jumping
        {
            move(12.0f);
        }
    },
    {"idle"}); //TransitionList

////////////////////////////////////////////////////////////////////////////

    const auto& runState = m_stateMachine.AddState("run",
    [this](fsm::StateMachine&) //ConditionToEnter
    {
        return m_controller.requestMoveLeft((*this)) || m_controller.requestMoveRight((*this));
    },
    [this](fsm::StateMachine&) //OnEnter
    {
        m_animator.Loop("run", 500ms);
    },
    [this](fsm::StateMachine&)
    {
        move(10.0f);
    },
    {"idle", "jump", "attack"}); //TransitionList
    runState->isDynamic = true;
////////////////////////////////////////////////////////////////////////////

    m_stateMachine.AddState("jump",
    [this](fsm::StateMachine&) //ConditionToEnter
    {
        auto isOnGround = Application::Get().collisionInfo->IsSensorActive("foot", (*this));
        auto isJumpKeyPressed = m_controller.requestJump((*this));

        return isOnGround && isJumpKeyPressed;
    },
    [this](fsm::StateMachine&) //OnEnter
    {
        jump();
        m_animator.Play("jump", 500ms);
    },
    [this](fsm::StateMachine& sm) //OnUpdate
    {
        move(12.0f);

        auto isHeadHitted = Application::Get().collisionInfo->IsSensorActive("head", (*this));
        auto isOnGround = Application::Get().collisionInfo->IsSensorActive("foot", (*this));

        if( isOnGround || isHeadHitted)
        {
            m_jumpTimer.Stop();
            sm.RequestState("idle");
        }
    },
    {"idle", "attack"}); //TransitionList
    ////////////////////////////////////////////////////////////////////////////
}

void Character::SetController(const CharacterController &controller)
{
    m_controller = controller;
}

void Character::Update()
{
    m_jumpTimer.Update();

    m_stateMachine.Update();
    Entity::Update();
    m_animator.Update(*this);
}

void Character::Draw(sf::RenderWindow &window) const
{
    Entity::Draw(window);
}

void Character::jump()
{
    sf::Vector2f jumpVelocity = {0.0f, -33.0f};
    std::chrono::milliseconds duration = 200ms;

    m_jumpTimer.Setup(Timer::Config(duration));
    m_jumpTimer.OnTick([this, jumpVelocity = std::move(jumpVelocity)]() mutable
    {
        Entity::ApplyForce(jumpVelocity);
        jumpVelocity.y = std::min(jumpVelocity.y + 1.0f, -15.0f);
    });
    m_jumpTimer.Start();
}

void Character::move(float speed)
{
    if(m_controller.requestMoveLeft((*this)))
    {
        Entity::SetFlip(true);
        Entity::ApplyForce({-speed, 0.0f});
    }
    else if(m_controller.requestMoveRight((*this)))
    {
        Entity::SetFlip(false);
        Entity::ApplyForce({speed, 0.0f});
    }
}

} //end of core
