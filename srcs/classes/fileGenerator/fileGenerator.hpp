#pragma once

#include "../../structs/t_map.hpp"
#include <string>

class fileGenerator
{
  public:
    static void generateFile(t_map map);
    static t_map parseFile(const std::string &mapPath);
};