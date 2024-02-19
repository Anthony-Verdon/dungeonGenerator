#include "ruleFileParser.hpp"
#include "../../../libs/jsoncpp_x64-linux/include/json/json.h"
#include "../../globals.hpp"
#include <fstream>
#include <iostream>
#include <string>

std::vector<Tile> ruleFileParser::parseRuleFile(const std::string &rulePath)
{
    std::ifstream ifs(rulePath);
    Json::Reader reader;
    Json::Value obj;
    reader.parse(ifs, obj);
    std::vector<Tile> tileset;

    for (int i = 0; obj["tiles"][i]; i++)
    {
        Tile newTile(std::make_unique<Texture>(obj["tiles"][i]["path"].asString()));
        newTile.setID(i);
        for (int j = 0; j < 4; j++)
        {
            for (int k = 0; obj["tiles"][i][directionsPossibilityArray[j]][k]; k++)
                newTile.addPossibleNeighbors(j, obj["tiles"][i][directionsPossibilityArray[j]][k].asInt());
        }
        tileset.push_back(newTile);
    }
    return (tileset);
}

bool ruleFileParser::isRuleFileValid(const std::string &rulePath)
{
    std::ifstream ifs(rulePath);
    Json::Reader reader;
    Json::Value obj;
    reader.parse(ifs, obj);

    try
    {
        if (!obj)
            throw(std::runtime_error("impossible to read"));

        Json::Value::Members members = obj.getMemberNames();
        if (obj.size() > 1)
            throw(std::runtime_error(createErrorMessage(TOO_MUCH_MEMBERS, "root")));
        if (!obj.isMember("tiles"))
            throw(std::runtime_error(createErrorMessage(NO_MEMBER, "tiles")));

        Json::Value tiles = obj["tiles"];
        if (!tiles.isArray() || tiles.size() < 1)
            throw(std::runtime_error(createErrorMessage(WRONG_VALUE, "tiles", ARRAY)));
        for (unsigned int i = 0; i < tiles.size(); i++)
        {
            Json::Value::Members tile = tiles[i].getMemberNames();
            if (!tiles[i].isMember("path"))
                throw(std::runtime_error(createErrorMessage(NO_MEMBER, "path", NONE, i)));
            if (!tiles[i]["path"].isString())
                throw(std::runtime_error(createErrorMessage(WRONG_VALUE, "path", STRING, i)));
            Texture tryTexture(tiles[i]["path"].asString());
            for (int j = 0; j < 4; j++)
            {
                if (!tiles[i].isMember(directionsPossibilityArray[j]))
                    throw(std::runtime_error(createErrorMessage(NO_MEMBER, directionsPossibilityArray[j], NONE, i)));
                if (!tiles[i][directionsPossibilityArray[j]].isArray())
                    throw(std::runtime_error(createErrorMessage(WRONG_VALUE, directionsPossibilityArray[j], ARRAY, i)));

                for (int k = 0; obj["tiles"][i][directionsPossibilityArray[j]][k]; k++)
                {
                    if (!tiles[i][directionsPossibilityArray[j]][k].isInt() ||
                        tiles[i][directionsPossibilityArray[j]][k] < 0 ||
                        tiles[i][directionsPossibilityArray[j]][k] >= tiles.size())
                        throw(std::runtime_error(
                            createErrorMessage(WRONG_VALUE, directionsPossibilityArray[j], INT, i, k)));
                }
            }
        }
    }
    catch (const std::exception &exception)
    {
        std::cerr << "Error while reading " << rulePath << ": " << exception.what() << std::endl;
        return (false);
    }
    return (true);
}

std::string ruleFileParser::createErrorMessage(e_errors error, std::string member, e_values value, int tileIndex,
                                               int neighborIndex)
{
    std::string errorMessage;

    errorMessage += member;
    if (tileIndex != -1)
        errorMessage += " at tile index " + std::to_string(tileIndex) + " ";
    if (neighborIndex != -1)
        errorMessage += "and at index " + std::to_string(neighborIndex) + " ";
    switch (error)
    {
    case NO_MEMBER:
        errorMessage += " is missing";
        break;
    case TOO_MUCH_MEMBERS:
        errorMessage += " contains too much members";
        break;
    case WRONG_VALUE: {
        errorMessage += " isn't ";
        switch (value)
        {
        case ARRAY:
            errorMessage += " an array or hasn't value in it";
            break;
        case STRING:
            errorMessage += " a string";
            break;
        case INT:
            errorMessage += " isn't an int or has an incorrect value";
            break;
        default:
            break;
        }
    }
    default:
        break;
    }
    return (errorMessage);
}