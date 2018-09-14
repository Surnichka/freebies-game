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

    void CheckForSensors(b2Contact* contact,
                         const std::string& sensorName,
                         int32_t fixtureType,
                         int32_t sensorModifier)
    {
        auto& colInfo = Application::Get().collisionInfo;
        if( fixtureType == GetFixtureId(contact, Fixture::A) )
        {
            auto id = GetBodyId(contact, Fixture::A);
            colInfo->collisionTable[id][sensorName] += sensorModifier;
        }
        else if( fixtureType == GetFixtureId(contact, Fixture::B) )
        {
            auto id = GetBodyId(contact, Fixture::B);
            colInfo->collisionTable[id][sensorName] += sensorModifier;
        }
    }
}

void CollisionListener::BeginContact(b2Contact *contact)
{
    helper::CheckForSensors(contact, "head", fixtureTypes::headSensor, (1));
    helper::CheckForSensors(contact, "foot", fixtureTypes::footSensor, (1));
}

void CollisionListener::EndContact(b2Contact *contact)
{
    helper::CheckForSensors(contact, "head", fixtureTypes::headSensor, (-1));
    helper::CheckForSensors(contact, "foot", fixtureTypes::footSensor, (-1));
}

} //end of core

