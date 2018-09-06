#pragma once
#include <chrono>
#include <functional>
using namespace std::chrono_literals;

namespace core
{

class Timer
{
public:
    struct Config
    {
        std::chrono::milliseconds duration = 0ms;
        std::chrono::milliseconds tickPeriod = 0ms;
        std::chrono::milliseconds delayBeforeStart = 0ms;

        Config(std::chrono::milliseconds duration_ = 0ms,
               std::chrono::milliseconds tickPeriod_ = 0ms,
               std::chrono::milliseconds delayBeforeStart_ = 0ms)
            : duration(duration_)
            , tickPeriod(tickPeriod_)
            , delayBeforeStart(delayBeforeStart_) {}
    };

    struct Info
    {
        Config config;
        std::chrono::milliseconds delayElapsed = 0ms;
        std::chrono::milliseconds tickElapsed = 0ms;
        std::chrono::milliseconds durationElapsed = 0ms;
    };

    using OnTickCB = std::function<void()>;
    using OnTickInfoCB = std::function<void(const Info&)>;
    using OnTimerEndCB = std::function<void()>;

    void Setup(const Timer::Config& config);
    void Update();

    void OnTick(const OnTickCB& onTick);
    void OnTick(const OnTickInfoCB& onTickInfo);
    void OnTimerEnd(const OnTimerEndCB& onTimerEnd);

    void Restart();
    void Start();
    void Stop();

    bool IsRunning() const;
    bool IsExpired() const;
    const Info& GetInfo() const;
private:
    bool isInfinity() const;
    void clear();

private:
    bool m_running = false;
    bool m_expired = false;
    Info m_info;

    OnTickCB m_onTick;
    OnTickInfoCB m_onTickInfo;
    OnTimerEndCB m_onTimerEnd;
};

} //end of core
