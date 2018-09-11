#pragma once
#include <chrono>
#include <memory>
#include "../Timer/Timer.h"

namespace core
{
class Entity;
class IAnimation
{
public:
    using uPtr = std::unique_ptr<IAnimation>;

    virtual ~IAnimation() = default;
    virtual void Start(std::chrono::milliseconds duration) = 0;
    virtual void Stop() = 0;
    virtual void Update(Entity& entity) = 0;

    inline bool IsRunning() const { return m_timer.IsRunning(); }
protected:
    Timer m_timer;
};

} //end of core
