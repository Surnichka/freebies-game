#include "Character.h"

namespace core
{

void Character::AddAnimation(const std::string& id, IAnimation::uPtr&& animation)
{
    if(id.empty())
    {
        throw std::runtime_error("Trying to create animation with empty id!");
    }
    m_animations[id] = std::move(animation);
}

void Character::Play(const std::string& id, std::chrono::milliseconds duration)
{
    m_activeAnim = m_animations.find(id);
    if( m_activeAnim != m_animations.end() )
    {
        m_activeAnim->second->Start(duration);
    }
}

void Character::Stop()
{
    if( m_activeAnim != m_animations.end() )
    {
        m_activeAnim->second->Stop();
    }
}

bool Character::Has(const std::string& id) const
{
    auto iter = m_animations.find(id);
    return (iter != m_animations.end());
}

bool Character::IsPlaying() const
{
    if( m_activeAnim != m_animations.end() )
    {
        return m_activeAnim->second->IsRunning();
    }
    return false;
}

std::string Character::GetActive() const
{
    if( m_activeAnim != m_animations.end() )
    {
        return m_activeAnim->first;
    }
    return "";
}

void Character::Update()
{
    Entity::Update();
    if( m_activeAnim != m_animations.end() )
    {
        m_activeAnim->second->Update(*this);
    }
}

} //end of core
