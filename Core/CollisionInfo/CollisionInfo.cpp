#include "CollisionInfo.h"
#include "../Entity/Entity.h"

namespace core
{

bool CollisionInfo::IsFootSensorActive(Entity &entity)
{
   uint64_t internalId = (*static_cast<uint64_t*>(entity.GetBody()->GetUserData()));
   auto iter = collisionTable.find(internalId);
   if( iter != collisionTable.end() )
   {
       return iter->second.isFootSensorActive;
   }
   return false;
}

bool CollisionInfo::IsHeatSensorActive(Entity &entity)
{
    uint64_t internalId = (*static_cast<uint64_t*>(entity.GetBody()->GetUserData()));
    auto iter = collisionTable.find(internalId);
    if( iter != collisionTable.end() )
    {
        return iter->second.isHeadSensorActive;
    }
    return false;
}

} //end of core
