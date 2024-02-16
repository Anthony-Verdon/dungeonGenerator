#include "DungeonGenerator.hpp"
#include "../../../libs/jsoncpp_x64-linux/include/json/json.h"
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
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
    std::ifstream ifs(rulePath);
    Json::Reader reader;
    Json::Value obj;
    reader.parse(ifs, obj);

    try
    {
        if (!obj)
            throw(std::runtime_error("rule file invalid: can't read " + rulePath));

        Json::Value::Members members = obj.getMemberNames();
        if (members.size() != 1 || !obj.isMember("tiles"))
            throw(std::runtime_error("rule file invalid: no member \"tiles\" or too much members"));

        Json::Value tiles = obj["tiles"];
        if (!tiles.isArray() || tiles.size() < 1)
            throw(std::runtime_error("rule file invalid: \"tiles\" isn't an array or has no value in it"));
        for (unsigned int i = 0; i < tiles.size(); i++)
        {
            Json::Value::Members tile = tiles[i].getMemberNames();
            if (!tiles[i].isMember("path") || !tiles[i]["path"].isString())
                throw(std::runtime_error("rule file invalid: \"tiles\" element \"" + std::to_string(i) +
                                         "\" has no value \"path\" or it value isn't a string"));
            for (auto it = directionsMap.begin(); it != directionsMap.end(); it++)
            {
                if (!tiles[i].isMember(it->second) || !tiles[i][it->second].isArray() ||
                    tiles[i][it->second].size() == 0)
                    throw(std::runtime_error("rule file invalid: \"tiles\" element \"" + std::to_string(i) +
                                             "\" has no value \"" + it->second +
                                             "\", it value isn't an array or it has no element in it"));
                for (unsigned int j = 0; j < tiles[i][it->second].size(); j++)
                {
                    if (!tiles[i][it->second][j].isInt() || tiles[i][it->second][j] < 0 ||
                        tiles[i][it->second][j] >= tiles.size())
                        throw(std::runtime_error("rule file invalid: \"tiles\" element [" + std::to_string(i) + "][" +
                                                 std::to_string(j) + "] isn't an int or is an incorrect value"));
                }
            }
        }
    }
    catch (const std::exception &exception)
    {
        std::cout << exception.what() << std::endl;
        return (false);
    }
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

t_map DungeonGenerator::generateMap(int width, int height, const std::string &rulePath)
{
    t_map map = initMap(width, height, rulePath);
    srand(time(NULL));

    t_point start = {rand() % width, rand() % height};

    defineTile(map, start);
    resetUpdateMap(map);
    updateNeighbors(map, start);
    for (int i = 0; i < width * height; i++)
    {
        std::vector<t_point> tilesWithMinPossibility;
        int minPossibility = map.tileset.size() + 1;
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
        updateNeighbors(map, tilesWithMinPossibility[index]);
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
        newTile.setID(i);
        for (auto it = directionsMap.begin(); it != directionsMap.end(); it++)
        {
            for (int j = 0; obj["tiles"][i][it->second][j]; j++)
                newTile.addPossibleNeighbors(it->first, obj["tiles"][i][it->second][j].asInt());
        }
        tileset.push_back(newTile);
    }
    return (tileset);
}

t_map DungeonGenerator::initMap(int width, int height, const std::string &rulePath)
{
    t_map map;
    map.width = width;
    map.height = height;
    map.rulePath = rulePath;
    map.tileset = parseRuleFile(rulePath);
    t_possibleTiles initPossiblesTiles;
    for (unsigned int i = 0; i < map.tileset.size(); i++)
        initPossiblesTiles.possiblesTilesID.push_back((i));
    initPossiblesTiles.nbPossibleTiles = map.tileset.size();
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

void DungeonGenerator::updateNeighbors(t_map &map, t_point coord)
{
    for (auto it = modifiersDirection.begin(); it != modifiersDirection.end(); it++)
    {
        if (!isNeighborValid(map, *it, coord))
            continue;

        t_possibleTiles &neighborTile = map.data[coord.y + it->second.y][coord.x + it->second.x];
        neighborTile.hasBeenUpdated = true;
        std::vector<int> possibleTiles = combineAllPossibleTiles(map, neighborTile, coord, it->first);
        if (neighborTile.possiblesTilesID == possibleTiles)
            continue;
        neighborTile.possiblesTilesID = possibleTiles;
        neighborTile.nbPossibleTiles = possibleTiles.size();
        if (neighborTile.nbPossibleTiles == 1)
            neighborTile.isDefined = true;
        updateNeighbors(map, {coord.x + it->second.x, coord.y + it->second.y});
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

std::vector<int> DungeonGenerator::combineAllPossibleTiles(t_map map, t_possibleTiles &neighborTile, t_point coord,
                                                           int direction)
{
    std::vector<int> possiblesTiles = neighborTile.possiblesTilesID;
    std::vector<int> B;
    for (int i = 0; i < map.data[coord.y][coord.x].nbPossibleTiles; i++)
    {
        std::vector<int> possibleNeighbors =
            map.tileset[map.data[coord.y][coord.x].possiblesTilesID[i]].getPossibleNeighbors(direction);
        B.insert(B.end(), possibleNeighbors.begin(), possibleNeighbors.end());
    }
    std::sort(B.begin(), B.end());
    B.erase(std::unique(B.begin(), B.end()), B.end());
    possiblesTiles.erase(std::remove_if(possiblesTiles.begin(), possiblesTiles.end(),
                                        [&B](int x) { return std::find(B.begin(), B.end(), x) == B.end(); }),
                         possiblesTiles.end());
    return (possiblesTiles);
}

void DungeonGenerator::generateFile(t_map map)
{
    std::ofstream fileGenerated("lastMapGenerated.txt");
    fileGenerated << map.width << " " << map.height << std::endl;
    fileGenerated << map.rulePath << std::endl;
    for (int y = 0; y < map.height; y++)
    {
        for (int x = 0; x < map.width; x++)
            fileGenerated << map.data[y][x].possiblesTilesID[0] << " ";
        fileGenerated << std::endl;
    }
    fileGenerated.close();
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
