#include "Character.h"
#include "SFML/Window/Event.hpp"
#include "../Application/Application.h"
#include "../World/PhysicWorld.h"
#include "../Animations/FadeAnimation.h"
#include <map>
#include <experimental/optional>

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
        m_animator.RunAnimation(FadeBy::Create(10), 1000ms);
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
        moveCharacter();
    },
    {"idle", "jump", "attack"}); //TransitionList
    runState->isDynamic = true;
////////////////////////////////////////////////////////////////////////////

    m_stateMachine.AddState("jump",
    [](fsm::StateMachine&) //ConditionToEnter
    {
        //auto collisionList = Application::Get().physicWorld->GetCollisionList(*this);
        //find in collisionList if character is touching solid ground
        return sf::Keyboard::isKeyPressed(sf::Keyboard::W);
    },
    [this](fsm::StateMachine& sm) //OnEnter
    {
        m_animator.Play("jump", 500ms);
        sm.RequestState("idle", 500ms); //temporary
    },
    [](fsm::StateMachine&)
    {
        //auto collisionList = Application::Get().physicWorld->GetCollisionList(*this);
        //find in collisionList if character is touching solid ground if yes, request state
        //sm.RequestState("idle");
    }, //OnUpdate
    {"idle", "attack"}); //TransitionList
    ////////////////////////////////////////////////////////////////////////////
}

void Character::Update()
{
    m_stateMachine.Update();
    Entity::Update();
    m_animator.Update(*this);
}

void Character::Draw(sf::RenderWindow &window) const
{
    Entity::Draw(window);
}

void Character::moveCharacter()
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
