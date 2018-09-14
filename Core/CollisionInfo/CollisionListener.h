#pragma once
#include <Box2D/Dynamics/b2WorldCallbacks.h>

namespace core
{

class CollisionListener : public b2ContactListener
{
private:
    void BeginContact(b2Contact* contact) override;
    void EndContact(b2Contact* contact) override;

};
} //end of core


