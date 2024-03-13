#pragma once

#include "t_map.hpp"
#include "t_gtkWindow.hpp"
#include <string>

typedef struct s_data
{
    t_gtkWindow window;
    std::string rulepath;
    std::string prefilledMapPath;
    t_map map;
} t_data;