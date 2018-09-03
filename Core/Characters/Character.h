#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include "../Math/Math.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "../Timer/Timer.h"
#include <chrono>
#include <vector>
#include <map>

namespace core
{

enum class ReplayPolicy {OnNew, Always, Never};

class Character
{
public:
    using Identifier = std::string;
    using SpriteList = std::vector<sf::Sprite>;
    using AnimMap = std::map<std::string, SpriteList>;

    void AddAnimation(const Identifier& id, const SpriteList& frames);
    void Play(const Identifier& id, std::chrono::milliseconds duration, ReplayPolicy replayPolicy = ReplayPolicy::OnNew);
    void Stop(const std::string& id);

    bool IsPlaying() const;
    std::string GetActive() const;

    void Update(std::chrono::milliseconds dt);
    void Draw(sf::RenderWindow& window);

    void SetPosition(sf::Vector2f pos);
    void SetScale(sf::Vector2f scale);
    void SetOrigin(sf::Vector2f origin);

    void Move(sf::Vector2f offset);
    void Rotate(float degree);
private:
    struct AnimInfo
    {
        bool playing = false;
        Timer lifetime;
        AnimMap::iterator activeAnim;
        size_t activeSpriteIndex = 0;
    };
    AnimMap m_animations;
    AnimInfo m_animInfo;

    sf::Transformable m_transformable;
};
}//end of core
