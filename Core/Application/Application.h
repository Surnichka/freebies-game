#pragma once
#include <memory>
#include <chrono>
#include <SFML/System/Vector2.hpp>

namespace core
{
    class Resources;
    class AnimatorFactory;
    class PhysicWorld;
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
    std::unique_ptr<core::PhysicWorld> physicWorld;
private:
    Application() = default;
    ~Application() = default;
};
