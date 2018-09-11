#pragma once
#include "../Entity/Entity.h"
#include "IAnimation.h"
#include <map>

namespace core
{

class Character : public Entity
{
public:
    void AddAnimation(const std::string& id, IAnimation::uPtr&& animation);
    void Play(const std::string& id, std::chrono::milliseconds duration);
    void Stop();
    bool Has(const std::string& id) const;

    bool IsPlaying() const;
    std::string GetActive() const;

    void Update();
private:
    using AnimMap = std::map<std::string, IAnimation::uPtr>;
    AnimMap m_animations;
    AnimMap::iterator m_activeAnim = m_animations.end();
};

} //end of core
