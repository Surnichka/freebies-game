#include "FrameAnimation.h"
#include "../Math/Math.h"

namespace core
{

FrameAnimation::FrameAnimation(std::vector<sf::Sprite> frames)
    : m_frames(frames)
{}

void FrameAnimation::Update(sf::Sprite& sprite)
{
    m_timer.Update();
    if( m_timer.IsRunning() )
    {
        const auto& info = m_timer.GetInfo();
        auto frameCount = m_frames.size();
        auto curFrameIndex = math::RangeMap(info.durationElapsed,
                                            0ms, info.config.duration,
                                            0ul, frameCount);
        sprite = m_frames.at(curFrameIndex);
    }
}

void FrameAnimation::Start(std::chrono::milliseconds duration)
{
    m_timer.Setup(Timer::Config(duration));
    m_timer.Start();
 }

void FrameAnimation::Stop()
{
    m_timer.Stop();
}

} //end of core
