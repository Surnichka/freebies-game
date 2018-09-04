#include "Application.h"
#include "../Resources/Resources.h"
#include "../Characters/CharacterCreator.h"
#include "../AssetsParser/CharacterParser.h"

void Application::Init()
{
    resources = std::make_unique<core::Resources>();

    characterCreator = std::make_unique<core::CharacterCreator>();
    characterCreator->Init();


}

Application &Application::Get()
{
    static Application app;
    return app;
}
