#include "Animator.h"
#include <algorithm>

namespace core
{

Animator::Animator(Animator&& other)
    : m_animations(std::move(other.m_animations))
    , m_activeAnim(m_animations.end())
{

}

Animator &Animator::operator=(Animator && other)
{
    m_animations = std::move(other.m_animations);
    m_activeAnim = m_animations.end();
    return *this;
}

void Animator::AddAnimation(const std::string& id, IAnimation::uPtr&& animation)
{
    if(id.empty())
    {
        throw std::runtime_error("Trying to create animation with empty id!");
    }
    m_animations[id] = std::move(animation);
}

void Animator::RunAnimation(IAnimation::uPtr&& animation, std::chrono::milliseconds duration)
{
    m_actions.emplace_back(std::move(animation));
    m_actions.back()->Start(duration);
}

void Animator::Play(const std::string& id, std::chrono::milliseconds duration)
{
    play(id, duration, false);
}

void Animator::Loop(const std::string &id, std::chrono::milliseconds duration)
{
    play(id, duration, true);
}

void Animator::Stop()
{
    if( m_activeAnim != m_animations.end() )
    {
        m_activeAnim->second->Stop();
        m_activeAnim = m_animations.end();
    }
}

bool Animator::Has(const std::string& id) const
{
    auto iter = m_animations.find(id);
    return (iter != m_animations.end());
}

bool Animator::IsPlaying(const std::string& id) const
{
    auto iter = (id.empty()) ? m_activeAnim : m_animations.find(id);
    if( iter != m_animations.end() )
    {
        return iter->second->IsRunning();
    }
    return false;
}

void Animator::Update(Entity& entity)
{
    if( m_activeAnim != m_animations.end() )
    {
        bool hasUpdated = m_activeAnim->second->Update(entity);
        if(false == hasUpdated)
        {
            m_activeAnim = m_animations.end();
        }
    }

    auto iter = std::remove_if(m_actions.begin(), m_actions.end(), [&entity](auto& action)
    {
        bool hasUpdated = (action->Update(entity));
        return (false == hasUpdated);
    });
    m_actions.erase(iter, m_actions.end());
}

void Animator::play(const std::string &id, std::chrono::milliseconds duration, bool loop)
{
    auto iter = m_animations.find(id);
    if( iter != m_animations.end() )
    {
        if(m_activeAnim != m_animations.end())
        {
            m_activeAnim->second->Stop();
        }
        m_activeAnim = iter;
        m_activeAnim->second->Start(duration, loop);
    }
    else
    {
        m_activeAnim = m_animations.end();
    }
}

} //end of core
