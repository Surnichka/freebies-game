#include "StateMachine.h"

namespace core
{

namespace fsm
{

const State::uPtr& StateMachine::AddState(const std::string &_name,
                                  const std::function<bool(StateMachine&)>& _conditionToEnterFn,
                                  const std::function<void(StateMachine&)>& _onEnterFn,
                                  const std::function<void(StateMachine&)>& _onUpdateFn,
                                  const std::vector<std::string> &_transitionStateNames)
{
    auto state = std::make_unique<State>();
    state->name = _name;
    state->conditionToEnterFn = _conditionToEnterFn;
    state->onEnterFn = _onEnterFn;
    state->onUpdateFn = _onUpdateFn;
    state->transitionList = _transitionStateNames;

    for(auto& stateName : state->transitionList)
    {
        if(_name == stateName)
        {
            throw std::runtime_error("You can not add your state name into transitonList!");
        }
    }

    m_states[_name] = std::move(state);
    return m_states.at(_name);
}

void StateMachine::Update()
{
    if( m_activeState == m_states.end() )
    {
        RequestState(defaultState);
        return;
    }

    m_timer.Update();
    if( m_activeState->second->isDynamic )
    {
        if( isConditionMet(m_activeState) )
        {
            updateState(m_activeState);
        }
        else
        {
            RequestState(defaultState);
        }
    }
    else
    {
        updateState(m_activeState);
    }

    for(auto& stateName : m_activeState->second->transitionList)
    {
        auto iter = m_states.find(stateName);
        if( iter == m_states.end() )
        {
            throw std::runtime_error("Traversing transitionList with states,"
                                     " that doesn't exist in StateMachine!");
        }
        if( isConditionMet(iter) )
        {
            changeState(iter);
        }
    }
}

void StateMachine::RequestState(const std::string &name, std::chrono::milliseconds delay)
{
    if(m_activeState != m_states.end() &&
       m_activeState->first == name)
    {
        return;
    }

    auto iter = m_states.find(name);
    if( iter != m_states.end() )
    {
        if(delay == std::chrono::milliseconds::zero())
        {
            changeState(iter);
        }
        else
        {
            m_timer.Setup(Timer::Config(delay));
            m_timer.Start();
            m_timer.OnTimerEnd([iter, this]()
            {
                changeState(iter);
            });
        }
    }
    else
    {
        m_activeState = m_states.find(defaultState);
        if( m_activeState == m_states.end() )
        {
            throw std::runtime_error("Request state and default state is not found!");
        }
        onEnterState(m_activeState);
    }
}

void StateMachine::changeState(StateMap::iterator iter)
{
    m_activeState = iter;
    onEnterState(m_activeState);
}

bool StateMachine::isConditionMet(StateMap::iterator iter)
{
    if( nullptr != iter->second->conditionToEnterFn )
    {
        return iter->second->conditionToEnterFn((*this));
    }
    return false;
}

void StateMachine::updateState(StateMap::iterator iter)
{
    if( nullptr != iter->second->onUpdateFn )
    {
        iter->second->onUpdateFn((*this));
    }
}

void StateMachine::onEnterState(StateMap::iterator iter)
{
    if( nullptr != iter->second->onEnterFn )
    {
        iter->second->onEnterFn((*this));
    }
}

} //end of fsm
} //end of core
