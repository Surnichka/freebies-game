#pragma once
#include "IResourceHolder.h"
#include <map>
#include <memory>
#include <iostream>

namespace core
{

template<typename T>
struct ResourceHolder : public IResourceHolder
{
    void Aquire(const std::string& id, const std::string& path) final override
    {
        auto iter = m_resourcesData.find(id);
        if(iter == m_resourcesData.end())
        {
            m_resourcesData[id] = {path, true};
        }
    }

    void Release(const std::string& id) final override
    {
        m_resourcesData.erase(id);
    }

    void Load() final override
    {
        for(const auto& p : m_resourcesData)
        {
            if(p.second.needReload)
            {
                const auto& key = p.first;
                const auto& path = p.second.path;
                load(key, path);
            }
        }
    }

    void Unload() final override
    {
        m_storedResources.clear();
    }

    const T& Get(const std::string& id)
    {
        auto iter = m_storedResources.find(id);
        if(iter == m_storedResources.end())
        {
            auto dataIter = m_resourcesData.find(id);
            if(dataIter == m_resourcesData.end())
            {
                throw std::runtime_error("Trying To Get Resource That Doesn't Aquired In ResourceHolder");
            }
            else
            {
                const auto& key = dataIter->first;
                const auto& path = dataIter->second.path;
                auto& resource = load(key, path);

                return *(static_cast<const T*>(resource.get()));
            }
        }
        return *(static_cast<const T*>(iter->second.get()));
    }
private:
    std::unique_ptr<T>& load(const std::string& id, const std::string& path)
    {
        auto& resource = m_storedResources[id];
        resource = std::make_unique<T>();
        resource->loadFromFile(path);
        return resource;
    }

    struct DataInfo
    {
        std::string path;
        bool needReload = false;
    };

    std::map<std::string, DataInfo> m_resourcesData;
    std::map<std::string, std::unique_ptr<T>> m_storedResources;
};

} //end of core
