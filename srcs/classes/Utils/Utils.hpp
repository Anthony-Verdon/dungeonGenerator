#pragma once
#include <sstream>
#include <string>
#include <vector>

class Utils
{
  public:
    static std::vector<std::string> splitLine(std::string line);
    static std::stringstream readFile(const std::string &path);
    static unsigned int convertRGBtoNum(unsigned char R, unsigned char G, unsigned char B);
    static bool checkExtension(const std::string &path, const std::string &extension);
};