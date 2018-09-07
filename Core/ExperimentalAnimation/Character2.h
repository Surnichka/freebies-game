#pragma once
#include "ISpriteAnimation.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <map>
#include <memory>

namespace core
{

class Character2 : public sf::Transformable
{
public:
    using Identifier = std::string;
    using SpriteAnimUPtr = std::unique_ptr<ISpriteAnimation>;
    void AddAnimation(const Identifier& id, SpriteAnimUPtr&& animation);

    void Play(const Identifier& id, std::chrono::milliseconds duration);
    void Stop();
    bool Has(const Identifier& id) const;

    void Update();
    void Draw(sf::RenderWindow& window);
private:
    using AnimMap = std::map<Identifier, SpriteAnimUPtr>;

    sf::Sprite m_characterSprite;
    AnimMap m_animations;
    AnimMap::iterator m_activeAnim = m_animations.end();
};
}//end of core
