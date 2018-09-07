#pragma once
#include <chrono>
#include "../Timer/Timer.h"
#include <SFML/Graphics/Sprite.hpp>

namespace core
{

class ISpriteAnimation
{
public:
    ISpriteAnimation() = default;
    virtual ~ISpriteAnimation() = default;

    ISpriteAnimation(ISpriteAnimation&&) = default;
    ISpriteAnimation& operator=(ISpriteAnimation&&) = default;

    ISpriteAnimation(const ISpriteAnimation&) = default;
    ISpriteAnimation& operator=(const ISpriteAnimation&) = default;

    using OnEndCallback = std::function<void()>;
    inline void SetOnAnimationEnd(const OnEndCallback& onEndCB)
    {
        m_onAnimationEnd = onEndCB;
    }
    virtual void Update(sf::Sprite& sprite) = 0;
    virtual void Start(std::chrono::milliseconds duration) = 0;
    virtual void Stop() = 0;
protected:
    Timer m_timer;
    OnEndCallback m_onAnimationEnd;
};

} //end of core
