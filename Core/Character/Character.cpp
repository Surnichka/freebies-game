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
//        m_animator.RunAnimation(FadeBy::Create(10), 1000ms);
        m_animator.Loop("idle", 500ms);
    },
    nullptr, //OnUpdate
    {"run", "attack", "jump"}); //TransitionList
////////////////////////////////////////////////////////////////////////////

    m_stateMachine.AddState("attack",
    [](fsm::StateMachine&) //ConditionToEnter
    {
        return sf::Keyboard::isKeyPressed(sf::Keyboard::K);
    },
    [this](fsm::StateMachine& sm) //OnEnter
    {
        m_animator.Play("attack", 300ms);
        sm.RequestState("idle", 300ms);
    },
    nullptr, //OnUpdate
    {"idle"}); //TransitionList

////////////////////////////////////////////////////////////////////////////

    const auto& runState = m_stateMachine.AddState("run",
    [](fsm::StateMachine&) //ConditionToEnter
    {
        return sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
               sf::Keyboard::isKeyPressed(sf::Keyboard::D);
    },
    [this](fsm::StateMachine&) //OnEnter
    {
        m_animator.Loop("run", 500ms);
    },
    [this](fsm::StateMachine&)
    {
        move();
    },
    {"idle", "jump", "attack"}); //TransitionList
    runState->isDynamic = true;
////////////////////////////////////////////////////////////////////////////

    m_stateMachine.AddState("jump",
    [this](fsm::StateMachine&) //ConditionToEnter
    {
        auto isOnGround = Application::Get().collisionInfo->IsFootSensorActive((*this));
        auto isJumpKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::W);

        return isOnGround && isJumpKeyPressed;
    },
    [this](fsm::StateMachine& sm) //OnEnter
    {
        jump();
        m_animator.Play("jump", 500ms);
    },
    [this](fsm::StateMachine& sm) //OnUpdate
    {
        move();
        auto isHeadHitted = Application::Get().collisionInfo->IsHeatSensorActive((*this));
        if( isHeadHitted )
        {
            m_jumpTimer.Stop();
        }

        auto isOnGround = Application::Get().collisionInfo->IsFootSensorActive((*this));
        if( isOnGround )
        {
            sm.RequestState("idle");
        }
    },
    {"idle", "attack"}); //TransitionList
    ////////////////////////////////////////////////////////////////////////////
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
    sf::Vector2f jumpVelocity = {0.0f, -30.0f};
    std::chrono::milliseconds duration = 200ms;

    m_jumpTimer.Setup(Timer::Config(duration));
    m_jumpTimer.OnTick([this, jumpVelocity = std::move(jumpVelocity)]() mutable
    {
        Entity::ApplyForce(jumpVelocity);
        jumpVelocity.y = std::min(jumpVelocity.y + 0.5f, -20.0f);
    });
    m_jumpTimer.Start();
}

void Character::move()
{
    float speed = 10.0f;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        Entity::SetFlip(true);
        Entity::ApplyForce({-speed, 0.0f});
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        Entity::SetFlip(false);
        Entity::ApplyForce({speed, 0.0f});
    }
}

} //end of core
