#include "DungeonGenerator.hpp"
#include "../../globals.hpp"
#include "../fileGenerator/fileGenerator.hpp"
#include "../ruleFileParser/ruleFileParser.hpp"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

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
    std::cout << "map generated" << std::endl;
    t_map map = initMap(width, height, rulePath);

    srand(time(NULL));
    t_point start = {rand() % width, rand() % height};
    defineTile(map, start);
    resetUpdateMap(map);
    updateNeighbors(map, start);

    generationLoop(map);
    return (map);
}

t_map DungeonGenerator::generateMap(const std::string &mapPath)
{
    /*
    need to create something to check if the file is ok
    -> good values
    -> be sure that every defined tile can be next to each other

    maybe create another class for this,
    or update ruleFileParser into fileParser with 2 differents sections
    */
    t_map map = fileGenerator::parseFile(mapPath);
    srand(time(NULL));
    for (int y = 0; y < map.height; y++)
    {
        for (int x = 0; x < map.width; x++)
        {
            if (map.data[y][x].isDefined)
            {
                resetUpdateMap(map);
                updateNeighbors(map, {x, y});
            }
        }
    }
    generationLoop(map);
    return (map);
}

void DungeonGenerator::generationLoop(t_map &map)
{
    for (int i = 0; i < map.width * map.height; i++)
    {
        std::vector<t_point> tilesWithMinPossibility;
        int minPossibility = map.tileset.size() + 1;
        for (int y = 0; y < map.height; y++)
        {
            for (int x = 0; x < map.width; x++)
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
}

t_map DungeonGenerator::initMap(int width, int height, const std::string &rulePath)
{
    t_map map;
    map.width = width;
    map.height = height;
    map.rulePath = rulePath;
    map.tileset = ruleFileParser::parseRuleFile(rulePath);
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
    for (int i = 0; i < 4; i++)
    {
        if (!isNeighborValid(map, directionModifiersArray[i], coord))
            continue;

        t_possibleTiles &neighborTile =
            map.data[coord.y + directionModifiersArray[i].y][coord.x + directionModifiersArray[i].x];
        neighborTile.hasBeenUpdated = true;
        std::vector<int> possibleTiles = combineAllPossibleTiles(map, neighborTile, coord, i);
        if (neighborTile.possiblesTilesID == possibleTiles)
            continue;
        neighborTile.possiblesTilesID = possibleTiles;
        neighborTile.nbPossibleTiles = possibleTiles.size();
        if (neighborTile.nbPossibleTiles == 1)
            neighborTile.isDefined = true;
        updateNeighbors(map, {coord.x + directionModifiersArray[i].x, coord.y + directionModifiersArray[i].y});
    }
}

bool DungeonGenerator::isNeighborValid(t_map &map, t_point modifier, t_point coord)
{
    if (coord.x + modifier.x < 0 || coord.x + modifier.x >= map.width)
        return (false);
    if (coord.y + modifier.y < 0 || coord.y + modifier.y >= map.height)
        return (false);
    if (map.data[coord.y + modifier.y][coord.x + modifier.x].isDefined ||
        map.data[coord.y + modifier.y][coord.x + modifier.x].hasBeenUpdated)
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
