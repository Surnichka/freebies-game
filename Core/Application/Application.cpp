#include "Application.h"
#include "../Resources/Resources.h"

#include "../Animator/AnimatorFactory.h"
#include "../AssetsParser/CharacterParser.h"

#include "../World/World.h"
#include <Box2D/Dynamics/b2World.h>

#include "../CollisionInfo/CollisionInfo.h"
#include "../CollisionInfo/CollisionListener.h"

void Application::Init()
{
    resources = std::make_unique<core::Resources>();

    animatorFactory = std::make_unique<core::AnimatorFactory>();
    animatorFactory->Init();

    m_collisionListener = std::make_unique<core::CollisionListener>();

    world = std::make_unique<core::World>();
    world->Init();
    world->GetPhysicWorld()->SetContactListener(m_collisionListener.get());

    collisionInfo = std::make_unique<core::CollisionInfo>();
}

Application &Application::Get()
{
    static Application app;
    return app;
}
