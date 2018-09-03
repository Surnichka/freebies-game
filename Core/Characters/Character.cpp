#include "Character.h"
#include "../Math/Math.h"

namespace core
{

void Character::AddAnimation(const Identifier &id, const SpriteList &frames)
{
    m_animations[id] = frames;
}


void Character::Play(const Identifier &id, std::chrono::milliseconds duration, ReplayPolicy replayPolicy)
{
    if(IsPlaying())
    {
        if((ReplayPolicy::OnNew == replayPolicy) && (id == GetActive()))
        {
            return;
        }
        if((ReplayPolicy::Never == replayPolicy) && IsPlaying())
        {
            return;
        }
    }

    auto iter = m_animations.find(id);
    if(iter == m_animations.end())
    {
        throw std::runtime_error("Playing animation with id: " + id + ", that doesn't exist!");
    }

    m_animInfo.activeAnim = iter;
    m_animInfo.playing = true;
    m_animInfo.lifetime.Setup(core::Timer::Config(duration));
    m_animInfo.lifetime.OnTick([this, iter](const core::Timer::Info& info)
    {
        m_animInfo.activeSpriteIndex = core::RangeMap(info.durationElapsed, 0ms, info.config.duration,
                                             size_t(0), m_animInfo.activeAnim->second.size() - 1);
    });
    m_animInfo.lifetime.OnTimerEnd([this]()
    {
        m_animInfo.playing = false;
    });
    m_animInfo.lifetime.Start();
}

void Character::Stop(const Identifier &id)
{

}

bool Character::IsPlaying() const
{
    return m_animInfo.playing;
}

Character::Identifier Character::GetActive() const
{
    return m_animInfo.activeAnim->first;
}

void Character::Update(std::chrono::milliseconds dt)
{
    m_animInfo.lifetime.Update(dt);
    auto& sprite = m_animInfo.activeAnim->second[m_animInfo.activeSpriteIndex];
    sprite.setPosition(m_transformable.getPosition());
    sprite.setOrigin(m_transformable.getScale());
    sprite.setScale(m_transformable.getScale());
    sprite.setRotation(m_transformable.getRotation());
}

void Character::Draw(sf::RenderWindow &window)
{
    window.draw(m_animInfo.activeAnim->second[m_animInfo.activeSpriteIndex]);
}

void Character::SetPosition(sf::Vector2f pos)
{
    m_transformable.setPosition(pos);
}

void Character::SetScale(sf::Vector2f scale)
{
    m_transformable.setScale(scale);
}

void Character::SetOrigin(sf::Vector2f origin)
{
    m_transformable.setOrigin(origin);
}

void Character::Move(sf::Vector2f offset)
{
    m_transformable.move(offset);
}

void Character::Rotate(float degree)
{
    m_transformable.rotate(degree);
}

}
