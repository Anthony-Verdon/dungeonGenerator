#include "fileGenerator.hpp"

#include <fstream>

void fileGenerator::generateFile(t_map map)
{
    std::ofstream fileGenerated("lastMapGenerated.txt");
    fileGenerated << map.width << " " << map.height << std::endl;
    fileGenerated << map.rulePath << std::endl;
    for (int y = 0; y < map.height; y++)
    {
        for (int x = 0; x < map.width; x++)
            fileGenerated << map.data[y][x].possiblesTilesID[0] << " ";
        fileGenerated << std::endl;
    }
    fileGenerated.close();
}