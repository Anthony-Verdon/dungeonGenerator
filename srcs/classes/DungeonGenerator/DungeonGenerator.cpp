#include "DungeonGenerator.hpp"
#include "../../../jsoncpp_x64-linux/include/json/json.h"
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <memory>

std::map<int, std::string> directionsMap{
    {NORTH, "possibilityNorth"},
    {SOUTH, "possibilitySouth"},
    {EAST, "possibilityEast"},
    {WEST, "possibilityWest"},
};

// modifiers.push_back({-1, 0});  // west
// modifiers.push_back({+1, 0});  // east
// modifiers.push_back({0, -1});  // north
// modifiers.push_back({0, +1});  // south
// modifiers.push_back({-1, -1}); // north west
// modifiers.push_back({-1, +1}); // south west
// modifiers.push_back({+1, -1}); // north east
// modifiers.push_back({+1, +1}); // south east
const std::map<int, t_point> modifiersDirection{
    {NORTH, {0, -1}},
    {SOUTH, {0, +1}},
    {EAST, {+1, 0}},
    {WEST, {-1, 0}},
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

    // for (unsigned int i = 0; i < tiles.size(); i++)
    //     std::cout << tiles[i] << std::endl;
    return (tiles);
}

t_map DungeonGenerator::initMap(int width, int height, const std::vector<Tile> &tiles)
{
    t_map map;
    map.width = width;
    map.height = height;
    t_possibleTiles initPossiblesTiles;
    for (unsigned int i = 0; i < tiles.size(); i++)
        initPossiblesTiles.possiblesTilesID.push_back((i));
    initPossiblesTiles.nbPossibleTiles = tiles.size();
    initPossiblesTiles.isDefined = false;

    std::vector<t_possibleTiles> newLine;
    for (int x = 0; x < width; x++)
        newLine.push_back(initPossiblesTiles);
    for (int y = 0; y < height; y++)
        map.data.push_back(newLine);
    return (map);
}

void DungeonGenerator::updateFuturesNeigbors(t_map &map, const std::vector<Tile> &tiles, t_point coord)
{
    if (coord.x < 0 || coord.x >= map.width)
        return;
    if (coord.y < 0 || coord.y >= map.height)
        return;
    if (map.data[coord.y][coord.x].isDefined)
        return;

    std::cout << "x: " << coord.x << " | y: " << coord.y << std::endl;
    std::vector<int> possibleTilesHere = map.data[coord.y][coord.x].possiblesTilesID;
    std::vector<int> allPossibleTilesNorth;
    for (unsigned int i = 0; i < possibleTilesHere.size(); i++)
    {
        std::vector<int> possibleTilesNorth = tiles[possibleTilesHere[i]].getPossibleNeighbors(NORTH);
        allPossibleTilesNorth.insert(allPossibleTilesNorth.end(), possibleTilesNorth.begin(), possibleTilesNorth.end());
        std::sort(allPossibleTilesNorth.begin(), allPossibleTilesNorth.end());
        allPossibleTilesNorth.erase(std::unique(allPossibleTilesNorth.begin(), allPossibleTilesNorth.end()),
                                    allPossibleTilesNorth.end());
        std::cout << "possibleTilesNorth: ";
        for (unsigned int j = 0; j < possibleTilesNorth.size(); j++)
            std::cout << possibleTilesNorth[j] << " ";
        std::cout << std::endl << "allPossibleTilesNorth: ";
        for (unsigned int j = 0; j < allPossibleTilesNorth.size(); j++)
            std::cout << allPossibleTilesNorth[j] << " ";
        std::cout << std::endl;
    }
    if (coord.y == 0)
        return;
    map.data[coord.y - 1][coord.x].possiblesTilesID = allPossibleTilesNorth;
    map.data[coord.y - 1][coord.x].nbPossibleTiles = allPossibleTilesNorth.size();
    if (map.data[coord.y - 1][coord.x].nbPossibleTiles == 1)
        map.data[coord.y - 1][coord.x].isDefined = true;
    else if ((unsigned int)map.data[coord.y - 1][coord.x].nbPossibleTiles != tiles.size())
        updateFuturesNeigbors(map, tiles, {coord.x, coord.y - 1});
}

