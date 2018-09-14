#include "CollisionListener.h"
#include "../Application/Application.h"
#include "../World/PhysicWorldUtils.h"
#include "CollisionInfo.h"
#include <Box2D/Dynamics/Contacts/b2Contact.h>

namespace core
{

namespace helper
{
    enum class Fixture { A, B };
    uint64_t GetBodyId(b2Contact* contact, Fixture fixture)
    {
        if( Fixture::A == fixture)
        {
            return (*static_cast<uint64_t*>(contact->GetFixtureA()->GetBody()->GetUserData()));
        }
        else if(Fixture::B == fixture)
        {
            return (*static_cast<uint64_t*>(contact->GetFixtureB()->GetBody()->GetUserData()));
        }
        else
        {
            throw std::runtime_error("Trying to get fixture that doesnt exist!");
        }
    }

    int32_t GetFixtureId(b2Contact* contact, Fixture fixture)
    {
        if( Fixture::A == fixture )
        {
            return (*static_cast<int32_t*>(contact->GetFixtureA()->GetUserData()));
        }
        else if( Fixture::B == fixture )
        {
            return (*static_cast<int32_t*>(contact->GetFixtureB()->GetUserData()));
        }
        else
        {
            throw std::runtime_error("Trying to get fixture that doesnt exist!");
        }
    }


    void CheckFootSensor(b2Contact* contact, bool contactTag)
    {
        auto& colInfo = Application::Get().collisionInfo;
        if( fixtureTypes::footSensor == GetFixtureId(contact, Fixture::A) )
        {
            auto id = GetBodyId(contact, Fixture::A);
            colInfo->collisionTable[id].isFootSensorActive = contactTag;
        }
        else if( fixtureTypes::footSensor == GetFixtureId(contact, Fixture::B) )
        {
            auto id = GetBodyId(contact, Fixture::B);
            colInfo->collisionTable[id].isFootSensorActive = contactTag;
        }
    }

    void CheckHeadSensor(b2Contact* contact, bool contactTag)
    {
        auto& colInfo = Application::Get().collisionInfo;
        if( fixtureTypes::headSensor == GetFixtureId(contact, Fixture::A) )
        {
            auto id = GetBodyId(contact, Fixture::A);
            colInfo->collisionTable[id].isHeadSensorActive = contactTag;
        }
        else if( fixtureTypes::headSensor == GetFixtureId(contact, Fixture::B) )
        {
            auto id = GetBodyId(contact, Fixture::B);
            colInfo->collisionTable[id].isHeadSensorActive = contactTag;
        }
    }
}

void CollisionListener::BeginContact(b2Contact *contact)
{
    helper::CheckFootSensor(contact, true);
    helper::CheckHeadSensor(contact, true);
}

void CollisionListener::EndContact(b2Contact *contact)
{
    helper::CheckFootSensor(contact, false);
    helper::CheckHeadSensor(contact, false);
}

} //end of core

