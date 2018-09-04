#pragma once
#include <string>

namespace core
{

struct IResourceHolder
{
    IResourceHolder() = default;
    virtual ~IResourceHolder() = default;

    IResourceHolder(IResourceHolder&&) = default;
    IResourceHolder& operator=(IResourceHolder&&) = default;

    IResourceHolder(const IResourceHolder&) = delete;
    IResourceHolder& operator=(const IResourceHolder&) = delete;

    virtual void Aquire(const std::string& id, const std::string& path) = 0;
    virtual void Release(const std::string& id) = 0;

    virtual void Load() = 0;
    virtual void Unload() = 0;
};

} //end of core
