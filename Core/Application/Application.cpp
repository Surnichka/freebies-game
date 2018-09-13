#include "Application.h"
#include "../Resources/Resources.h"

#include "../Animator/AnimatorFactory.h"
#include "../AssetsParser/CharacterParser.h"

#include "../World/World.h"
#include <Box2D/Dynamics/b2World.h>


void Application::Init()
{
    resources = std::make_unique<core::Resources>();

    animatorFactory = std::make_unique<core::AnimatorFactory>();
    animatorFactory->Init();

    world = std::make_unique<core::World>();
    world->Init();
}

Application &Application::Get()
{
    static Application app;
    return app;
}
