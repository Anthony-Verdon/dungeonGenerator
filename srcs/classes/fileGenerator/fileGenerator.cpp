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

t_map fileGenerator::parseFile(const std::string &mapPath)
{
    t_map map;

    std::ifstream mapFile(mapPath);
    std::string line;
    int nbLine = 0;

    while (std::getline(mapFile, line))
    {
        switch (nbLine)
        {
        case (0): {
            std::size_t index = line.find(' ');
            std::string width = line.substr(0, index);
            std::string height = line.substr(index);
            map.width = std::stoi(width);
            map.height = std::stoi(height);
            break;
        }
        case (1):
            map.rulePath = line;
            map.tileset = ruleFileParser::parseRuleFile(line);
            break;
        default: {
            std::vector<t_possibleTiles> dataLine;
            std::vector<std::string> linesplit = Utils::splitLine(line);
            for (int i = 0; i < map.width; i++)
            {
                t_possibleTiles initPossiblesTiles;
                if (std::stoi(linesplit[i]) == -1)
                {
                    for (unsigned int i = 0; i < map.tileset.size(); i++)
                        initPossiblesTiles.possiblesTilesID.push_back((i));
                    initPossiblesTiles.nbPossibleTiles = map.tileset.size();
                    initPossiblesTiles.isDefined = false;
                }
                else
                {
                    initPossiblesTiles.possiblesTilesID.push_back((std::stoi(linesplit[i])));
                    initPossiblesTiles.nbPossibleTiles = 1;
                    initPossiblesTiles.isDefined = true;
                }
                dataLine.push_back(initPossiblesTiles);
            }
            map.data.push_back(dataLine);
            break;
        }
        }
        nbLine++;
    }
    return (map);
}