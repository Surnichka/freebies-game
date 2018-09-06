#include "Character2.h"

namespace core
{

void Character2::AddAnimation(const Identifier &id, SpriteAnimUPtr&& animation)
{
    m_animations[id] = std::move(animation);
}

void Character2::Play(const Identifier &id, std::chrono::milliseconds duration)
{
    m_activeAnim = m_animations.find(id);
    if(m_activeAnim != m_animations.end())
    {
        m_activeAnim->second->Start(duration);
    }
}

void Character2::Stop()
{
    m_activeAnim->second->Stop();
}

bool Character2::Has(const Identifier &id) const
{
    return true;
}

void Character2::Update()
{
    if( m_activeAnim != m_animations.end() )
    {
        m_activeAnim->second->Update(m_characterSprite);
    }

    m_characterSprite.setPosition(getPosition());
    m_characterSprite.setOrigin(getOrigin());
    m_characterSprite.setScale(getScale());
    m_characterSprite.setRotation(getRotation());
}

void Character2::Draw(sf::RenderWindow &window)
{
    window.draw(m_characterSprite);

}

} //end of core
