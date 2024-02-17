#pragma once

#include <string>
#include <vector>
#include "t_possibleTiles.hpp"
#include "../classes/Tile/Tile.hpp"
typedef struct s_map
{
    int width;
    int height;
    std::string rulePath;
    std::vector<Tile> tileset;
    std::vector<std::vector<t_possibleTiles>> data;
} t_map;