#include "DungeonGenerator.hpp"
#include "../../../jsoncpp_x64-linux/include/json/json.h"
#include <algorithm>
#include <cstdlib>
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

void DungeonGenerator::updatePossiblesTiles(std::vector<int> &a, const std::vector<int> &b)
{
    std::vector<int> intersection;
    std::set_intersection(a.begin(), a.end(), b.begin(), b.end(), std::back_inserter(intersection));
    a = intersection;
}

void DungeonGenerator::defineTile(t_map &map, const std::vector<Tile> &tiles, t_point coord)
{
    int firstTile = rand() % map.data[coord.y][coord.x].nbPossibleTiles;
    map.data[coord.y][coord.x].nbPossibleTiles = 1;
    std::vector<int> newTilesID;
    newTilesID.push_back(map.data[coord.y][coord.x].possiblesTilesID[firstTile]);
    map.data[coord.y][coord.x].possiblesTilesID = newTilesID;
    map.data[coord.y][coord.x].isDefined = true;

    if (coord.x - 1 >= 0 && !map.data[coord.y][coord.x - 1].isDefined)
    {
        updatePossiblesTiles(map.data[coord.y][coord.x - 1].possiblesTilesID,
                             tiles[firstTile].getPossibleNeighbors(WEST));
        map.data[coord.y][coord.x - 1].nbPossibleTiles = map.data[coord.y][coord.x - 1].possiblesTilesID.size();
        if (map.data[coord.y][coord.x - 1].nbPossibleTiles == 1)
            map.data[coord.y][coord.x - 1].isDefined = true;
    }
    if (coord.x + 1 < map.width && !map.data[coord.y][coord.x + 1].isDefined)
    {
        updatePossiblesTiles(map.data[coord.y][coord.x + 1].possiblesTilesID,
                             tiles[firstTile].getPossibleNeighbors(EAST));
        map.data[coord.y][coord.x + 1].nbPossibleTiles = map.data[coord.y][coord.x + 1].possiblesTilesID.size();
        if (map.data[coord.y][coord.x + 1].nbPossibleTiles == 1)
            map.data[coord.y][coord.x + 1].isDefined = true;
    }
    if (coord.y - 1 >= 0 && !map.data[coord.y - 1][coord.x].isDefined)
    {
        updatePossiblesTiles(map.data[coord.y - 1][coord.x].possiblesTilesID,
                             tiles[firstTile].getPossibleNeighbors(SOUTH));
        map.data[coord.y - 1][coord.x].nbPossibleTiles = map.data[coord.y - 1][coord.x].possiblesTilesID.size();
        if (map.data[coord.y - 1][coord.x].nbPossibleTiles == 1)
            map.data[coord.y - 1][coord.x].isDefined = true;
    }
    if (coord.y + 1 < map.height && !map.data[coord.y + 1][coord.x].isDefined)
    {
        updatePossiblesTiles(map.data[coord.y + 1][coord.x].possiblesTilesID,
                             tiles[firstTile].getPossibleNeighbors(NORTH));
        map.data[coord.y + 1][coord.x].nbPossibleTiles = map.data[coord.y + 1][coord.x].possiblesTilesID.size();
        if (map.data[coord.y + 1][coord.x].nbPossibleTiles == 1)
            map.data[coord.y + 1][coord.x].isDefined = true;
    }
}
t_map DungeonGenerator::generate(int width, int height, const std::string &rulePath)
{
    std::vector<Tile> tiles = parseRuleFile(rulePath);
    t_map map = initMap(width, height, tiles);
    srand(time(NULL));

    t_point start = {rand() % width, rand() % height};
    defineTile(map, tiles, start);

    for (int i = 0; i < width * height; i++)
    {
        std::vector<t_point> tilesWithMinPossibility;
        int minPossibility = tiles.size() + 1;
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
        std::cout << map << std::endl;
        int newStartID = rand() % tilesWithMinPossibility.size();
        t_point coord = tilesWithMinPossibility[newStartID];
        if (map.data[coord.y][coord.x].nbPossibleTiles == 0)
            std::cout << "problem at x: " << coord.x << " y: " << coord.y << std::endl;
        else
            defineTile(map, tiles, coord);
    }
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
