#include "Character.h"
#include "../Math/Math.h"
#include <iostream>

namespace core
{

Character::Character(Character &&other)
    : m_animations(std::move(other.m_animations))
{
    clear();
}

Character::Character()
{
    clear();
}

Character::Character(const Character& other)
    : m_animations(other.m_animations)
{
    clear();
}

Character &Character::operator=(const Character& other)
{
    clear();
    m_animations = other.m_animations;
    return *this;
}

Character &Character::operator=(Character &&other)
{
    clear();
    this->m_animations = std::move(other.m_animations);
    return *this;
}

void Character::AddAnimation(const Identifier &id, const SpriteList &frames)
{
    m_animations[id] = frames;
}

void Character::Play(const Identifier& id, std::chrono::milliseconds duration, ReplayPolicy replayPolicy)
{
    if(m_animations.empty())
    {
        return;
    }

    if(IsPlaying())
    {
        if((ReplayPolicy::Never == replayPolicy))
        {
            return;
        }
        else if((ReplayPolicy::OnNew == replayPolicy) && (id == GetActive()))
        {
            return;
        }
    }
    //else ReplayPolicy::Always

    auto iter = m_animations.find(id);
    if(iter == m_animations.end())
    {
        m_animInfo.playing = false;
        m_animInfo.activeSpriteIndex = 0;
        m_animInfo.lifetime.Stop();
        return;
    }

    m_animInfo.activeAnim = iter;
    m_animInfo.playing = true;
    m_animInfo.activeSpriteIndex = 0;

    auto animFramesCount = m_animInfo.activeAnim->second.size();
    auto tickPeriod = static_cast<size_t>(duration.count()) / animFramesCount;

    core::Timer::Config timerConfig;
    timerConfig.tickPeriod = std::chrono::milliseconds(tickPeriod);
    timerConfig.duration = duration;

    m_animInfo.lifetime.Setup(timerConfig);
    m_animInfo.lifetime.OnTick([this](const core::Timer::Info& info)
    {
        m_animInfo.activeSpriteIndex = info.tickCount;
    });
    m_animInfo.lifetime.OnTimerEnd([this]()
    {
        m_animInfo.playing = false;
    });
    m_animInfo.lifetime.Start();
}

void Character::Stop()
{
    m_animInfo.playing = false;
}

bool Character::Has(const Character::Identifier &id) const
{
    auto iter = m_animations.find(id);
    return (iter != m_animations.end());
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
    if(m_animInfo.activeAnim != m_animations.end())
    {
        m_animInfo.lifetime.Update(dt);

        auto& sprite = m_animInfo.activeAnim->second[m_animInfo.activeSpriteIndex];
        sprite.setPosition(getPosition());
        sprite.setOrigin(getScale());
        sprite.setScale(getScale());
        sprite.setRotation(getRotation());
    }
}

void Character::Draw(sf::RenderWindow &window)
{
    if(m_animInfo.activeAnim != m_animations.end())
    {
        window.draw(m_animInfo.activeAnim->second[m_animInfo.activeSpriteIndex]);
    }
}

void Character::clear()
{
    m_animInfo.activeAnim = m_animations.end();
    m_animInfo.activeSpriteIndex = 0;
    m_animInfo.playing = false;
}

}
