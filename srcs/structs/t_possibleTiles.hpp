#pragma once

#include <vector>

typedef struct s_possibleTiles
{
    bool isDefined;
    bool hasBeenUpdated;
    int nbPossibleTiles;
    std::vector<int> possiblesTilesID;
} t_possibleTiles;