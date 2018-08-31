#pragma once

#include "InByteStream.h"
#include "OutByteStream.h"

namespace libs
{

class Msg
{
public:
    std::string name;

    template<typename T>
    void AddValue(const std::string& name, T&& value)
    {
        libs::oByteStream out;
        out << std::forward<T>(value);

        m_msgs.insert({name, out.GetBuffer()});
    }

    template<typename T>
    bool GetValue(const std::string& name, T& value) const
    {
        auto iter = m_msgs.find(name);
        if(iter != m_msgs.end())
        {
            libs::iByteStream in(iter->second);
            in >> value;
            return true;
        }
        return false;
    }

    bool HasValue(const std::string& name) const;

private:
    std::unordered_map<std::string, std::vector<uint8_t>> m_msgs;

};

} //end of namespace libs
