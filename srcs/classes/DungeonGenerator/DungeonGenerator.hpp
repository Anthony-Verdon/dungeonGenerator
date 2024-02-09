#pragma once

#include "../Tile/Tile.hpp"
#include <string>
#include <vector>

typedef struct s_point
{
    int x;
    int y;
} t_point;

typedef struct s_possibleTiles
{
    bool isDefined;
    int nbPossibleTiles;
    std::vector<int> possiblesTilesID;
} t_possibleTiles;

typedef struct s_map
{
    int width;
    int height;
    std::vector<std::vector<t_possibleTiles>> data;
} t_map;

class DungeonGenerator
{
  private:
    static std::vector<Tile> parseRuleFile(const std::string &rulePath);
    static t_map initMap(int width, int height, const std::vector<Tile> &tiles);
    static void defineTile(t_map &map, const std::vector<Tile> &tiles, t_point coord);
    static void updateFuturesNeigbors(t_map &map, const std::vector<Tile> &tiles, t_point coord);

  public:
    static bool isRuleFileValid(const std::string &rulePath);

    static t_map generate(int width, int height, const std::string &rulePath);
};

std::ostream &operator<<(std::ostream &os, const t_map &instance);