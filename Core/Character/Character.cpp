#include "Character.h"
#include "SFML/Window/Event.hpp"
#include <map>
#include <experimental/optional>

namespace core
{

void Character::Init()
{
    attacking.name = "attack";
    attacking.onEnterFn = [this] ()
    {
        m_animator.Play("attack", 500ms);
    };
    attacking.onUpdateFn = [this] ()
    {
        if( false == m_animator.IsPlaying("attack"))
        {
            currentState = &standing;
            currentState->onEnterFn();
        }
    };
    attacking.conditionsFn = []()
    {
        return sf::Keyboard::isKeyPressed(sf::Keyboard::K);
    };
    attacking.transitionList = {&running};
//////////////////////////////////////////////////////////////////

    running.name = "run";
    running.onEnterFn = [this] ()
    {
        m_animator.Play("run", 500ms);
    };

    running.isDynamic = true;
    running.onUpdateFn = [this] ()
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            Entity::SetFlip(true);
            Entity::ApplyForce({-10.0f, 0.0f});
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            Entity::SetFlip(false);
            Entity::ApplyForce({10.0f, 0.0f});
        }

        if( false == m_animator.IsPlaying("run"))
        {
            m_animator.Play("run", 500ms);
        }
    };
    running.conditionsFn = []()
    {
        return sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
               sf::Keyboard::isKeyPressed(sf::Keyboard::D);
    };

//////////////////////////////////////////////////////////////////
    standing.name = "idle";
    standing.onEnterFn = [this] () { m_animator.Play("idle", 500ms); };
    standing.onUpdateFn = [this] ()
    {
        if( false == m_animator.IsPlaying("idle"))
        {
            m_animator.Play("idle", 500ms);
        }
    };
    standing.conditionsFn = []() { return true; };

    standing.transitionList = {&running, &attacking};
//////////////////////////////////////////////////////////////////
    currentState = &standing;
    currentState->onEnterFn();
}

void Character::Update()
{
    if(currentState->isDynamic)
    {
        if( currentState->conditionsFn() )
        {
            currentState->onUpdateFn();
        }
        else
        {
            currentState = &standing;
            currentState->onEnterFn();
        }
    }
    else
    {
        currentState->onUpdateFn();
    }

    for(auto& state : currentState->transitionList)
    {
        bool conditionsMet = state->conditionsFn();
        if( conditionsMet )
        {
            currentState = state;
            currentState->onEnterFn();
            break;
        }
    }

//    State::Attacking att;
//    att.canInterupt = false;
//    att.isDynamic = false;
//    att.onEnd = switchToIdle / loop



//    /// \brief states that need to be actively requested to be played
//    State requestActiveState;
//    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) requestActiveState = State::Running;
//    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) requestActiveState = State::Running;

//    /// \brief states that need to just to be switched to get activated
//    State requestPassiveState;
//    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) requestPassiveState = State::Jumping;
//    if(sf::Keyboard::isKeyPressed(sf::Keyboard::K)) requestPassiveState = State::Attacking;

//    if( requestActiveState != m_currentState )
//    {
//        if(requestPassiveState == State::Jumping)   m_animator.Play("jump", 500ms);
//        if(requestPassiveState == State::Attacking) m_animator.Play("attack", 500ms);
//    }

//    if(requestState != std::experimental::nullopt &&
//       m_currentState != requestState.value())
//    {
//        m_currentState = requestState.value();
//        switch( m_currentState )
//        {
//            case State::Standing:
//            {

//            }break;
//            case State::Running:
//            {
//                m_animator.Play("run", 500ms);
//            }break;

//            case State::Jumping:
//            {
//                m_animator.Play("jump", 500ms);
//            }break;

//            case State::Attacking:
//            {
//                m_animator.Play("attack", 500ms);
//            }break;
//        };
//    }

//    switch( m_currentState )
//    {
//        case State::Jumping:
//        {
//            if( false == m_animator.IsPlaying("jump"))
//            {
//                m_currentState = State::Standing;
//                m_animator.Play("idle", 500ms);
//            }
//        }break;

//        case State::Attacking:
//        {
//            if( false == m_animator.IsPlaying("attack"))
//            {
//                m_currentState = State::Standing;
//                m_animator.Play("idle", 500ms);
//            }
//        }break;

//        case State::Standing:
//        {
//            if( false == m_animator.IsPlaying("idle") )
//            {
//                m_animator.Play("idle", 500ms);
//            }
//        }break;

//        case State::Running:
//        {
//            if( false == m_animator.IsPlaying("run") )
//            {
//                m_animator.Play("run", 500ms);
//            }
//        }break;
//    }

    Entity::Update();
    m_animator.Update(*this);
}

} //end of core
