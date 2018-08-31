#pragma once
#include "SFML/Graphics/Rect.hpp"
#include "libs/byte_stream/Msg.h"

#include <string>
#include <vector>
#include <map>

namespace tinyxml2
{
    class XMLElement;
}

namespace libs
{
namespace parser
{

enum class FieldType
{
    Text,
    Integer,
    Bool,
    Vector2f,
    FloatRect
};

struct Descriptor
{
    std::string name;
    std::map<std::string, FieldType> fields;
};

Msg toMsg(tinyxml2::XMLElement* element, const Descriptor& descriptor);

} //end of parser
} //end of libs
