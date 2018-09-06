#include "Timer.h"
#include "../Application/Application.h"

namespace core
{

void Timer::Setup(const Timer::Config &config)
{
    m_info.config = config;
    clear();
}

void Timer::Update()
{
    auto dt = Application::Get().frameTime;
    if( false == IsRunning() )
    {
        if(m_expired)
        {
            m_expired = false;
        }
        return;
    }

    m_info.delayElapsed += dt;
    if( m_info.delayElapsed < m_info.config.delayBeforeStart )
    {
        return;
    }

    m_info.tickElapsed += dt;
    m_info.durationElapsed += dt;

    if( m_info.tickElapsed >= m_info.config.tickPeriod )
    {
        if( nullptr != m_onTick )
        {
            m_onTick();
        }

        if( nullptr != m_onTickInfo )
        {
            m_onTickInfo(m_info);
        }

        m_info.tickElapsed -= m_info.config.tickPeriod;
    }

    if( false == isInfinity() )
    {
        if( m_info.durationElapsed >= m_info.config.duration )
        {
            m_running = false;
            m_expired = true;
            if(nullptr != m_onTimerEnd)
            {
                m_onTimerEnd();
            }
        }
    }
}

void Timer::OnTick(const Timer::OnTickCB &onTick)
{
    m_onTick = onTick;
    m_onTickInfo = nullptr;
}

void Timer::OnTick(const Timer::OnTickInfoCB &onTickInfo)
{
    m_onTickInfo = onTickInfo;
    m_onTick = nullptr;
}

void Timer::OnTimerEnd(const Timer::OnTimerEndCB &onTimerEnd)
{
    m_onTimerEnd = onTimerEnd;
}

void Timer::Restart()
{
    m_running = true;
    clear();
}

void Timer::Start()
{
    if(false == IsRunning())
    {
        m_running = true;
        clear();
    }
}

void Timer::Stop()
{
    m_running = false;
    clear();
}

bool Timer::IsRunning() const
{
    return m_running;
}

bool Timer::isInfinity() const
{
    return m_info.config.duration == 0ms;
}

void Timer::clear()
{
    m_info.delayElapsed = 0ms;
    m_info.durationElapsed = 0ms;
    m_info.tickElapsed = 0ms;
}

bool Timer::IsExpired() const
{
    return m_expired;
}

const Timer::Info &Timer::GetInfo() const
{
    return m_info;
}

} //end of core
