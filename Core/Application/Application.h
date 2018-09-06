#pragma once
#include <memory>
#include <chrono>

namespace core
{
    class Resources;
    class CharacterCreator;
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
    std::chrono::milliseconds frameTime;
    std::unique_ptr<core::Resources> resources;
    std::unique_ptr<core::CharacterCreator> characterCreator;

private:
    Application() = default;
    ~Application() = default;
};
