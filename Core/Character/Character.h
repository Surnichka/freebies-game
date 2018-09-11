#pragma once
#include "../Entity/Entity.h"
#include "../Animator/Animator.h"
#include "../InputController/InputController.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include <set>
#include <map>
#include <functional>

namespace core
{

namespace fsm
{

struct State
{
    std::string name;
    std::function<void()> onEnterFn;
    std::function<void()> onUpdateFn;
    std::function<bool()> conditionsFn;

    /// \brief Will force to stay on this state for given duration of time.
    std::chrono::milliseconds blockStateFor = std::chrono::milliseconds::zero();

    /// \brief On true: user must request for this state every game update,
    /// otherwise will onEndFn be called.
    /// On false: state will stay until external event happen.
    bool isDynamic = false;

    /// \brief refer to all states you can go from this one
    std::vector<State*> transitionList;
};

//class StateMachine
//{
//public:
//    void Add(State state)
//    {

//    }
//private:
//    std::vector<State> m_states;
//};

} //end of fsm


class Character : public Entity
{
public:
    void Init();
    void Update();

//private:
    Animator m_animator;
    fsm::State attacking;
    fsm::State running;
    fsm::State standing;


    fsm::State* currentState = nullptr;
//    State m_currentState = State::Standing;
};

} //end of core
