#pragma once
#include "../Animations/IAnimation.h"
#include <chrono>
#include <map>
#include <vector>

namespace core
{

class Entity;
class Animator
{
public:
    Animator() = default;
    ~Animator() = default;
    Animator(const Animator&) = delete;
    Animator& operator=(const Animator&) = delete;
    Animator(Animator&& other);
    Animator& operator=(Animator&& other);

    /// \brief Pair animation with id, into Animation object, so it can later be called
    /// with Play(id, duration) function.
    void AddAnimation(const std::string& id, IAnimation::uPtr&& animation);

    /// \brief Run external animation once.
    void RunAnimation(IAnimation::uPtr&& animation, std::chrono::milliseconds duration);

    /// \brief Play animation on given 'id' for specified duration time
    /// otherwise if 'id' doesn't exist function won't start animation
    void Play(const std::string& id, std::chrono::milliseconds duration);

    /// \brief Same as Play, expect will loop the animation
    void Loop(const std::string& id, std::chrono::milliseconds duration);

    void Stop();
    bool Has(const std::string& id) const;

    /// \brief if not argument is given will get result for current animation
    bool IsPlaying(const std::string& id = "") const;

    void Update(Entity& entity);
private:
    void play(const std::string& id, std::chrono::milliseconds duration, bool loop);

    using AnimationMap = std::map<std::string, IAnimation::uPtr>;
    AnimationMap m_animations;
    std::vector<IAnimation::uPtr> m_actions;
    AnimationMap::iterator m_activeAnim = m_animations.end();
};

} //end of core
