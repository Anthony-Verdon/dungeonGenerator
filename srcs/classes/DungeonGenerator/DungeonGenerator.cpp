#include "DungeonGenerator.hpp"
#include "../../../jsoncpp_x64-linux/include/json/json.h"
#include <fstream>
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

    std::ifstream ifs(rulePath);
    Json::Reader reader;
    Json::Value obj;
    reader.parse(ifs, obj);
    std::cout << obj["tiles"][0]["path"] << std::endl;

    //--------
    srand(time(NULL));

    t_map map;
    map.width = width;
    map.height = height;

    for (int y = 0; y < height; y++)
    {
        std::vector<int> newLine;
        for (int x = 0; x < width; x++)
            newLine.push_back((rand() % 3));
        map.data.push_back(newLine);
    }

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
