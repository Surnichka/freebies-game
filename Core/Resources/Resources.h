#pragma once
#include <map>
#include "ResourceHolder.h"
#include <memory>

namespace core
{

class Resources
{
public:
    template<typename T>
    ResourceHolder<T>* AddHolder(const std::string& name)
    {
        auto& ptr = m_resourceHolders[name];
        ptr = std::make_unique<ResourceHolder<T>>();
        return static_cast<ResourceHolder<T>*>(ptr.get());
    }

    template<typename T>
    ResourceHolder<T>* GetHolder(const std::string& name)
    {
        auto iter = m_resourceHolders.find(name);
        if(iter == m_resourceHolders.end())
        {
            return AddHolder<T>(name);
        }
        return static_cast<ResourceHolder<T>*>(iter->second.get());
    }

    bool HasHolder(const std::string& name)
    {
        auto iter = m_resourceHolders.find(name);
        return (iter != m_resourceHolders.end());
    }

    void RemoveHolder(const std::string& name)
    {
        m_resourceHolders.erase(name);
    }
private:
    std::map<std::string, std::unique_ptr<IResourceHolder>> m_resourceHolders;
};

} //end of core
