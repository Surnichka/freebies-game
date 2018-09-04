#pragma once
#include <memory>

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

    std::unique_ptr<core::Resources> resources;
    std::unique_ptr<core::CharacterCreator> characterCreator;

private:
    Application() = default;
    ~Application() = default;
};
