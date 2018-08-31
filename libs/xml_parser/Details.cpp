#include "Details.h"
#include <iterator>
#include <sstream>
#include "tinyxml2.h"

namespace libs
{
namespace parser
{

int32_t toInteger(const std::string &text)
{
    return std::stoi(text);
}

std::string toText(const std::string &text)
{
    return text;
}

std::vector<int> toIntegerTokens(std::string text)
{
    if( text.empty() )
    {
        return {};
    }

    if(text.front() != '{' || text.back() != '}')
    {
        return {};
    }

    text.erase(0, 1);
    text.pop_back();

    auto digitOrSpace = [](char c) { return (std::isdigit(c) || isspace(c)); };
    auto iter = std::find_if(text.begin(), text.end(), digitOrSpace);

    if( iter == text.end() )
    {
        return {};
    }

    std::stringstream stream(text);
    std::vector<std::string> tokens((std::istream_iterator<std::string>(stream)),
                                     std::istream_iterator<std::string>());

    std::vector<int> integerTokens;
    integerTokens.reserve(tokens.size());
    for(const auto& token : tokens)
    {
        integerTokens.push_back(toInteger(token));
    }

    return integerTokens;
}

sf::Vector2f toVector2f(const std::string &text)
{
    auto token = toIntegerTokens(text);
    if(token.size() != 2)
    {
        throw std::runtime_error("Parsing pos with incorect count number [should be equal to 2] !");
    }
    return sf::Vector2f(token[0], token[1]);
}

sf::FloatRect toFloatRect(const std::string &text)
{
    auto token = toIntegerTokens(text);
    if(token.size() != 4)
    {
        throw std::runtime_error("Parsing rect with incorect count number [should be equal to 4] !");
    }

    return sf::FloatRect(token[0], token[1], token[2], token[3]);
}

bool toBool(const std::string &text)
{
    if(text == "true")
    {
        return true;
    }
    else if(text == "false")
    {
        return false;
    }
    else
    {
        throw std::runtime_error("Parsing bool with wrong name: " + text);
    }
}


Msg toMsg(tinyxml2::XMLElement* element, const Descriptor &descriptor)
{
    Msg msg;
    msg.name = descriptor.name;

    auto addToMsg = [&msg, element](const std::string& id, FieldType fieldType)
    {
        auto atrb = element->Attribute(id.c_str());
        if(nullptr == atrb)
        {
            return;
        }

        switch (fieldType)
        {
            case FieldType::Text:      msg.AddValue(id, toText(atrb));      break;
            case FieldType::Integer:   msg.AddValue(id, toInteger(atrb));   break;
            case FieldType::Bool:      msg.AddValue(id, toBool(atrb));      break;
            //case FieldType::Vector2f:  msg.AddValue(id, toVector2f(atrb));  break;
            //case FieldType::FloatRect: msg.AddValue(id, toFloatRect(atrb)); break;
        }
    };
    for(const auto& p : descriptor.fields)
    {
        addToMsg(p.first, p.second);
    }
    return msg;
}

} //end of parser
} //end of libs
