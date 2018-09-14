#pragma once
#include <memory>
#include <chrono>
#include <SFML/System/Vector2.hpp>

namespace core
{
    class Resources;
    class AnimatorFactory;
    class World;
    class CollisionInfo;
    class CollisionListener;
}

class Application
{
public:
    Application(const Application&) = delete;
    Application(Application&&) = delete;
    Application& operator=(const Application&) = delete;
    Application& operator=(Application&&) = delete;

    void Init();
    static Application& Get();

public:
    sf::Vector2f windowSize = {1440, 1024};
    std::chrono::milliseconds frameTime;
    std::unique_ptr<core::Resources> resources;
    std::unique_ptr<core::AnimatorFactory> animatorFactory;
    std::unique_ptr<core::World> world;
    std::unique_ptr<core::CollisionInfo> collisionInfo;
private:
    std::unique_ptr<core::CollisionListener> m_collisionListener;
    Application() = default;
    ~Application() = default;
};
