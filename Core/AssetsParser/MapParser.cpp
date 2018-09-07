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
}

void MapParser::Parse()
{
    for(const auto& mapRow : experimental::map)
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
