#include "DungeonGenerator.hpp"
#include <iostream>

/*information example for rule
    path {string}
    id {number}
    possibilityNorth {tileID, prob}
    possibilitySouth {tileID, prob}
    possibilityEast {tileID, prob}
    possibilityWest {tileID, prob}

    {

    }
*/

t_map DungeonGenerator::generate(int width, int height, const std::string &rulePath)
{
    (void)rulePath;
    std::vector<int> emptyLine;
    for (int i = 0; i < width; i++)
        emptyLine.push_back(-1);
    t_map map;
    map.width = width;
    map.height = height;
    for (int i = 0; i < height; i++)
        map.data.push_back(emptyLine);

    return (map);
}

std::ostream &operator<<(std::ostream &os, const t_map &instance)
{
    os << "width: " << instance.width << " | height: " << instance.height << std::endl;
    for (int x = 0; x < instance.width; x++)
    {
        for (int y = 0; y < instance.height; y++)
            os << instance.data[x][y] << " ";
        os << std::endl;
    }
    return (os);
}
