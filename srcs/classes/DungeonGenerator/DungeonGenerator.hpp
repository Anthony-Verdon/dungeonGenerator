#pragma once

#include "../../structs/t_map.hpp"
#include "../../structs/t_point.hpp"
#include "../../structs/t_possibleTiles.hpp"
#include <string>
#include <vector>

class DungeonGenerator
{
  private:
    static t_map initMap(int width, int height, const std::string &rulePath);
    static void generationLoop(t_map &map);
    static void defineTile(t_map &map, t_point coord);
    static void resetUpdateMap(t_map &map);
    static void updateNeighbors(t_map &map, t_point coord);
    static bool isNeighborValid(t_map &map, t_point modifier, t_point coord);
    static std::vector<int> combineAllPossibleTiles(t_map map, t_possibleTiles &neighborTile, t_point coord,
                                                    int direction);

  public:
    static t_map generateMap(int width, int height, const std::string &rulePath);
    static t_map generateMap(const std::string &mapPath);
};

std::ostream &operator<<(std::ostream &os, const t_map &instance);