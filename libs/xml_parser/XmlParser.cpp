#include "XmlParser.h"
#include "tinyxml2.h"
#include <map>
#include <vector>

namespace libs
{

void XmlParser::Init()
{
    m_parsers["Image"] = [&](tinyxml2::XMLElement* element)->Msg
    {
        parser::Descriptor descriptor;
        descriptor.name = "Image";
        descriptor.fields["id"] = parser::FieldType::Text;
        descriptor.fields["path"] = parser::FieldType::Text;
        descriptor.fields["pos"] = parser::FieldType::Vector2f;
        descriptor.fields["srcRect"] = parser::FieldType::FloatRect;
        descriptor.fields["dstRect"] = parser::FieldType::FloatRect;

        auto msg = parser::toMsg(element, descriptor);
        return msg;
    };

    m_parsers["Animation"] = [&](tinyxml2::XMLElement* element)->Msg
    {
        std::map<std::string, std::vector<Msg>> animations;

        auto animationTypeEl = element->FirstChildElement();
        while(nullptr != animationTypeEl)
        {
            std::vector<Msg> images;
            auto containerEl = animationTypeEl->FirstChildElement();
            while(nullptr != containerEl)
            {
                std::string fieldName = containerEl->Name();
                if(fieldName != "Image")
                {
                    throw std::runtime_error("Animation can be parsed with only Image types");
                }
                auto imageMsg = m_parsers.at("Image")(containerEl);
                images.emplace_back(std::move(imageMsg));

                containerEl = containerEl->NextSiblingElement();
            }
            animations[animationTypeEl->Name()] = std::move(images);
        }

        Msg msg;
//        msg.AddValue("animations", animations);
        return msg;
    };

    m_parsers["Tag"] = [&](tinyxml2::XMLElement* element)->Msg
    {
        parser::Descriptor descriptor;
        descriptor.name = "Tag";
        descriptor.fields["id"] = parser::FieldType::Text;
        descriptor.fields["version"] = parser::FieldType::Text;

        Msg msg = parser::toMsg(element, descriptor);
        std::vector<Msg> childs;

        auto child = element->FirstChildElement();
        while(nullptr != child)
        {
             std::string name = child->Name();
             auto iter = m_parsers.find(name);
             if( iter == m_parsers.end() )
             {
                 //TODO(borko) - add warning
                 continue;
             }
             auto msg = iter->second( child );
             childs.emplace_back(std::move(msg));
             child = child->NextSiblingElement();
        }

//        msg.AddValue("childs", childs);
        return msg;
    };
}

void XmlParser::LoadFile(const std::string &filePath)
{
    tinyxml2::XMLDocument doc;
    doc.LoadFile(filePath.c_str());
    if( doc.Error() )
    {
        throw std::runtime_error("Failed to parse xml, path: " + filePath);
    }
    auto root = doc.RootElement();
    auto tagElement = root->FirstChildElement();

    while(nullptr != tagElement)
    {
        auto msg = m_parsers.at("Tag")(tagElement);

        tagElement = tagElement->NextSiblingElement();
    }
}

}
