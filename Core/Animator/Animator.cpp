#include "Animator.h"

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
    m_animations["[external/animation]"] = std::move(animation);
    m_activeAnim->second->Start(duration);
}

void Animator::Play(const std::string& id, std::chrono::milliseconds duration)
{
    auto iter = m_animations.find(id);
    if( iter != m_animations.end() )
    {
        if(m_activeAnim != m_animations.end())
        {
            m_activeAnim->second->Stop();
        }
        m_activeAnim = iter;
        m_activeAnim->second->Start(duration);
    }
    else
    {
        m_activeAnim = m_animations.end();
    }
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
}

} //end of core
