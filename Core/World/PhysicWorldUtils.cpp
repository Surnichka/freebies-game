#include "PhysicWorldUtils.h"
#include "../Application/Application.h"
#include "../World/World.h"
#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2World.h>

namespace core
{

float PixelToMeter(float pixel)
{
    return pixel * (1.0f / physicWorldScale);
}

float MeterToPixel(float meter)
{
    return meter * physicWorldScale;
}

void BodyDeleter::operator()(b2Body *body)
{
    Application::Get().world->GetPhysicWorld()->DestroyBody(body);
}

} // end of core
