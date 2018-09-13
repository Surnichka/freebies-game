#include "FadeAnimation.h"
#include "../Entity/Entity.h"
#include "../Math/RangeMap.h"

namespace core
{


FadeBy::uPtr FadeBy::Create(int32_t fadeBy)
{
    auto fadeByAnimation = std::make_unique<FadeBy>();
    fadeByAnimation->m_fadeBy = fadeBy;
    return fadeByAnimation;
}

void FadeBy::Start(std::chrono::milliseconds duration, bool)
{
    m_timer.Setup(Timer::Config(duration));
    m_timer.Start();
}

void FadeBy::Stop()
{
    m_timer.Stop();
}

bool FadeBy::Update(Entity& entity)
{
    m_timer.Update();
    if(m_timer.IsRunning())
    {
        const auto& info = m_timer.GetInfo();

        auto curFade = math::RangeMap(info.durationElapsed,
                                        0ms, info.config.duration,
                                        0, m_fadeBy);
        auto c = entity.GetSprite().getColor();
        c.a += curFade;
        entity.GetSprite().setColor(c);

        return true;
    }
    return false;
}


} //end of core
