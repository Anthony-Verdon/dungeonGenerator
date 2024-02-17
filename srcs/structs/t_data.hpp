#pragma once

#include "t_map.hpp"
#include <string>

typedef struct s_data
{
    std::string rulepath;
    int scale;
    t_map map;
} t_data;