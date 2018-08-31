#pragma once
#include "Details.h"
#include <functional>

namespace tinyxml2
{
    class XMLElement;
}

namespace libs
{

class XmlParser
{
public:
    void Init();
    void LoadFile(const std::string& filePath);
private:
    std::map<std::string, std::function<Msg(tinyxml2::XMLElement*)>> m_parsers;
};

}
