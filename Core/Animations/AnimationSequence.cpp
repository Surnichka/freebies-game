#include "AnimationSequence.h"
#include "../Entity/Entity.h"
#include "../Math/RangeMap.h"

namespace core
{

AnimationSequence::AnimationSequence(const std::string &holder, const std::vector<std::string> &textureIds)
    : m_resouceHolderId(holder)
    , m_textureIds(textureIds)
{
    if(m_resouceHolderId.empty() || m_textureIds.empty())
    {
        throw std::runtime_error("Trying to create AnimationSequence without specifying animation ids!");
    }
}

void AnimationSequence::Start(std::chrono::milliseconds duration, bool loop)
{
    m_timer.Setup(Timer::Config(duration));
    m_timer.Start();
    m_loop = loop;
}

void AnimationSequence::Stop()
{
    m_timer.Stop();
}

bool AnimationSequence::Update(Entity& entity)
{
    bool active = true;

    m_timer.Update();
    if( m_timer.IsRunning())
    {
        const auto& info = m_timer.GetInfo();
        auto animFramesCount = m_textureIds.size() - 1;
        size_t curAnimIdx = math::RangeMap(info.durationElapsed,
                                           0ms, info.config.duration,
                                           0ul, animFramesCount);

        auto textureId = m_textureIds[curAnimIdx];
        entity.SetTexture(m_resouceHolderId, textureId);
    }
    else
    {
        active = m_loop;
        if(m_loop)
        {
            m_timer.Restart();
        }
    }

    return active;
}

} //end of core
