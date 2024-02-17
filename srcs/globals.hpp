#pragma once

#include <string>
#include "enums/e_directions.hpp"
#include "structs/t_point.hpp"

const std::string directionsPossibilityArray[] {
    "possibilityNorth",
    "possibilitySouth",
    "possibilityEast",
    "possibilityWest"
};

const t_point directionModifiersArray[]{
    {0, -1},
    {0, +1},
    {+1, 0},
    {-1, 0}
};