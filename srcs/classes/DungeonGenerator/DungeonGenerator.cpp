#include "DungeonGenerator.hpp"
#include "../../../jsoncpp_x64-linux/include/json/json.h"
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

std::map<int, std::string> directionsMap{
    {NORTH, "possibilityNorth"},
    {SOUTH, "possibilitySouth"},
    {EAST, "possibilityEast"},
    {WEST, "possibilityWest"},
};

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

void DungeonGenerator::resetUpdateMap(t_map &map)
{
    for (int y = 0; y < map.height; y++)
    {
        for (int x = 0; x < map.width; x++)
            map.data[y][x].hasBeenUpdated = false;
    }
}

t_map DungeonGenerator::generate(int width, int height, const std::string &rulePath)
{
    std::vector<Tile> tileset = parseRuleFile(rulePath);
    t_map map = initMap(width, height, tileset);
    srand(time(NULL));

    t_point start = {rand() % width, rand() % height};

    defineTile(map, start);
    resetUpdateMap(map);
    updateNeighbors(map, tileset, start);
    for (int i = 0; i < width * height; i++)
    {
        std::vector<t_point> tilesWithMinPossibility;
        int minPossibility = tileset.size() + 1;
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                if (map.data[y][x].isDefined)
                    continue;
                if (map.data[y][x].nbPossibleTiles < minPossibility)
                {
                    minPossibility = map.data[y][x].nbPossibleTiles;
                    tilesWithMinPossibility.clear();
                }
                if (map.data[y][x].nbPossibleTiles == minPossibility)
                    tilesWithMinPossibility.push_back({x, y});
            }
        }
        if (tilesWithMinPossibility.size() == 0)
            break;
        int index = rand() % tilesWithMinPossibility.size();
        defineTile(map, tilesWithMinPossibility[index]);
        resetUpdateMap(map);
        updateNeighbors(map, tileset, tilesWithMinPossibility[index]);
    }
    return (map);
}

std::vector<Tile> DungeonGenerator::parseRuleFile(const std::string &rulePath)
{
    std::ifstream ifs(rulePath);
    Json::Reader reader;
    Json::Value obj;
    reader.parse(ifs, obj);
    std::vector<Tile> tileset;

    for (int i = 0; obj["tiles"][i]; i++)
    {
        Tile newTile(std::make_unique<Texture>(obj["tiles"][i]["path"].asString()));
        newTile.setID(obj["tiles"][i]["id"].asInt());
        for (auto it = directionsMap.begin(); it != directionsMap.end(); it++)
        {
            for (int j = 0; obj["tiles"][i][it->second][j]; j++)
                newTile.addPossibleNeighbors(it->first, obj["tiles"][i][it->second][j].asInt());
        }
        tileset.push_back(newTile);
    }
    return (tileset);
}

t_map DungeonGenerator::initMap(int width, int height, const std::vector<Tile> &tileset)
{
    t_map map;
    map.width = width;
    map.height = height;
    t_possibleTiles initPossiblesTiles;
    for (unsigned int i = 0; i < tileset.size(); i++)
        initPossiblesTiles.possiblesTilesID.push_back((i));
    initPossiblesTiles.nbPossibleTiles = tileset.size();
    initPossiblesTiles.isDefined = false;

    std::vector<t_possibleTiles> newLine;
    for (int x = 0; x < width; x++)
        newLine.push_back(initPossiblesTiles);
    for (int y = 0; y < height; y++)
        map.data.push_back(newLine);
    return (map);
}

void DungeonGenerator::defineTile(t_map &map, t_point coord)
{
    t_possibleTiles &chosenTile = map.data[coord.y][coord.x];
    int firstTile = rand() % chosenTile.nbPossibleTiles;
    chosenTile.nbPossibleTiles = 1;
    std::vector<int> newTilesID;
    newTilesID.push_back(chosenTile.possiblesTilesID[firstTile]);
    chosenTile.possiblesTilesID = newTilesID;
    chosenTile.isDefined = true;
}

void DungeonGenerator::updateNeighbors(t_map &map, const std::vector<Tile> &tileset, t_point coord)
{
    for (auto it = modifiersDirection.begin(); it != modifiersDirection.end(); it++)
    {
        if (!isNeighborValid(map, *it, coord))
            continue;

        t_possibleTiles &neighborTile = map.data[coord.y + it->second.y][coord.x + it->second.x];
        neighborTile.hasBeenUpdated = true;
        std::vector<int> possibleTiles = combineAllPossibleTiles(map, tileset, neighborTile, *it, coord);
        if (neighborTile.possiblesTilesID == possibleTiles)
            continue;
        neighborTile.possiblesTilesID = possibleTiles;
        neighborTile.nbPossibleTiles = possibleTiles.size();
        if (neighborTile.nbPossibleTiles == 1)
            neighborTile.isDefined = true;
        updateNeighbors(map, tileset, {coord.x + it->second.x, coord.y + it->second.y});
    }
}

bool DungeonGenerator::isNeighborValid(t_map &map, std::pair<int, t_point> dictionnary, t_point coord)
{
    if (coord.x + dictionnary.second.x < 0 || coord.x + dictionnary.second.x >= map.width)
        return (false);
    if (coord.y + dictionnary.second.y < 0 || coord.y + dictionnary.second.y >= map.height)
        return (false);
    if (map.data[coord.y + dictionnary.second.y][coord.x + dictionnary.second.x].isDefined ||
        map.data[coord.y + dictionnary.second.y][coord.x + dictionnary.second.x].hasBeenUpdated)
        return (false);

    return (true);
}

std::vector<int> DungeonGenerator::combineAllPossibleTiles(t_map map, const std::vector<Tile> &tileset,
                                                           t_possibleTiles &neighborTile,
                                                           std::pair<int, t_point> dictionnary, t_point coord)
{
    std::vector<int> possiblesTiles = neighborTile.possiblesTilesID;
    std::vector<int> B;
    for (int i = 0; i < map.data[coord.y][coord.x].nbPossibleTiles; i++)
    {
        std::vector<int> possibleNeighbors =
            tileset[map.data[coord.y][coord.x].possiblesTilesID[i]].getPossibleNeighbors(dictionnary.first);
        B.insert(B.end(), possibleNeighbors.begin(), possibleNeighbors.end());
    }
    std::sort(B.begin(), B.end());
    B.erase(std::unique(B.begin(), B.end()), B.end());
    possiblesTiles.erase(std::remove_if(possiblesTiles.begin(), possiblesTiles.end(),
                                        [&B](int x) { return std::find(B.begin(), B.end(), x) == B.end(); }),
                         possiblesTiles.end());
    return (possiblesTiles);
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
