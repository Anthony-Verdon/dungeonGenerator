#pragma once

#include "../Tile/Tile.hpp"
#include <string>
#include <vector>

typedef struct s_map
{
    int width;
    int height;
    std::vector<std::vector<int>> data;
} t_map;

class DungeonGenerator
{
  private:
    static std::vector<Tile> parseRuleFile(const std::string &rulePath);

  public:
    static bool isRuleFileValid(const std::string &rulePath);

    static t_map generate(int width, int height, const std::string &rulePath);
};

std::ostream &operator<<(std::ostream &os, const t_map &instance);