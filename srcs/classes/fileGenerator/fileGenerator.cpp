#include "fileGenerator.hpp"
#include "../Utils/Utils.hpp"
#include "../ruleFileParser/ruleFileParser.hpp"
#include <cstddef>
#include <fstream>
#include <string>

void fileGenerator::generateFile(const t_map &map, const std::string &folderPath)
{
    std::ofstream fileGenerated(folderPath + "/lastMapGenerated.txt");
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