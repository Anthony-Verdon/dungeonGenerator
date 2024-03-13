#pragma once

#include <string>
#include "../../structs/t_map.hpp"

class preFilledMapParser
{
    public:
        static bool isPreFilledMapValid(const std::string &mapPath);
        static t_map parseFile(const std::string &mapPath);
};