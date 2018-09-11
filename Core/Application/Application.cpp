#include "Application.h"
#include "../Resources/Resources.h"
#include "../Characters/CharacterCreator.h"
#include "../AssetsParser/CharacterParser.h"
#include "../World/PhysicWorld.h"
#include <Box2D/Dynamics/b2World.h>

void Application::Init()
{
    resources = std::make_unique<core::Resources>();

    characterCreator = std::make_unique<core::CharacterCreator>();
    characterCreator->Init();

    physicWorld = std::make_unique<core::PhysicWorld>();
    physicWorld->Init();
}

Application &Application::Get()
{
    static Application app;
    return app;
}
