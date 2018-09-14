#include "MapParser.h"
#include <map>

namespace core
{

namespace experimental
{
    const std::map<char, std::string> ids =
    {
        {'O', ""},
        {'T', "../freebies-game/Assets/Box.png"},
        {'D', "../freebies-game/Assets/Tree_2.png"},
    };
    //20 row, 16 height
    const std::vector<std::string> map =
    {
        "OOOOOOOOOOOOOOOOOOOO",
        "TOOOODOOOOOOOOOOOOOT",
        "TOOOOOOOOOOOOTOOOOOT",
        "TOOOOOOOOOOOOOOOOOOT",
        "TTTOOOOOOTTTOOTOOOOT",
        "TOOTTTTTOOOOTOOOOOOT",
        "TOOOOOOOOOOOOOOOTOOT",
        "TOOOOOOOOOOOOOOTOOOT",
        "TOOOODOOOOOOOOTOOOOT",
        "TOOOOOOOOOOOOTOOOOOT",
        "TOOOOOOOOOOTTOOOOOOT",
        "TTTOOOOOOOTTOOOOOOOT",
        "TOOTTTTTOOOOOOOOOOOT",
        "TOOOOOOOOOOOOOOOOOOT",
        "TOOOOOOOOOOOOOOOOOOT",
        "TTTTTTTTTTTTTTTTTTTT",
    };

    const std::vector<std::string> map2 =
    {
        "OOOOOOOOOOOOOOOOOOOO",
        "TOOOOOOOOOOOOOOOOOOT",
        "TOOOOOOOOOOOOOOOOOOT",
        "TOOOTTTTTTTTTTTTTTTT",
        "TTOOOOOOOOOOOOOOOOOT",
        "TTTOOOOOOOOOOOOOOOOT",
        "TTTTTTTTTTTTTTTTOOOT",
        "TOOOOOOOOOOOOOOOOOTT",
        "TOOOOOOOOOOOOOOOOTTT",
        "TOOOTTTTTTTTTTTTTTTT",
        "TTOOOOOOOOOOOOOOOOOT",
        "TTTOOOOOOOOOOOOOOOOT",
        "TTTTTTTTTTTTTTTTOOOT",
        "TOOOOOOOOOOOOOOOOOTT",
        "TOOOOOOOOOOOOOOOOTTT",
        "TTTTTTTTTTTTTTTTTTTT",
    };
}

void MapParser::Parse()
{
    for(const auto& mapRow : experimental::map2)
    {
        MapRow row;
        for(auto id : mapRow)
        {
            const auto& path = experimental::ids.at(id);
            row.push_back(path);
        }
        m_mapGrid.emplace_back(std::move(row));
    }
}

const MapParser::MapGrid &MapParser::GetMapGrid() const
{
    return m_mapGrid;
}

} //end of core
