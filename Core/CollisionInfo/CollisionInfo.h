#pragma once
#include <unordered_map>

namespace core
{

class Entity;
struct CollisionInfo
{
    using InfoMap = std::unordered_map<std::string, int32_t>;
    std::unordered_map<uint64_t, InfoMap> collisionTable;

    bool IsSensorActive(const std::string& sensor, Entity& entity);
};

} //end of core


