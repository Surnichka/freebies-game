#include "CollisionInfo.h"
#include "../Entity/Entity.h"
#include <iostream>

namespace core
{

bool CollisionInfo::IsSensorActive(const std::string &sensor, Entity &entity)
{
    uint64_t internalId = (*static_cast<uint64_t*>(entity.GetBody()->GetUserData()));
    auto iter = collisionTable.find(internalId);
    if( iter != collisionTable.end() )
    {
        auto sensorIter = iter->second.find(sensor);
        if( sensorIter != iter->second.end() )
        {
            if(sensor == "head")
            {
                std::cout << "Entity: " << internalId << "|Sensor: " <<  sensorIter->first
                          << "|Count: " << sensorIter->second << std::endl;
            }
            return (sensorIter->second != 0);
        }
        else
        {
            return false;
        }
    }
    return false;
}

} //end of core
