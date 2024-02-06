#include "DungeonGenerator.hpp"
#include "../../../jsoncpp_x64-linux/include/json/json.h"
#include <fstream>
#include <iostream>
#include <memory>

const std::map<int, std::string> directionsMap{
    {NORTH, "possibilityNorth"},
    {SOUTH, "possibilitySouth"},
    {EAST, "possibilityEast"},
    {WEST, "possibilityWest"},
};

bool DungeonGenerator::isRuleFileValid(const std::string &rulePath)
{
    (void)rulePath;
    return (true);
}

std::vector<Tile> DungeonGenerator::parseRuleFile(const std::string &rulePath)
{
    std::ifstream ifs(rulePath);
    Json::Reader reader;
    Json::Value obj;
    reader.parse(ifs, obj);
    std::vector<Tile> tiles;

    for (int i = 0; obj["tiles"][i]; i++)
    {
        Tile newTile(std::make_unique<Texture>(obj["tiles"][i]["path"].asString()));
        newTile.setID(obj["tiles"][i]["id"].asInt());
        for (auto it = directionsMap.begin(); it != directionsMap.end(); it++)
        {
            for (int j = 0; obj["tiles"][i][it->second][j]; j++)
                newTile.addPossibleNeighbors(it->first, obj["tiles"][i][it->second][j].asInt());
        }
        tiles.push_back(newTile);
    }

    for (unsigned int i = 0; i < tiles.size(); i++)
        std::cout << tiles[i] << std::endl;
    return (tiles);
}

t_map DungeonGenerator::generate(int width, int height, const std::string &rulePath)
{
    parseRuleFile(rulePath);
    srand(time(NULL));

    t_map map;
    map.width = width;
    map.height = height;

    for (int y = 0; y < height; y++)
    {
        std::vector<int> newLine;
        for (int x = 0; x < width; x++)
            newLine.push_back((rand() % 4));
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
