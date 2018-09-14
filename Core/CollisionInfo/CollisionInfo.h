#pragma once
#include <unordered_map>

namespace core
{

class Entity;
struct CollisionInfo
{
    struct Info
    {
        bool isFootSensorActive = false;
        bool isHeadSensorActive = false;
    };
    std::unordered_map<uint64_t, Info> collisionTable;

    bool IsFootSensorActive(Entity& entity);
    bool IsHeatSensorActive(Entity& entity);

private:
};

} //end of core


