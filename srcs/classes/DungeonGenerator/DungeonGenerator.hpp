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
    bool hasBeenUpdated;
    int nbPossibleTiles;
    std::vector<int> possiblesTilesID;
} t_possibleTiles;

typedef struct s_map
{
    int width;
    int height;
    std::string rulePath;
    std::vector<Tile> tileset;
    std::vector<std::vector<t_possibleTiles>> data;
} t_map;

class DungeonGenerator
{
  private:
    static bool isRuleFileValid(const std::string &rulePath);
    static t_map initMap(int width, int height, const std::string &rulePath);
    static std::vector<Tile> parseRuleFile(const std::string &rulePath);
    static void defineTile(t_map &map, t_point coord);
    static void resetUpdateMap(t_map &map);
    static void updateNeighbors(t_map &map, t_point coord);
    static bool isNeighborValid(t_map &map, std::pair<int, t_point> dictionnary, t_point coord);
    static std::vector<int> combineAllPossibleTiles(t_map map, t_possibleTiles &neighborTile, t_point coord,
                                                    int direction);

  public:
    static t_map generateMap(int width, int height, const std::string &rulePath);
    static void generateFile(t_map map);
};

std::ostream &operator<<(std::ostream &os, const t_map &instance);