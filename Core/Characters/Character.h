#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "../Math/Math.h"
#include "../Timer/Timer.h"
#include <chrono>
#include <vector>
#include <map>
#include <iostream>

namespace core
{

enum class ReplayPolicy {OnNew, Always, Never};

class Character : public sf::Transformable
{
public:
    using Identifier = std::string;
    using SpriteList = std::vector<sf::Sprite>;
    using AnimMap = std::map<std::string, SpriteList>;

    Character();
    ~Character() = default;

    Character(const Character& other);
    Character& operator=(const Character& other);

    Character(Character&& other);
    Character& operator=(Character&& other);

    void AddAnimation(const Identifier& id, const SpriteList& frames);
    void Play(const Identifier& id, std::chrono::milliseconds duration, ReplayPolicy replayPolicy = ReplayPolicy::OnNew);
    void Stop();
    bool Has(const Identifier& id) const;

    bool IsPlaying() const;
    std::string GetActive() const;

    void Update();
    void Draw(sf::RenderWindow& window);
private:
    friend class ICharacterAnimation;
    sf::Sprite m_activeSprite;

    void clear();
    struct AnimInfo
    {
        bool playing = false;
        Timer lifetime;
        AnimMap::iterator activeAnim;
        size_t activeSpriteIndex = 0;
    };
    AnimMap m_animations;
    AnimInfo m_animInfo;
};
}//end of core