void DungeonGenerator::defineTile(t_map &map, const std::vector<Tile> &tiles, t_point coord)
{
    // int firstTile = rand() % map.data[coord.y][coord.x].nbPossibleTiles;
    int firstTile = 1; // fourDirection
    map.data[coord.y][coord.x].nbPossibleTiles = 1;
    std::vector<int> newTilesID;
    newTilesID.push_back(map.data[coord.y][coord.x].possiblesTilesID[firstTile]);
    map.data[coord.y][coord.x].possiblesTilesID = newTilesID;
    map.data[coord.y][coord.x].isDefined = true;

    for (auto it = modifiersDirection.begin(); it != modifiersDirection.end(); it++)
    {
        if (coord.x + it->second.x < 0 || coord.x + it->second.x >= map.width)
            continue;
        if (coord.y + it->second.y < 0 || coord.y + it->second.y >= map.height)
            continue;
        if (map.data[coord.y + it->second.y][coord.x + it->second.x].isDefined)
            continue;

        // update of the close neighbors
        auto coordInformations = map.data[coord.y + it->second.y][coord.x + it->second.x];
        std::vector<int> intersection;
        std::set_intersection(coordInformations.possiblesTilesID.begin(), coordInformations.possiblesTilesID.end(),
                              tiles[firstTile].getPossibleNeighbors(it->first).begin(),
                              tiles[firstTile].getPossibleNeighbors(it->first).end(), std::back_inserter(intersection));
        coordInformations.possiblesTilesID = intersection;
        coordInformations.nbPossibleTiles = coordInformations.possiblesTilesID.size();
        if (coordInformations.nbPossibleTiles == 1)
            coordInformations.isDefined = true;
        map.data[coord.y + it->second.y][coord.x + it->second.x] = coordInformations;

        // update of the distance one
        if (!map.data[coord.y + it->second.y][coord.x + it->second.x].isDefined)
        {
            // std::cout << directionsMap[it->first] << ": ";
            // for (int i = 0; i < map.data[coord.y + it->second.y][coord.x + it->second.x].nbPossibleTiles; i++)
            //     std::cout << map.data[coord.y + it->second.y][coord.x + it->second.x].possiblesTilesID[i] << " ";
            // std::cout << std::endl;

            if (directionsMap[it->first] == "possibilityNorth")
                updateFuturesNeigbors(map, tiles, {coord.x + it->second.x, coord.y + it->second.y});
            // on a direction(ex: North), addition all possibleNorthTiles of each tiles
            // if it's differents from tileset size
            //  call again
        }
    }
}

t_map DungeonGenerator::generate(int width, int height, const std::string &rulePath)
{
    std::vector<Tile> tiles = parseRuleFile(rulePath);
    t_map map = initMap(width, height, tiles);
    srand(time(NULL));

    t_point start = {rand() % width, rand() % height};
    defineTile(map, tiles, start);

    // for (int i = 0; i < width * height; i++)
    // {
    //     std::vector<t_point> tilesWithMinPossibility;
    //     int minPossibility = tiles.size() + 1;
    //     for (int y = 0; y < height; y++)
    //     {
    //         for (int x = 0; x < width; x++)
    //         {
    //             if (map.data[y][x].isDefined)
    //                 continue;
    //             if (map.data[y][x].nbPossibleTiles < minPossibility)
    //             {
    //                 minPossibility = map.data[y][x].nbPossibleTiles;
    //                 tilesWithMinPossibility.clear();
    //             }
    //             if (map.data[y][x].nbPossibleTiles == minPossibility)
    //                 tilesWithMinPossibility.push_back({x, y});
    //         }
    //     }

    //     if (tilesWithMinPossibility.size() == 0)
    //         break;
    //     std::cout << map << std::endl;
    //     int newStartID = rand() % tilesWithMinPossibility.size();
    //     t_point coord = tilesWithMinPossibility[newStartID];
    //     if (map.data[coord.y][coord.x].nbPossibleTiles == 0)
    //         std::cout << "problem at x: " << coord.x << " y: " << coord.y << std::endl;
    //     else
    //         defineTile(map, tiles, coord);
    // }
    return (map);
}

std::ostream &operator<<(std::ostream &os, const t_map &instance)
{
    os << "width: " << instance.width << " | height: " << instance.height << std::endl;
    for (int y = 0; y < instance.height; y++)
    {
        for (int x = 0; x < instance.width; x++)
        {
            if (instance.data[y][x].nbPossibleTiles == 1)
                os << "t" << instance.data[y][x].possiblesTilesID[0] << " ";
            else
                os << instance.data[y][x].nbPossibleTiles << "p ";
        }
        os << std::endl;
    }
    return (os);
}
