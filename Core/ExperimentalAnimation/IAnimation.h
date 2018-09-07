#pragma once
#include <chrono>
#include "../Timer/Timer.h"
#include <SFML/Graphics/Sprite.hpp>
#include "../Math/Easing.h"

namespace core
{

class IAnimation
{
public:
    IAnimation() = default;
    virtual ~IAnimation() = default;

    IAnimation(IAnimation&&) = default;
    IAnimation& operator=(IAnimation&&) = default;

    IAnimation(const IAnimation&) = default;
    IAnimation& operator=(const IAnimation&) = default;

    using OnEndCallback = std::function<void()>;
    inline void SetOnAnimationEnd(const OnEndCallback& onEndCB)
    {
        m_onAnimationEnd = onEndCB;
    }
    virtual void Update(sf::Sprite& sprite) = 0;
    virtual void Start(std::chrono::milliseconds duration,
                       const math::ease::Function& ease = math::ease::linear) = 0;
    virtual void Stop() = 0;
protected:
    Timer m_timer;
    math::ease::Function m_easeFunction = math::ease::linear;
    OnEndCallback m_onAnimationEnd;
};

} //end of core
