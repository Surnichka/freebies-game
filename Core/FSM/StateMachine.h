#pragma once
#include "State.h"
#include "../Timer/Timer.h"
#include <map>

namespace core
{

namespace fsm
{

class StateMachine
{
public:
    using StateMap = std::map<std::string, State::uPtr>;

    /// \brief Refer to (starting/default/neutral) state to which every other state have access.
    std::string defaultState;

    const State::uPtr& AddState(const std::string& _name,
                                const std::function<bool(StateMachine&)>& _conditionToEnterFn,
                                const std::function<void(StateMachine&)>& _onEnterFn,
                                const std::function<void(StateMachine&)>& _onUpdateFn,
                                const std::vector<std::string>& _transitionStateNames = {});
    void Update();

    /// \brief Request state now or with some time delay
    void RequestState(const std::string& name, std::chrono::milliseconds delay = {});
private:
    void changeState(StateMap::iterator iter);
    bool isConditionMet(StateMap::iterator iter);
    void updateState(StateMap::iterator iter);
    void onEnterState(StateMap::iterator iter);

    StateMap m_states;
    StateMap::iterator m_activeState = m_states.end();
    Timer m_timer;
};

} //end of fsm
} //end of core
