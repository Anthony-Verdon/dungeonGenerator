#include "preFilledMapParser.hpp"
#include <fstream>
#include "../ruleFileParser/ruleFileParser.hpp"
#include "../Utils/Utils.hpp"
#include <iostream>

t_map preFilledMapParser::parseFile(const std::string &mapPath)
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

bool preFilledMapParser::isPreFilledMapValid(const std::string &mapPath)
{
    try
    {
        std::ifstream mapFile(mapPath);
        std::string line;
        int nbLine = 0;

        long nbTiles;
        size_t width;

        while (std::getline(mapFile, line))
        {
            switch (nbLine)
            {
            case (0): {
                std::size_t index = line.find(' ');
                if (index == std::string::npos)
                    throw (std::runtime_error("no space on first line for width height definition"));
                std::string widthString = line.substr(0, index);
                std::string heightString = line.substr(index);
                char *end;
                width = std::strtol(widthString.c_str(), &end,10);
                if (end[0] != '\0' || width <= 0)
                    throw (std::runtime_error("width invalid"));
                int height = std::strtol(heightString.c_str(), &end,10);
                if (end[0] != '\0' || height <= 0)
                    throw (std::runtime_error("height invalid"));
                break;
            }
            case (1):
                if (!ruleFileParser::isRuleFileValid(line))
                    throw (std::runtime_error("invalid rule file"));
                nbTiles = ruleFileParser::parseRuleFile(line).size();
                break;
            default: {
                std::vector<t_possibleTiles> dataLine;
                std::vector<std::string> lineSplit = Utils::splitLine(line);
                if (lineSplit.size() != width)
                    throw (std::runtime_error("line " + std::to_string(nbLine + 1) + " invalid"));
                for (size_t i = 0; i < width; i++)
                {
                    char *end;
                    long number = std::strtol(lineSplit[i].c_str(), &end, 10);
                    if (end[0] != '\0')
                        throw (std::runtime_error("line " + std::to_string(nbLine + 1) + " invalid"));
                    if (number < -1 || number > nbTiles)
                        throw (std::runtime_error("line " + std::to_string(nbLine + 1) + " invalid"));
                }
                break;
            }
            }
            nbLine++;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return (false);
    }
    
    return (true);
}