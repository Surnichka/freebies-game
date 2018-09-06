#pragma once
#include "ISpriteAnimation.h"
#include <vector>
#include <SFML/Graphics/Sprite.hpp>

namespace core
{

class FrameAnimation : public ISpriteAnimation
{
public:
    explicit FrameAnimation(std::vector<sf::Sprite> frames);
    void Update(sf::Sprite& sprite) final override;
    void Start(std::chrono::milliseconds duration) final override;
    void Stop() final override;
private:
    std::vector<sf::Sprite> m_frames;
    size_t m_activeFrameIdx = 0;
};

} //end of core
