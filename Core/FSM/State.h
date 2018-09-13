#pragma once
#include <string>
#include <functional>
#include <chrono>
#include <memory>
#include <vector>

namespace core
{
namespace fsm
{

class StateMachine;
struct State
{
    using uPtr = std::unique_ptr<State>;

    std::string name;
    std::function<bool(StateMachine&)> conditionToEnterFn;
    std::function<void(StateMachine&)> onEnterFn;
    std::function<void(StateMachine&)> onUpdateFn;

    /// \brief Will force to stay on this state for given duration of time.
    std::chrono::milliseconds blockStateFor = std::chrono::milliseconds::zero();

    /// \brief On true: user must request for this state every game update,
    /// otherwise will switch to default state.
    /// On false: state will stay until state changing event happen.
    bool isDynamic = false;

    /// \brief refer to all states you can go from this one
    std::vector<std::string> transitionList;
};

} //end of fsm
} //end of core
