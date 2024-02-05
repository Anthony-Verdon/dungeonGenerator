#pragma once

#include <string>
#include <vector>

enum e_Direction
{
    NORTH,
    EAST,
    SOUTH,
    WEST
};

typedef struct s_tile
{
    std::string path;
    float probability;
    std::vector<struct s_tile> possibleNeighbors[4];
} t_tile;

typedef struct s_map
{
    int width;
    int height;
    std::vector<std::vector<int>> data;
} t_map;

class DungeonGenerator
{
  public:
    static t_map generate(int width, int height, const std::string &rulePath);
};

std::ostream &operator<<(std::ostream &os, const t_map &instance);