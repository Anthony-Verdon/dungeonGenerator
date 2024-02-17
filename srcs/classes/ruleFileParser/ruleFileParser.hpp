#pragma once

#include "../Tile/Tile.hpp"
#include <string>
#include <vector>
#include "../../enums/e_errors.hpp"
#include "../../enums/e_values.hpp"
class ruleFileParser
{
    private:
        static std::string createErrorMessage(e_errors error, std::string member, e_values value = NONE, int tileIndex = -1, int neighborIndex = -1);

    public:
        static std::vector<Tile> parseRuleFile(const std::string &rulePath);
        static bool isRuleFileValid(const std::string &rulePath);
};