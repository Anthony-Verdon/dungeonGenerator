#pragma once

#include "../Tile/Tile.hpp"
#include <string>
#include <vector>
#include "../../structs/t_map.hpp"
#include "../../structs/t_point.hpp"
#include "../../structs/t_possibleTiles.hpp"

class DungeonGenerator
{
  private:
    static t_map initMap(int width, int height, const std::string &rulePath);
    static void defineTile(t_map &map, t_point coord);
    static void resetUpdateMap(t_map &map);
    static void updateNeighbors(t_map &map, t_point coord);
    static bool isNeighborValid(t_map &map, t_point modifier, t_point coord);
    static std::vector<int> combineAllPossibleTiles(t_map map, t_possibleTiles &neighborTile, t_point coord,
                                                    int direction);

  public:
    static t_map generateMap(int width, int height, const std::string &rulePath);
};

std::ostream &operator<<(std::ostream &os, const t_map &instance);