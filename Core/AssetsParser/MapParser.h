#pragma once
#include <vector>
#include <string>

namespace core
{
class MapParser
{
public:
    using TexturePath = std::string;
    using MapRow = std::vector<TexturePath>;
    using MapGrid = std::vector<MapRow>;

    void Parse();

    const MapGrid& GetMapGrid() const;
private:
    MapGrid m_mapGrid;
};
}
