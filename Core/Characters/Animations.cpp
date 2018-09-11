#include "Animations.h"
#include "../Entity/Entity.h"
#include "../Math/RangeMap.h"

namespace core
{

FrameAnimation::FrameAnimation(const std::string &holder, const std::vector<std::string> &textureIds)
    : m_resouceHolderId(holder)
    , m_textureIds(textureIds)
{
    if(m_resouceHolderId.empty() || m_textureIds.empty())
    {
        throw std::runtime_error("Trying to create FrameAnimation without specifying animation ids!");
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

void FrameAnimation::Update(Entity& entity)
{
    m_timer.Update();
    if( m_timer.IsRunning() )
    {
        const auto& info = m_timer.GetInfo();
        auto animFramesCount = m_textureIds.size() - 1;
        size_t curAnimIdx = math::RangeMap(info.durationElapsed,
                                           0ms, info.config.duration,
                                           0ul, animFramesCount);

        auto textureId = m_textureIds[curAnimIdx];
        entity.SetTexture(m_resouceHolderId, textureId);
    }
}

} //end of core
