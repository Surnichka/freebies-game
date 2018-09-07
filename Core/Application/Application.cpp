#include "Application.h"
#include "../Resources/Resources.h"
#include "../Characters/CharacterCreator.h"
#include "../AssetsParser/CharacterParser.h"
#include "../World/PWorld.h"
#include <Box2D/Box2D.h>

void Application::Init()
{
    resources = std::make_unique<core::Resources>();

    characterCreator = std::make_unique<core::CharacterCreator>();
    characterCreator->Init();

    physicWorld = std::make_unique<core::PWorld>();
    physicWorld->Init();
}

Application &Application::Get()
{
    static Application app;
    return app;
}
